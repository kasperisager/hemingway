// Copyright (c) 2016 Kasper Kronborg Isager.
#include "vector.hpp"

namespace lsh {
  /**
   * Construct a new vector.
   *
   * @param components The components of the vector.
   */
  vector::vector(std::vector<bool> components) {
    this->size_ = components.size();

    unsigned int s = this->size_;
    unsigned char c = sizeof(s) * 8;

    unsigned int i = 0;
    unsigned char k = 0;

    while (i < s) {
      this->components_.push_back(0);

      unsigned int n = i + c > s ? s - i : c;

      for (int j = 0; j < n; j++) {
        this->components_[k] |= components[i + j] << (n - j - 1);
      }

      i += n;
      k += 1;
    }
  }

  /**
   * Get the number of components in this vector.
   *
   * @return The number of components in this vector.
   */
  unsigned int vector::size() {
    return this->size_;
  }

  /**
   * Get the component at the specified index of this vector.
   *
   * @param index The index of the component to get.
   * @return The component at the index.
   */
  bool vector::get(int index) {
    unsigned int s = this->size_;
    unsigned char c = sizeof(s) * s;

    if (index < 0 || index >= s) {
      return -1;
    }

    unsigned int d = index / s;
    unsigned int j = d * s;
    unsigned int p = j + c > s ? s - j : c;

    return (this->components_[d] >> (p - (index % s) - 1)) & 1;
  }

  /**
   * Get a string representation of this vector.
   *
   * @return The string representation of the vector.
   */
  std::string vector::to_string() {
    unsigned int n = this->size_;

    std::string value = "Vector[";

    for (int i = 0; i < n; i++) {
      value += std::to_string(this->get(i));
    }

    return value + "]";
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
  int vector::distance(vector& u, vector& v) {
    unsigned int d = 0;
    unsigned int n = u.components_.size();

    for (int i = 0; i < n; i++) {
      int x = u.components_[i] ^ v.components_[i];

      while (x) {
        x &= x - 1;
        d++;
      }
    }

    return d;
  }
}
