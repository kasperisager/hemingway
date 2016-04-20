// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#pragma once

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
      virtual vector project(const vector& vector) const;
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
       * Construct a new mask.
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
      vector project(const vector& vector) const;
  };

  class covering_mask: public mask {
    public:
      /**
       * A random mapping of vectors.
       */
      typedef std::vector<vector> mapping;

    private:
      /**
       * The random mapping to use for this mask.
       */
      mapping mapping_;

      /**
       * Project a vector, reducing it to a dimensionality specified by this mask.
       *
       * @param vector The vector to project.
       * @return The projected vector.
       */
      vector project(const vector& vector) const;

      /**
       * Create a random mapping.
       *
       * @param dimensions The number of vectors in the mapping.
       * @param radius The radius that the mapping should cover.
       * @return The random mapping.
       */
      static mapping create_mapping(unsigned int dimensions, unsigned int radius);
  };
}
