// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#pragma once

#include <stdexcept>
#include <memory>
#include <vector>
#include <random>
#include "vector.hpp"

namespace lsh {
  class mask {
    protected:
      /**
       * The dimensionality of vectors to mask.
       */
      unsigned int dimensions_;

      /**
       * The vector mask to use.
       */
      std::unique_ptr<vector> mask_;

    public:
      /**
       * Project a vector.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      vector project(const vector& vector) const;
  };

  class classic_mask: public mask {
    public:
      /**
       * Construct a new classic mask.
       *
       * @param dimensionality The dimensionality of vectors to mask.
       * @param width The number of dimensions in vector projections.
       */
      classic_mask(unsigned int dimensions, unsigned int width);
  };

  class covering_mask: public mask {
    public:
      /**
       * A random mapping of vectors.
       */
      typedef std::vector<vector> mapping;

      /**
       * Construct a new covering mask.
       *
       * @param dimensionality The dimensionality of vectors to mask.
       * @param vector The vector to use for this mask.
       * @param mapping The random vector mapping to use for the mask.
       */
      covering_mask(unsigned int dimensions, unsigned int vector, const mapping& mapping);
  };
}
