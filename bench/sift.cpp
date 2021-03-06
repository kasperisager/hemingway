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

double delta = 0.01;

unsigned short r = 4;
unsigned short l = (1 << (r + 1)) - 1;
unsigned short k = ceil(log2(1 - pow(delta, 1.0 / l)) / log2(1 - r / 64.0));

table t_lin(table::brute({.dimensions = 64}));

table t_cla({.dimensions = 64, .samples = k, .partitions = l});
table t_cov({.dimensions = 64, .radius = r});

unsigned int vn = vs.size();
unsigned int qn = qs.size();

unsigned int vi;
unsigned int qi;

unsigned int runs = 50;

void print_stats(const table& t) {
  table::statistics s = t.stats();

  std::cout << "               ";
  std::cout << "Number of buckets: ";
  std::cout << s.buckets / (1.0 * s.partitions);
  std::cout << " /partition" << std::endl;

  std::cout << "               ";
  std::cout << "Number of vectors: ";
  std::cout << s.vectors / (1.0 * s.buckets);
  std::cout << " /bucket" << std::endl;
}

void print_results(const std::vector<vector>& fs) {
  unsigned int fn = 0;

  for (unsigned int i = 0; i < qn; i++) {
    vector q = qs[i];
    vector t = gt[i];

    if (vector::distance(q, t) <= r) {
      vector f = fs[i];

      if (f.size() == 0 || vector::distance(q, f) > r) {
        fn++;
      }
    }
  }

  std::cout << "                 ";
  std::cout << "False negatives: ";
  std::cout << fn / (1.0 * qn);
  std::cout << " /query" << std::endl;
}

BENCHMARK(table, insert_linear, runs, vn / runs) {
  unsigned int i = vi++ % vn;

  t_lin.insert(vs[i]);
}

BENCHMARK(table, insert_classic, runs, vn / runs) {
  unsigned int i = vi++ % vn;

  t_cla.insert(vs[i]);

  if (i == vn - 1) {
    print_stats(t_cla);
  }
}

BENCHMARK(table, insert_covering, runs, vn / runs) {
  unsigned int i = vi++ % vn;

  t_cov.insert(vs[i]);

  if (i == vn - 1) {
    print_stats(t_cov);
  }
}

BENCHMARK(table, query_linear, runs, qn / runs) {
  unsigned int i = qi++ % qn;

  vector q = qs[i];
  vector r = t_lin.query(q);

  gt.push_back(r);
}

std::vector<vector> vf_cla;

BENCHMARK(table, query_classic, runs, qn / runs) {
  unsigned int i = qi++ % qn;

  vector q = qs[i];
  vector t = gt[i];

  vf_cla.push_back(t_cla.query(q));

  if (i == qn - 1) {
    print_results(vf_cla);
  }
}

std::vector<vector> vf_cov;

BENCHMARK(table, query_covering, runs, qn / runs) {
  unsigned int i = qi++ % qn;

  vector q = qs[i];
  vector t = gt[i];

  vf_cov.push_back(t_cov.query(q));

  if (i == qn - 1) {
    print_results(vf_cov);
  }
}
