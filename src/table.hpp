// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "vector.hpp"
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
      std::vector<std::unique_ptr<mask>> masks_;

      /**
       * The partitions containing the buckets of vectors.
       */
      std::vector<partition> partitions_;

    public:
      struct classic {
        /**
         * The number of dimensions of vectors in the table.
         */
        unsigned int dimensions;

        /**
         * The width of each vector hash.
         */
        unsigned int width;

        /**
         * The number of paritions to use.
         */
        unsigned int partitions;
      };

      struct covering {
        /**
         * The number of dimensions of vectors in the table.
         */
        unsigned int dimensions;

        /**
         * The radius to cover in the table.
         */
        unsigned int radius;
      };

      /**
       * Construct a new classic lookup table.
       *
       * @param config The configuration parameters for the lookup table.
       */
      table(classic config);

      /**
       * Construct a new covering lookup table.
       *
       * @param config The configuration parameters for the lookup table.
       */
      table(covering config);

      /**
       * Get the number of vectors in this lookup table.
       *
       * @return The number of vectors in this lookup table.
       */
      unsigned int size() const;

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
