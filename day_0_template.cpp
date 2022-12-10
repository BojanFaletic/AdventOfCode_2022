#include <algorithm>
#include <array>
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

void EXPECT_EQ(size_t num, size_t expected) {
  if (num != expected) {
    cerr << "Expected: " << num << " received: " << expected << '\n';
  }
}

int solve_part_1(string file_name) {
  ifstream input = get_file(file_name);
  int score = 0;

  return score;
}

int solve_part_2(string file_name) {
  ifstream input = get_file(file_name);
  int score = 0;

  return score;
}

int main() {
  string const test_file = "../inputs/day_x_test.txt";
  string const deploy_file = "../inputs/day_x.txt";

  const bool USE_PART_1 = true;
  const bool USE_PART_2 = true;

  if (USE_PART_1) {
    int out = solve_part_1(test_file);
    // EXPECT_EQ(1, 15);

    int out = solve_part_1(test_file);
    cout << "Part 1 solution: " << out << '\n';
  }

  if (USE_PART_2) {
    int out = solve_part_2(test_file);
    // EXPECT_EQ(1, 15);

    int out = solve_part_2(test_file);
    cout << "Part 2 solution: " << out << '\n';
  }
  return 0;
}