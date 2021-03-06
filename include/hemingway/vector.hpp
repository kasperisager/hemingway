// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <random>

namespace lsh {
  class vector {
    private:
      /**
       * The size of component chunks.
       */
      static const unsigned int chunk_size_ = sizeof(unsigned int) * 8;

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
       * Create a new vector.
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
       * Check if this vector is equal to another vector.
       *
       * @param vector The other vector.
       * @return `true` if this vector equals the other vector, otherwise `false`.
       */
      bool operator==(const vector& vector) const;

      /**
       * Check if this vector is different from another vector.
       *
       * @param vector The other vector.
       * @return `true` if this vector differs from the other vector, otherwise `false`.
       */
      bool operator!=(const vector& vector) const;

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
      unsigned int hash() const;

      /**
       * Compute the distance between two vectors.
       *
       * @see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
       *
       * @param u The first vector.
       * @param v The second vector.
       * @return The distance between the two vectors.
       */
      static unsigned int distance(const vector& u, const vector& v);

      /**
       * Construct a random vector of a given dimensionality.
       *
       * @param dimensions The number of dimensions in the vector.
       * @return The randomly generated vector.
       */
      static vector random(unsigned int dimensions);
  };
}
