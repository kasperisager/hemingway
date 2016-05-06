// Copyright (c) 2016 Kasper Kronborg Isager and Radosław Niemczyk.
#include <vector>
#include <iostream>
#include <fstream>
#include <hayai/hayai.hpp>
#include <hayai/hayai_posix_main.cpp>
#include <hemingway/vector.hpp>
#include <hemingway/table.hpp>

using namespace lsh;

std::vector<vector> parse(std::string path) {
  std::ifstream stream(path, std::ios::binary);
  std::vector<vector> vectors;

  std::vector<char> buffer(1 << 20);

  while (!stream.eof()) {
    stream.read(&buffer[0], 1 << 20);

    int read = stream.gcount();

    for (int i = 0; i < read; i += 8) {
      unsigned long n;

      for (int j = 0; j < 8; j++) {
        ((char*) &n)[j] = buffer[i + j];
      }

      std::vector<bool> c(64);

      for (int j = 0; j < 64; j++) {
          c[j] = (n >> (63 - j)) & 1;
      }

      vectors.push_back(vector(c));
    }
  }

  return vectors;
}

std::vector<vector> vs = parse("bench/data/vectors.bin");
std::vector<vector> qs = parse("bench/data/queries.bin");

std::vector<vector> gt;

table t_lin(table::brute({.dimensions = 64}));

table t_cla({.dimensions = 64, .samples = 31, .partitions = 31});
table t_cov({.dimensions = 64, .radius = 4});

unsigned int vn = vs.size();
unsigned int qn = qs.size();

unsigned int vi;
unsigned int qi;

unsigned int runs = 50;

BENCHMARK(table, insert_linear, runs, vn / runs) {
  t_lin.insert(vs[vi++ % vn]);
}

BENCHMARK(table, insert_classic, runs, vn / runs) {
  t_cla.insert(vs[vi++ % vn]);
}

BENCHMARK(table, insert_covering, runs, vn / runs) {
  t_cov.insert(vs[vi++ % vn]);
}

BENCHMARK(table, query_linear, runs, qn / runs) {
  vector q = qs[qi++ % qn];
  vector r = t_lin.query(q);

  gt.push_back(r);
}

BENCHMARK(table, query_classic, runs, qn / runs) {
  unsigned int i = qi++ % qn;

  vector q = qs[i];
  vector t = gt[i];

  vector r = t_cla.query(q);

  if (vector::distance(q, t) <= 4) {
    if (r.size() == 0) {
    }

    else if (vector::distance(q, r) > 4) {
    }
  }
}

BENCHMARK(table, query_covering, runs, qn / runs) {
  unsigned int i = qi++ % qn;

  vector q = qs[i];
  vector t = gt[i];

  vector r = t_cov.query(q);

  if (vector::distance(q, t) <= 4) {
    if (r.size() == 0) {
    }

    else if (vector::distance(q, r) > 4) {
    }
  }
}
