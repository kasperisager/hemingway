// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <test.hpp>
#include <hemingway/vector.hpp>

lsh::vector v({1, 0, 0, 1});

TEST_CASE("#size returns the number of components in a vector") {
  REQUIRE(v.size() == 4);
}

TEST_CASE("#get returns the component at a specified index of a vector") {
  REQUIRE(v.get(0) == 1);
  REQUIRE(v.get(1) == 0);
  REQUIRE(v.get(2) == 0);
  REQUIRE(v.get(3) == 1);
}

TEST_CASE("#to_string returns the string representation of a vector") {
  REQUIRE(v.to_string() == "Vector[1001]");
}

TEST_CASE("#== checks if a vector is equal to another vector") {
  lsh::vector v1({1, 1, 1, 0});
  lsh::vector v2({1, 1, 1, 0});
  lsh::vector v3({1, 1, 0, 0});

  REQUIRE(v1 == v1);
  REQUIRE(v1 == v2);
  REQUIRE(!(v1 == v3));
  REQUIRE(!(v2 == v3));
}

TEST_CASE("#!= checks if a vector is different from another vector") {
  lsh::vector v1({1, 1, 1, 0});
  lsh::vector v2({1, 1, 1, 0});
  lsh::vector v3({1, 1, 0, 0});

  REQUIRE(v1 != v3);
  REQUIRE(!(v1 != v1));
  REQUIRE(!(v1 != v2));
}

TEST_CASE("#* computes the dot product of two vectors") {
  lsh::vector v1({1, 1, 1, 0});
  lsh::vector v2({1, 0, 1, 0});

  REQUIRE(v1 * v2 == 2);
}

TEST_CASE("#& computes the bitwise AND of two vectors") {
  lsh::vector v1({1, 1, 0, 0});
  lsh::vector v2({1, 0, 0, 1});
  lsh::vector v3({1, 0, 0, 0});

  REQUIRE((v1 & v2) == v3);
}

TEST_CASE("#hash returns the hash value of a vector") {
  REQUIRE(v.hash() == 9);
}

TEST_CASE(".distance computes the distance between two vectors") {
  lsh::vector v1({1, 1, 0, 0});
  lsh::vector v2({1, 0, 1, 0});

  REQUIRE(lsh::vector::distance(v1, v2) == 2);
}
