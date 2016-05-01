// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <vector>
#include <hayai/hayai.hpp>
#include <hayai/hayai_posix_main.cpp>
#include <hemingway/table.hpp>

using namespace lsh;

table t_cla({.dimensions = 128, .samples = 32, .partitions = 64});
table t_cov({.dimensions = 128, .radius = 5});

BENCHMARK(table, table_classic, 500, 4) {
  table({.dimensions = 128, .samples = 32, .partitions = 64});
}

BENCHMARK(table, table_covering, 500, 2) {
  table({.dimensions = 128, .radius = 5});
}

BENCHMARK(table, insert_classic, 1500, 10) {
  t_cla.insert(vector::random(128));
}

BENCHMARK(table, insert_covering, 1500, 10) {
  t_cov.insert(vector::random(128));
}

BENCHMARK(table, query_classic, 1500, 10) {
  t_cla.query(vector::random(128));
}

BENCHMARK(table, query_covering, 1500, 10) {
  t_cov.query(vector::random(128));
}
