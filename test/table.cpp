// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <test.hpp>
#include <hemingway/vector.hpp>
#include <hemingway/table.hpp>

lsh::vector v1({1, 0, 0, 1});
lsh::vector v2({1, 1, 0, 0});

TEST_CASE("#size returns the number of vectors in a table") {
  lsh::table t({.dimensions = 4, .samples = 2, .partitions = 2});

  REQUIRE(t.size() == 0);

  t.insert(v1);
  t.insert(v2);

  REQUIRE(t.size() == 2);
}

TEST_CASE("#insert adds a vector to a table") {
  lsh::table t({.dimensions = 4, .samples = 2, .partitions = 2});

  t.insert(v1);
  t.insert(v2);

  REQUIRE(t.size() == 2);
  REQUIRE(t.query(v1) == v1);
  REQUIRE(t.query(v2) == v2);
}

TEST_CASE("#erase removes a vector from a table") {
  lsh::table t({.dimensions = 4, .samples = 2, .partitions = 2});

  t.insert(v1);
  t.insert(v2);

  REQUIRE(t.size() == 2);

  t.erase(v2);

  REQUIRE(t.size() == 1);
  REQUIRE(t.query(v1) == v1);
  REQUIRE(t.query(v2) != v2);
}
