#include <algorithm>
#include <array>
#include <cassert>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <numeric>
using namespace std;

ifstream get_file(string file) {
  ifstream data{file};
  if (!data.is_open()) {
    cerr << "Unable to find file\n";
    exit(1);
  }
  return data;
}

namespace part_one {
int solution(ifstream &in) {
  long accum = 0;
  long largest_elf = 0;
  string line;
  while (getline(in, line, '\n')){
    if (line.size() == 0) {
      if (largest_elf < accum) {
        largest_elf = accum;
      }
      accum = 0;
    } else {
      accum += stoi(line);
    }
  }
  if (largest_elf < accum) {
    largest_elf = accum;
  }
  return largest_elf;
}

void test() {
  ifstream input = get_file("../inputs/day_1_test.txt");
  auto out = solution(input);
  assert(out == 24000);
}

void program() {
  ifstream input = get_file("../inputs/day_1.txt");
  auto out = solution(input);
  cout << "Solution: " << out << '\n';
}
}; // namespace part_one

namespace part_two {
const int N_TOP_ELVES = 3;

int solution(ifstream &in) {
  long accum = 0;
  array<long, N_TOP_ELVES> largest_elf = {0};
  string line;

  auto process_accum = [&]() {
    if (largest_elf[0] < accum) {
      largest_elf[0] = accum;
      sort(largest_elf.begin(), largest_elf.end());
    }
  };
  while (getline(in, line, '\n')) {
    if (line.size() == 0) {
      process_accum();
      accum = 0;
    } else {
      accum += stoi(line);
    }
  }
  process_accum();
  long sum = accumulate(largest_elf.begin(), largest_elf.end(), 0);
  return sum;
}

void test() {
  ifstream input = get_file("../inputs/day_1_test.txt");
  auto out = solution(input);
  assert(out == 45000);
}

void program() {
  ifstream input = get_file("../inputs/day_1.txt");
  auto out = solution(input);
  cout << "Solution: " << out << '\n';
}
}; // namespace part_two

int main() {
  part_one::test();
  part_one::program();

  part_two::test();
  part_two::program();
  return 0;
}