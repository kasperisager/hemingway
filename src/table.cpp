// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <hemingway/table.hpp>

namespace lsh {
  /**
   * Construct a new classic lookup table.
   *
   * @param config The configuration parameters for the lookup table.
   */
  table::table(const classic& c) {
    unsigned int d = c.dimensions;
    unsigned int s = c.samples;
    unsigned int p = c.partitions;

    this->dimensions_ = d;
    this->masks_.reserve(p);
    this->partitions_.reserve(p);

    for (unsigned int i = 0; i < p; i++) {
      this->masks_.push_back(classic_mask(d, s));
      this->partitions_.push_back(partition());
    }
  }

  /**
   * Construct a new covering lookup table.
   *
   * @param config The configuration parameters for the lookup table.
   */
  table::table(const covering& c) {
    unsigned int d = c.dimensions;
    unsigned int r = c.radius;
    unsigned int n = 1 << (r + 1);

    this->dimensions_ = d;
    this->masks_.reserve(n - 1);
    this->partitions_.reserve(n - 1);

    covering_mask::mapping m;

    for (unsigned int i = 0; i < d; i++) {
      m.push_back(vector::random(n));
    }

    for (unsigned int i = 1; i < n; i++) {
      std::vector<bool> c(n);

      for (unsigned int j = 0; j < n; j++) {
        c[j] = (i >> (n - j - 1)) & 1;
      }

      this->masks_.push_back(covering_mask(d, vector(c), m));
      this->partitions_.push_back(partition());
    }
  }

  /**
   * Construct a brute-force lookup table.
   *
   * @param config The configuration parameters for the lookup table.
   */
  table::table(const brute& c) {
    unsigned int d = c.dimensions;

    this->dimensions_ = d;
    this->masks_.push_back(brute_mask(d));
    this->partitions_.push_back(partition());
  }

  /**
   * Get the number of vectors in this lookup table.
   *
   * @return The number of vectors in this lookup table.
   */
  unsigned int table::size() const {
    return this->vectors_.size();
  }

  /**
   * Insert a vector into this lookup table.
   *
   * @param vector The vector to insert into this lookup table.
   */
  void table::insert(const vector& v) {
    if (this->dimensions_ != v.size()) {
      throw std::invalid_argument("Invalid vector size");
    }

    unsigned int n = this->partitions_.size();
    unsigned int u = this->next_id_++;

    this->vectors_.insert({u, v});

    for (unsigned int i = 0; i < n; i++) {
      vector k = this->masks_[i].project(v);
      bucket& b = this->partitions_[i][k.hash()];

      b.push_back(u);
    }
  }

  /**
   * Erase a vector from this lookup table.
   *
   * @param vector The vector to erase from this lookup table.
   */
  void table::erase(const vector& v) {
    if (this->dimensions_ != v.size()) {
      throw std::invalid_argument("Invalid vector size");
    }

    unsigned int n = this->partitions_.size();
    unsigned int u = 0;

    for (const auto& it: this->vectors_) {
      if (it.second == v) {
        u = it.first;
        break;
      }
    }

    this->vectors_.erase(u);

    for (unsigned int i = 0; i < n; i++) {
      partition& p = this->partitions_[i];

      for (auto& it: p) {
        bucket& b = it.second;

        for (auto j = b.begin(); j != b.end(); j++) {
          if (*j == u) {
            b.erase(j);
            break;
          }
        }
      }
    }
  }

  /**
   * Query this lookup table for the nearest neighbour of a query vector.
   *
   * @param vector The query vector to look up the nearest neighbour of.
   * @return The nearest neighbouring vector if found, otherwise a vector of size 0.
   */
  vector table::query(const vector& v) {
    if (this->dimensions_ != v.size()) {
      throw std::invalid_argument("Invalid vector size");
    }

    unsigned int n = this->partitions_.size();

    // Keep track of the best candidate we've encountered.
    const vector* best_c = nullptr;

    // Keep track of the distance to the best candidate.
    unsigned int best_d = UINT_MAX;

    for (unsigned int i = 0; i < n; i++) {
      vector k = this->masks_[i].project(v);
      bucket& b = this->partitions_[i][k.hash()];

      for (unsigned int u: b) {
        vector& c = this->vectors_.at(u);

        unsigned int d = vector::distance(v, c);

        if (d < best_d) {
          best_c = &c;
          best_d = d;
        }
      }
    }

    return best_c ? *best_c : vector({});
  }
}
