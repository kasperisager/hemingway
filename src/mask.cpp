// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#include "mask.hpp"

namespace lsh {
  /**
   * Construct a new classic mask.
   *
   * @param dimensionality The dimensionality of vectors to mask.
   * @param width The number of dimensions in vector projections.
   */
  classic_mask::classic_mask(unsigned int d, unsigned int w) {
    this->dimensions_ = d;

    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<> indices (0, d - 1);

    this->dimensions_ = d;

    std::vector<bool> c(d);

    for (unsigned int i = 0; i < w; i++) {
      c[indices(generator)] = 1;
    }

    std::unique_ptr<vector> p(new vector(c));

    this->mask_ = std::move(p);
  }

  /**
   * Project a vector, reducing it to a dimensionality specified by this mask.
   *
   * @param vector The vector to project.
   * @return The projected vector.
   */
  vector classic_mask::project(const vector& v) const {
    if (this->dimensions_ != v.size()) {
      throw std::invalid_argument("Invalid vector size");
    }

    return *this->mask_ & v;
  }

  /**
   * Construct a new covering mask.
   *
   * @param dimensionality The dimensionality of vectors to mask.
   * @param vector The vector to use for this mask.
   * @param mapping The random vector mapping to use for the mask.
   */
  covering_mask::covering_mask(unsigned int d, unsigned int v, const mapping& m) {
    this->dimensions_ = d;

    std::vector<bool> c(d);

    for (unsigned int j = 0; j < d; j++) {
      c[j] = (m[j] * v) % 2;
    }

    std::unique_ptr<vector> p(new vector(c));

    this->mask_ = std::move(p);
  }

  /**
   * Project a vector, reducing it to a dimensionality specified by this mask.
   *
   * @param vector The vector to project.
   * @return The projected vector.
   */
  vector covering_mask::project(const vector& v) const {
    if (this->dimensions_ != v.size()) {
      throw std::invalid_argument("Invalid vector size");
    }

    return *this->mask_ & v;
  }
}
