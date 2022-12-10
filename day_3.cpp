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

int solve_part_2(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  int i = 0;
  const int N_GROUPS = 3;
  array<string, N_GROUPS> group;
  vector<char> solutions;
  while (getline(input, line)) {
    group[i] = line;
    if (i == N_GROUPS - 1) {
      array<unordered_map<char, int>, N_GROUPS> hist;
      unordered_set<char> candidates;

      // make histograms for all characters in groups
      for (size_t j = 0; j < N_GROUPS; j++) {
        for (char ch : group[j]) {
          hist[j][ch]++;
          candidates.insert(ch);
        }
      }

      // find specific item in all groups
      for (char ch : candidates) {
        bool is_common = true;
        for (auto s : hist) {
          is_common &= s[ch] != 0;
        }
        if (is_common) {
          solutions.push_back(ch);
        }
      }
    }
    i++;
    i %= N_GROUPS;
  }

  int score = 0;
  for (char ch : solutions) {
    score += (isupper(ch)) ? ch - 'A' + 27 : ch - 'a' + 1;
  }

  return score;
}

size_t get_n_unique(string const &st) {
  size_t unique = 1;
  char current_ch = st[0];
  for (size_t i = 1; i < st.size(); i++) {
    if (current_ch != st[i]) {
      unique++;
      current_ch = st[i];
    }
  }
  return unique;
}

auto solve_part_1(string file_name) {
  ifstream input = get_file(file_name);
  vector<char> solution;

  string line;
  while (getline(input, line)) {
    size_t half = line.size() / 2;
    unordered_set<char> full;
    map<char, int> hist_1, hist_2;

    for (size_t i = 0; i < line.size(); i++) {
      char ch = line[i];
      if (i < half) {
        hist_1[ch]++;
      } else {
        hist_2[ch]++;
      }
      full.insert(ch);
    }

    for (char ch : full) {
      if (hist_1[ch] != 0 && hist_2[ch] != 0) {
        solution.push_back(ch);
        break;
      }
    }
  }

  int score = 0;
  for (char ch : solution) {
    score += (isupper(ch)) ? ch - 'A' + 27 : ch - 'a' + 1;
  }

  return score;
}

int main() {
  string const test_file = "../inputs/day_3_test.txt";
  string const deploy_file = "../inputs/day_3.txt";

  const bool USE_PART_1 = false;
  const bool USE_PART_2 = true;

  if (USE_PART_1) {
    auto out_test = solve_part_1(test_file);
    EXPECT_EQ(out_test, 157);

    auto out_sol = solve_part_1(deploy_file);
    cout << "Part 1 solution: " << out_sol << '\n';
  }

  if (USE_PART_2) {
    auto out_test = solve_part_2(test_file);
    EXPECT_EQ(out_test, 70);

    auto out_sol = solve_part_2(deploy_file);
    cout << "Part 2 solution: " << out_sol << '\n';
  }
  return 0;
}