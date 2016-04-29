// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <vector>
#include <hayai/hayai.hpp>
#include <hayai/hayai_posix_main.cpp>
#include <hemingway/vector.hpp>

using namespace lsh;

std::vector<bool> c(128);

vector u = vector::random(128);
vector v = vector::random(128);

BENCHMARK(vector, vector, 10000, 300) {
  lsh::vector v(c);
}

BENCHMARK(vector, size, 10000, 75000) {
  v.size();
}

BENCHMARK(vector, get, 10000, 18000) {
  v.get(64);
}

BENCHMARK(vector, equals, 10000, 10000) {
  bool f = v == u;
}

BENCHMARK(vector, dot_product, 10000, 10000) {
  v * u;
}

BENCHMARK(vector, and, 10000, 500) {
  v & u;
}

BENCHMARK(vector, hash, 10000, 28000) {
  v.hash();
}

BENCHMARK(vector, distance, 10000, 9000) {
  vector::distance(u, v);
}

BENCHMARK(vector, random, 10000, 10) {
  vector::random(128);
}
