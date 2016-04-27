// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <vector>
#include "../lib/hayai/hayai.hpp"
#include "../lib/hayai/hayai_posix_main.cpp"
#include "../src/table.hpp"

using namespace lsh;

table t_cla({.dimensions = 128, .width = 32, .partitions = 64});
table t_cov({.dimensions = 128, .radius = 5});

vector v = vector::random(128);

BENCHMARK(table, table_classic, 500, 4) {
  table({.dimensions = 128, .width = 32, .partitions = 64});
}

BENCHMARK(table, table_covering, 500, 2) {
  table({.dimensions = 128, .radius = 5});
}

BENCHMARK(table, insert_classic, 10000, 10) {
  t_cla.insert(v);
}

BENCHMARK(table, insert_covering, 10000, 10) {
  t_cov.insert(v);
}

BENCHMARK(table, query_classic, 10000, 10) {
  t_cla.query(v);
}

BENCHMARK(table, query_covering, 10000, 10) {
  t_cov.query(v);
}
