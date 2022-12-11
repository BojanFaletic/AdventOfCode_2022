#include <bits/stdc++.h>
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

auto solve_part_2(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  using interval = pair<int, int>;
  interval a, b;

  int score = 0;
  while (getline(input, line)) {
    // 78-83,81-99
    sscanf(line.c_str(), "%d-%d,%d-%d", &a.first, &a.second, &b.first,
           &b.second);

    interval &first = (a.first <= b.first) ? a : b;
    interval &second = (a.first <= b.first) ? b : a;

    if (first.second >= second.first) {
      score++;
    }
  }
  return score;
}

auto solve_part_1(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  using interval = pair<int, int>;
  interval a, b;

  int score = 0;
  while (getline(input, line)) {
    // 78-83,81-99
    sscanf(line.c_str(), "%d-%d,%d-%d", &a.first, &a.second, &b.first,
           &b.second);

    // check if interval is in range
    int a_size = a.second - a.first;
    int b_size = b.second - b.first;

    interval &smaller = (a_size < b_size) ? a : b;
    interval &larger = (a_size < b_size) ? b : a;

    if (larger.first <= smaller.first && larger.second >= smaller.second) {
      score++;
    }
  }
  return score;
}

int main() {
  string const test_file = "../inputs/day_4_test.txt";
  string const deploy_file = "../inputs/day_4.txt";

  const bool USE_PART_1 = false;
  const bool USE_PART_2 = true;

  if (USE_PART_1) {
    auto out_test = solve_part_1(test_file);
    EXPECT_EQ(out_test, 2);

    auto out_sol = solve_part_1(deploy_file);
    cout << "Part 1 solution: " << out_sol << '\n';
  }

  if (USE_PART_2) {
    auto out_test = solve_part_2(test_file);
    EXPECT_EQ(out_test, 4);

    auto out_sol = solve_part_2(deploy_file);
    cout << "Part 2 solution: " << out_sol << '\n';
  }
  return 0;
}