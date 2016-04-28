// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include "table.hpp"

namespace lsh {
  /**
   * Construct a new classic lookup table.
   *
   * @param config The configuration parameters for the lookup table.
   */
  table::table(classic c) {
    unsigned int d = c.dimensions;
    unsigned int w = c.width;
    unsigned int p = c.partitions;

    this->dimensions_ = d;

    this->masks_.resize(p);
    this->partitions_.resize(p);

    for (unsigned int i = 0; i < p; i++) {
      std::unique_ptr<mask> mask(new classic_mask(d, w));

      this->masks_[i] = std::move(mask);
      this->partitions_[i] = partition();
    }
  }

  /**
   * Construct a new covering lookup table.
   *
   * @param config The configuration parameters for the lookup table.
   */
  table::table(covering c) {
    unsigned int d = c.dimensions;
    unsigned int r = c.radius;

    this->dimensions_ = d;

    unsigned int n = (1 << (r + 1)) - 1;

    covering_mask::mapping m;

    for (unsigned int i = 0; i < d; i++) {
      m.push_back(vector::random(n + 1));
    }

    this->masks_.resize(n);
    this->partitions_.resize(n);

    for (unsigned int i = 0; i < n; i++) {
      std::unique_ptr<mask> mask(new covering_mask(d, i + 1, m));

      this->masks_[i] = std::move(mask);
      this->partitions_[i] = partition();
    }
  }

  /**
   * Get the number of vectors in this lookup table.
   *
   * @return The number of vectors in this lookup table.
   */
  unsigned int table::size() const {
    return this->size_;
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

    std::shared_ptr<vector> u = std::make_shared<vector>(v);

    for (unsigned int i = 0; i < n; i++) {
      vector k = this->masks_[i]->project(v);
      bucket* b = &this->partitions_[i][k];

      b->insert(u);
    }

    this->size_++;
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

    std::shared_ptr<vector> u = std::make_shared<vector>(v);

    for (unsigned int i = 0; i < n; i++) {
      vector k = this->masks_[i]->project(v);
      bucket* b = &this->partitions_[i][k];

      b->erase(u);
    }

    this->size_--;
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
    std::shared_ptr<vector> best_c;

    // Keep track of the distance to the best candidate.
    unsigned int best_d = UINT_MAX;

    for (unsigned int i = 0; i < n; i++) {
      vector k = this->masks_[i]->project(v);
      bucket* b = &this->partitions_[i][k];

      for (const std::shared_ptr<vector>& c: *b) {
        unsigned int d = vector::distance(v, *c);

        if (d < best_d) {
          best_c = c;
          best_d = d;
        }
      }
    }

    // In case we didn't find a vector then return the null vector.
    if (!best_c) {
      return vector({});
    }

    return *best_c;
  }
}
