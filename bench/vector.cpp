#include <vector>
#include "../lib/hayai/hayai.hpp"
#include "../lib/hayai/hayai_posix_main.cpp"
#include "../src/vector.hpp"

using namespace lsh;

std::vector<bool> c(128);

BENCHMARK(vector, vector, 10000, 1000) {
  lsh::vector v(c);
}
