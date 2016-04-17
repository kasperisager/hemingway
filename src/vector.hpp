// Copyright (c) 2016 Kasper Kronborg Isager.
#pragma once

#include <string>
#include <vector>

namespace lsh {
  class vector {
    private:
      /**
       * The number of components in this vector.
       */
      unsigned int size_;

      /**
       * The chunked components of this vector.
       */
      std::vector<unsigned int> components_;

    public:
      /**
       * Construct a new vector.
       *
       * @param components The components of the vector.
       */
      vector(std::vector<bool> components);

      /**
       * Get the number of components in this vector.
       *
       * @return The number of components in this vector.
       */
      unsigned int size();

      /**
       * Get the component at the specified index of this vector.
       *
       * @param index The index of the component to get.
       * @return The component at the index.
       */
      bool get(int index);

      /**
       * Get a string representation of this vector.
       *
       * @return The string representation of the vector.
       */
      std::string to_string();

      /**
       * Compute the distance between two vectors.
       *
       * @see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
       *
       * @param u The first vector.
       * @param v The second vector.
       * @return The distance between the two vectors.
       */
      static int distance(vector& u, vector& v);
  };
}
