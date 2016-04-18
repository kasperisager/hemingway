// Copyright (c) 2016 Kasper Kronborg Isager.
#pragma once

#include <vector>
#include <random>
#include "vector.hpp"

namespace lsh {
  class mask {
    private:
      /**
       * The number of dimensions in vector projections.
       */
      unsigned int width_;

      /**
       * The randomly chosen indices to pick for vector projections.
       */
      std::vector<unsigned int> indices_;

    public:
      /**
       * Construct a new mask.
       *
       * @param dimensionality The dimensionality of vectors to mask.
       * @param width The number of dimensions in vector projections.
       */
      mask(unsigned int dimensions, unsigned int width);

      /**
       * Project a vector, reducing it to a dimensionality specified by this mask.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      vector project(const vector& vector) const;
  };
}
