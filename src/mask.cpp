// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#include "mask.hpp"

namespace lsh {
  /**
   * Construct a new mask.
   *
   * @param dimensionality The dimensionality of vectors to mask.
   * @param width The number of dimensions in vector projections.
   */
  random_mask::random_mask(unsigned int dimensions, unsigned int width) {
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<unsigned int> indices (0, dimensions - 1);

    this->width_ = width;

    for (unsigned int i = 0; i < width; i++) {
      this->indices_.push_back(indices(generator));
    }
  }

  /**
   * Project a vector, reducing it to a dimensionality specified by this mask.
   *
   * @param vector The vector to project.
   * @return The projected vector.
   */
  vector random_mask::project(const vector& vector) const {
    unsigned int w = this->width_;

    std::vector<bool> c;

    for (unsigned int i = 0; i < w; i++) {
      c.push_back(vector.get(this->indices_[i]));
    }

    return lsh::vector(c);
  }

  /**
   * Construct a new covering mask.
   *
   * @param dimensionality The dimensionality of vectors to mask.
   * @param vector The vector to use for this mask.
   * @param mapping The random vector mapping to use for the mask.
   */
  covering_mask::covering_mask(unsigned int dimensions, unsigned int vector, mapping mapping) {
    std::vector<bool> c(dimensions);

    for (unsigned int j = 0; j < dimensions; j++) {
      c[j] = (mapping[j] * vector) % 2;
    }

    this->mask_ = new lsh::vector(c);
  }

  /**
   * Destruct this covering mask.
   */
  covering_mask::~covering_mask() {
    delete this->mask_;
  }

  /**
   * Project a vector, reducing it to a dimensionality specified by this mask.
   *
   * @param vector The vector to project.
   * @return The projected vector.
   */
  vector covering_mask::project(const vector& vector) const {
    return *this->mask_ & vector;
  }
}
