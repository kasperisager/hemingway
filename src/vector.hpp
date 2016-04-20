// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#pragma once

#include <string>
#include <vector>
#include <random>

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

      /**
       * Create a new vector from existing component chunks.
       *
       * @param components The existing component chunks.
       * @param size The number of components.
       */
      vector(const std::vector<unsigned int>& components, unsigned int size);

    public:
      /**
       * Construct a new vector.
       *
       * @param components The components of the vector.
       */
      vector(const std::vector<bool>& components);

      /**
       * Get the number of components in this vector.
       *
       * @return The number of components in this vector.
       */
      unsigned int size() const;

      /**
       * Get the component at the specified index of this vector.
       *
       * @param index The index of the component to get.
       * @return The component at the index.
       */
      bool get(unsigned int index) const;

      /**
       * Get a string representation of this vector.
       *
       * @return The string representation of the vector.
       */
      std::string to_string() const;

      /**
       * Check if this vector equals another vector.
       *
       * @param vector The other vector.
       * @return `true` if this vector equals the other vector, otherwise `false`.
       */
      bool operator==(const vector& vector) const;

      /**
       * Compute the dot product of this and another vector.
       *
       * @param vector The other vector.
       * @return The dot product of this and another vector.
       */
      unsigned int operator*(const vector& vector) const;

      /**
       * Compute the bitwise AND of this and another vector.
       *
       * @param vector The other vector.
       * @return The bitwise AND of this and another vector.
       */
      vector operator&(const vector& vector) const;

      /**
       * Compupte the hash of this vector.
       *
       * @return The hash of this vector.
       */
      int hash() const;

      /**
       * Compute the distance between two vectors.
       *
       * @see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
       *
       * @param u The first vector.
       * @param v The second vector.
       * @return The distance between the two vectors.
       */
      static int distance(const vector& u, const vector& v);

      /**
       * Construct a random vector of a given dimensionality.
       *
       * @param dimensions The number of dimensions in the vector.
       * @return The randomly generated vector.
       */
      static vector random(unsigned int dimensions);
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
      size_t operator()(const lsh::vector& vector) const {
        return vector.hash();
      }
  };
}
