// Copyright (c) 2016 Kasper Kronborg Isager.
#pragma once

#include <vector>
#include <unordered_map>
#include "mask.hpp"

namespace lsh {
  class table {
    private:
      /**
       * A bucket containing vectors who are candidate pairs.
       */
      typedef std::vector<vector> bucket;

      /**
       * A partition consisting of buckets of vectors.
       */
      typedef std::unordered_map<vector, bucket> partition;

      /**
       * The number of dimensions of vectors in the table.
       */
      unsigned int dimensions_;

      /**
       * The number of vectors in this lookup table.
       */
      unsigned int size_;

      /**
       * The bit masks used for constructing vector projections.
       */
      std::vector<mask> masks_;

      /**
       * The partitions containing the buckets of vectors.
       */
      std::vector<partition> partitions_;

    public:
      /**
       * Construct a new lookup table.
       *
       * @param dimensions The number of dimensions of vectors in the table.
       * @param width The width of each vector hash.
       * @param partitions The number of paritions to use.
       */
      table(unsigned int dimensions, unsigned int width, unsigned int partitions);

      /**
       * Get the number of vectors in this lookup table.
       *
       * @return The number of vectors in this lookup table.
       */
      int size() const;

      /**
       * Add a vector to this lookup table.
       *
       * @param vector The vector to add to this lookup table.
       */
      void add(vector vector);

      /**
       * Query this lookup table for the nearest neighbour of a query vector.
       *
       * @param vector The query vector to look up the nearest neighbour of.
       * @return The nearest neighbouring vector if found, otherwise a vector of size 0.
       */
      vector query(const vector& vector);
  };
}
