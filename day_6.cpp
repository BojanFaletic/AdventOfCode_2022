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

template <typename T> void EXPECT_EQ(T num, T expected) {
  if (num != expected) {
    cerr << "Expected: " << expected << " received: " << num << '\n';
  }
}

auto solve_part_1(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  const int n_same = 4;
  list<char> buff;
  while (getline(input, line)) {
    int i = 0;
    for (char c : line) {
      if (i >= n_same){
        unordered_map<char, int> hist;
        for (char el : buff){
          hist[el] += 1;
        }

        bool duplicate = false;
        for (auto el : hist){
          if (el.second != 1){
            duplicate = true;
          }
        }
        if (!duplicate){
          return i;
        }
        buff.erase(buff.begin());
      }
      buff.push_back(c);
      i++;
    }
  }
  return -1;
}

auto solve_part_2(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  const int n_same = 14;
  list<char> buff;
  while (getline(input, line)) {
    int i = 0;
    for (char c : line) {
      if (i >= n_same){
        unordered_map<char, int> hist;
        for (char el : buff){
          hist[el] += 1;
        }

        bool duplicate = false;
        for (auto el : hist){
          if (el.second != 1){
            duplicate = true;
          }
        }
        if (!duplicate){
          return i;
        }
        buff.erase(buff.begin());
      }
      buff.push_back(c);
      i++;
    }
  }
  return -1;
}

int main() {
  string const test_file = "../inputs/day_6_test.txt";
  string const deploy_file = "../inputs/day_6.txt";

  const bool USE_PART_1 = false;
  const bool USE_PART_2 = true;

  if (USE_PART_1) {
    auto out_test = solve_part_1(test_file);
    EXPECT_EQ(out_test, 7);

    auto out_sol = solve_part_1(deploy_file);
    cout << "Part 1 solution: " << out_sol << '\n';
  }

  if (USE_PART_2) {
    auto out_test = solve_part_2(test_file);
    EXPECT_EQ(out_test, 19);

    auto out_sol = solve_part_2(deploy_file);
    cout << "Part 2 solution: " << out_sol << '\n';
  }
  return 0;
}