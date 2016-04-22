// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#pragma once

#include <memory>
#include <vector>
#include <random>
#include "vector.hpp"

namespace lsh {
  /**
   * The mask class acts as sort of a bit mask that can reduce the dimensionality of
   * vectors by a projection.
   */
  class mask {
    public:
      /**
       * Project a vector, reducing it to a dimensionality specified by this mask.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      virtual vector project(const vector& vector) const = 0;
  };

  class random_mask: public mask {
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
       * Construct a new random mask.
       *
       * @param dimensionality The dimensionality of vectors to mask.
       * @param width The number of dimensions in vector projections.
       */
      random_mask(unsigned int dimensions, unsigned int width);

      /**
       * Project a vector, reducing it to a dimensionality specified by this mask.
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
      covering_mask(unsigned int dimensions, unsigned int vector, mapping mapping);

      /**
       * Project a vector, reducing it to a dimensionality specified by this mask.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      vector project(const vector& vector) const override;
  };
}
