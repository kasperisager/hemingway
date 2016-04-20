// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#include "table.hpp"

namespace lsh {
  /**
   * Construct a new lookup table.
   *
   * @param dimensions The number of dimensions of vectors in the table.
   * @param width The width of each vector hash.
   * @param partitions The number of paritions to use.
   */
  table::table(unsigned int dimensions, unsigned int width, unsigned int partitions) {
    this->dimensions_ = dimensions;

    for (unsigned int i = 0; i < partitions; i++) {
      this->masks_.push_back(random_mask(dimensions, width));
      this->partitions_.push_back(partition());
    }
  }

  /**
   * Construct a new lookup table.
   *
   * @param dimensions The number of dimensions of vectors in the table.
   * @param radius The radius to cover in the table.
   */
  table::table(unsigned int dimensions, unsigned int radius) {
    covering_mask::mapping m = covering_mask::create_mapping(dimensions, radius);

    unsigned int n = (1 << (radius + 1)) - 1;

    for (unsigned int i = 0; i < n; i++) {
      this->masks_.push_back(covering_mask(dimensions, i, m));
      this->partitions_.push_back(partition());
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
   * Add a vector to this lookup table.
   *
   * @param vector The vector to add to this lookup table.
   */
  void table::add(vector vector) {
    unsigned int n = this->partitions_.size();

    for (unsigned int i = 0; i < n; i++) {
      lsh::vector k = this->masks_[i].project(vector);
      bucket* b = &this->partitions_[i][k];

      b->push_back(vector);
    }

    this->size_++;
  }

  /**
   * Query this lookup table for the nearest neighbour of a query vector.
   *
   * @param vector The query vector to look up the nearest neighbour of.
   * @return The nearest neighbouring vector if found, otherwise a vector of size 0.
   */
  vector table::query(const vector& vector) {
    unsigned int n = this->partitions_.size();

    // Keep track of the best candidate we've encountered.
    lsh::vector* best_c = NULL;

    // Keep track of the distance to the best candidate.
    unsigned int best_d = 0;

    for (unsigned int i = 0; i < n; i++) {
      lsh::vector k = this->masks_[i].project(vector);
      bucket* b = &this->partitions_[i][k];

      for (lsh::vector& c: *b) {
        unsigned int d = lsh::vector::distance(vector, c);

        if (!best_c || d < best_d) {
          best_c = &c;
          best_d = d;
        }
      }
    }

    // In case we didn't find a vector then return the null vector.
    if (!best_c) {
      return lsh::vector(std::vector<bool> {});
    }

    return *best_c;
  }
}
