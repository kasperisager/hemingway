// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#pragma once

#include <stdexcept>
#include <climits>
#include <memory>
#include <vector>
#include <unordered_map>
#include <hemingway/vector.hpp>
#include <hemingway/mask.hpp>

namespace lsh {
  class table {
    private:
      /**
       * A bucket containing candidate pairs.
       */
      typedef std::vector<unsigned int> bucket;

      /**
       * A partition consisting of buckets.
       */
      typedef std::unordered_map<unsigned int, bucket> partition;

      /**
       * The next available vector id.
       */
      unsigned int next_id_;

      /**
       * The number of dimensions of vectors in the table.
       */
      unsigned int dimensions_;

      /**
       * The vectors stored in this lookup table.
       */
      std::unordered_map<unsigned int, vector> vectors_;

      /**
       * The bit masks used for constructing vector projections.
       */
      std::vector<mask> masks_;

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
         * The number of bits to sample from each vector.
         */
        unsigned short samples;

        /**
         * The number of paritions to use.
         */
        unsigned short partitions;
      };

      struct covering {
        /**
         * The number of dimensions of vectors in the table.
         */
        unsigned int dimensions;

        /**
         * The radius to cover in the table.
         */
        unsigned short radius;
      };

      struct brute {
        /**
         * The number of dimensions of vectors in the table.
         */
        unsigned int dimensions;
      };

      /**
       * Construct a new classic lookup table.
       *
       * @param config The configuration parameters for the lookup table.
       */
      table(const classic& config);

      /**
       * Construct a new covering lookup table.
       *
       * @param config The configuration parameters for the lookup table.
       */
      table(const covering& config);

      /**
       * Construct a brute-force lookup table.
       *
       * @param config The configuration parameters for the lookup table.
       */
      table(const brute& config);

      /**
       * Get the number of vectors in this lookup table.
       *
       * @return The number of vectors in this lookup table.
       */
      unsigned int size() const;

      /**
       * Insert a vector into this lookup table.
       *
       * @param vector The vector to insert into this lookup table.
       */
      void insert(const vector& vector);

      /**
       * Erase a vector from this lookup table.
       *
       * @param vector The vector to erase from this lookup table.
       */
      void erase(const vector& vector);

      /**
       * Query this lookup table for the nearest neighbour of a query vector.
       *
       * @param vector The query vector to look up the nearest neighbour of.
       * @return The nearest neighbouring vector if found, otherwise a vector of size 0.
       */
      vector query(const vector& vector);
  };
}
