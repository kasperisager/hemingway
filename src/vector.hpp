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
       * Check if this vector equals another vector.
       *
       * @param vector The other vector.
       * @return `true` if this vector equals the other vector, otherwise `false`.
       */
      bool operator==(vector& vector);

      /**
       * Compupte the hash of this vector.
       *
       * @return The hash of this vector.
       */
      int hash();

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

namespace std {
  template <> struct hash<lsh::vector> {
    public:
      /**
       * Compute the hash of a vector.
       *
       * This bit of ugliness is required in order for the C++ standard library
       * to utilise LSH vectors in hash-based data structures such as the unordered
       * sets used in lookup tables.
       *
       * @return The hash of the vector.
       */
      size_t operator()(lsh::vector& vector) {
        return vector.hash();
      }
  };
}
