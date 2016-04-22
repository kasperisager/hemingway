// Copyright (c) 2016 Kasper Kronborg Isager and Radoslaw Niemczyk.
#include "vector.hpp"

#include <iostream>

namespace lsh {
  /**
   * Create a new vector from existing component chunks.
   *
   * @param components The existing component chunks.
   * @param size The number of components.
   */
  vector::vector(const std::vector<unsigned int>& components, unsigned int size) {
    this->size_ = size;

    unsigned int n = components.size();

    for (unsigned int i = 0; i < n; i++) {
      this->components_.push_back(components[i]);
    }
  }

  /**
   * Construct a new vector.
   *
   * @param components The components of the vector.
   */
  vector::vector(const std::vector<bool>& components) {
    this->size_ = components.size();

    unsigned int s = this->size_;
    unsigned int c = this->chunk_size_;

    unsigned int i = 0;
    unsigned char k = 0;

    while (i < s) {
      this->components_.push_back(0);

      // Compute the number of bits in the current chunk.
      unsigned int b = i + c > s ? s - i : c;

      for (unsigned int j = 0; j < b; j++) {
        this->components_[k] |= components[i + j] << (b - j - 1);
      }

      i += b;
      k += 1;
    }
  }

  /**
   * Get the number of components in this vector.
   *
   * @return The number of components in this vector.
   */
  unsigned int vector::size() const {
    return this->size_;
  }

  /**
   * Get the component at the specified index of this vector.
   *
   * @param index The index of the component to get.
   * @return The component at the index.
   */
  bool vector::get(unsigned int index) const {
    unsigned int s = this->size_;
    unsigned int c = this->chunk_size_;

    if (index >= s) {
      return -1;
    }

    // Compute the index of the target chunk.
    unsigned int d = index / s;

    // Compute the index of the first bit of the target chunk.
    unsigned int j = d * s;

    // Compute the number of bits in the target chunk.
    unsigned int b = j + c > s ? s - j : c;

    return (this->components_[d] >> (b - (index % s) - 1)) & 1;
  }

  /**
   * Get a string representation of this vector.
   *
   * @return The string representation of the vector.
   */
  std::string vector::to_string() const {
    unsigned int n = this->size_;

    std::string value = "Vector[";

    for (unsigned int i = 0; i < n; i++) {
      value += std::to_string(this->get(i));
    }

    return value + "]";
  }

  /**
   * Check if this vector equals another vector.
   *
   * @param vector The other vector.
   * @return `true` if this vector equals the other vector, otherwise `false`.
   */
  bool vector::operator==(const vector& vector) const {
    return vector::distance(*this, vector) == 0;
  }

  /**
   * Compute the dot product of this and another vector.
   *
   * @param vector The other vector.
   * @return The dot product of this and another vector.
   */
  unsigned int vector::operator*(const vector& vector) const {
    unsigned int d = 0;
    unsigned int n = this->components_.size();

    for (unsigned int i = 0; i < n; i++) {
      d += __builtin_popcount(this->components_[i] & vector.components_[i]);
    }

    return d;
  }

  /**
   * Compute the dot product of this vector and an integer.
   *
   * @param integer The integer.
   * @return The dot product of this vector and an integer.
   */
  unsigned int vector::operator*(unsigned int integer) const {
    unsigned int d = 0;
    unsigned int s = this->size_;
    unsigned int c = this->chunk_size_;
    unsigned int n = this->components_.size();

    for (unsigned int i = 0; i < n; i++) {
      // Compute the index of the first bit of the current chunk.
      unsigned int j = c * i;

      // Compute the number of bits in the current chunk.
      unsigned int m = j + c > s ? s - j : c;

      // Grab the bits of the integer that correspond to the current chunk.
      unsigned int b = (integer >> (s - j - m)) % (1 << m);

      d += __builtin_popcount(this->components_[i] & b);
    }

    return d;
  }

  /**
   * Compute the bitwise AND of this and another vector.
   *
   * @param vector The other vector.
   * @return The bitwise AND of this and another vector.
   */
  vector vector::operator&(const vector& vector) const {
    std::vector<unsigned int> c;

    unsigned int n = this->components_.size();

    for (unsigned int i = 0; i < n; i++) {
      c.push_back(this->components_[i] & vector.components_[i]);
    }

    return lsh::vector(c, this->size_);
  }

  /**
   * Compupte the hash of this vector.
   *
   * @return The hash of this vector.
   */
  int vector::hash() const {
    unsigned int n = this->components_.size();
    unsigned long h = 7;

    for (unsigned int i = 0; i < n; i++) {
      h = 31 * h + this->components_[i];
    }

    return h ^ (h >> 32);
  }

  /**
   * Compute the distance between two vectors.
   *
   * @see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
   *
   * @param u The first vector.
   * @param v The second vector.
   * @return The distance between the two vectors.
   */
  int vector::distance(const vector& u, const vector& v) {
    unsigned int d = 0;
    unsigned int n = u.components_.size();

    for (unsigned int i = 0; i < n; i++) {
      unsigned int x = u.components_[i] ^ v.components_[i];

      while (x) {
        x &= x - 1;
        d++;
      }
    }

    return d;
  }

  /**
   * Construct a random vector of a given dimensionality.
   *
   * @param dimensions The number of dimensions in the vector.
   * @return The randomly generated vector.
   */
  vector vector::random(unsigned int dimensions) {
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<> components(0, 1);

    std::vector<bool> c;

    for (unsigned int i = 0; i < dimensions; i++) {
      c.push_back(components(generator));
    }

    return vector(c);
  }
}
