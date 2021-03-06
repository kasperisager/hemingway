// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <vector>
#include <hayai/hayai.hpp>
#include <hayai/hayai_posix_main.cpp>
#include <hemingway/vector.hpp>

using namespace lsh;

std::vector<bool> c(128);

vector u = vector::random(128);
vector v = vector::random(128);

BENCHMARK(vector, vector, 10000, 350) {
  lsh::vector v(c);
}

BENCHMARK(vector, size, 10000, 55000) {
  v.size();
}

BENCHMARK(vector, get, 10000, 16000) {
  v.get(64);
}

BENCHMARK(vector, equals, 10000, 5500) {
  void(v == u);
}

BENCHMARK(vector, dot_product, 10000, 5500) {
  v * u;
}

BENCHMARK(vector, and, 10000, 600) {
  v & u;
}

BENCHMARK(vector, hash, 10000, 18000) {
  v.hash();
}

BENCHMARK(vector, distance, 10000, 6000) {
  vector::distance(u, v);
}

BENCHMARK(vector, random, 10000, 30) {
  vector::random(128);
}
