// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#pragma once

#include <stdexcept>
#include <memory>
#include <vector>
#include <random>
#include "vector.hpp"

namespace lsh {
  class mask {
    public:
      /**
       * Project a vector.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      virtual vector project(const vector& vector) const = 0;
  };

  class classic_mask: public mask {
    private:
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
       * Construct a new classic mask.
       *
       * @param dimensionality The dimensionality of vectors to mask.
       * @param width The number of dimensions in vector projections.
       */
      classic_mask(unsigned int dimensions, unsigned int width);

      /**
       * Project a vector.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      vector project(const vector& vector) const override;
  };

  class covering_mask: public mask {
    public:
      /**
       * A random mapping of vectors.
       */
      typedef std::vector<vector> mapping;

    private:
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
       * Construct a new covering mask.
       *
       * @param dimensionality The dimensionality of vectors to mask.
       * @param vector The vector to use for this mask.
       * @param mapping The random vector mapping to use for the mask.
       */
      covering_mask(unsigned int dimensions, unsigned int vector, const mapping& mapping);

      /**
       * Project a vector.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      vector project(const vector& vector) const override;
  };
}
