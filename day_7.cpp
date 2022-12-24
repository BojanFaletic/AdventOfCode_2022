#include "util.hpp"
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

class Dir {
  Dir *parent = NULL;

public:
  string name;
  vector<Dir> folders;
  vector<pair<int, string>> files;

  Dir() = default;
  Dir(string name) : name{name} {}
  Dir(string name, Dir *parent) : name{name}, parent{parent} {}

  void add_dir(string name) { folders.push_back(Dir(name, this)); }

  void add_file(int size, string name) { files.push_back({size, name}); }

  int size() {
    int sz = 0;
    for_each(files.begin(), files.end(), [&sz](auto f) { sz += f.first; });
    return sz;
  }

  Dir &cd(string cmd) {
    if (cmd == "/") {
      Dir *tmp = this;
      while (tmp->parent != NULL) {
        tmp = tmp->parent;
      }
      return *tmp;
    } else if (cmd == "..") {
      return *parent;
    } else {
      for (auto &el : folders) {
        if (el.name == cmd) {
          return el;
        }
      }
    }

    return *this;
  }

  Dir &back() { return *parent; }
};

void process_line(vector<string> lines, Dir &directory) {
  for (int i = 0; i < lines.size(); i++) {
    string &line = lines[i];
    smatch sm;

    if (line[0] != '$') {
      // instruction
      if (regex_match(line, sm, regex("dir (\\w+)"))) {
        directory.add_dir(sm[1]);
      }
      if (regex_match(line, sm, regex("(\\d+) (\\w+\\.\\w+)"))) {
        directory.add_file(stoi(sm[1]), sm[2]);
      }
    } else {
      if (regex_match(line, sm, regex("\\$ cd (.*)"))) {
        directory = directory.cd(sm[1]);
      }
    }
  }
}

auto solve_part_1(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  const int n_same = 4;
  list<char> buff;
  vector<string> s_lines;
  while (getline(input, line)) {
    s_lines.push_back(line);
  }
  Dir dir;
  process_line(s_lines, dir);

  // calculate size
  dir = dir.cd("/");
  for (auto &el : dir.folders){
    cout << el.name << " " << el.size() << '\n';
  }
  return -1;
}

auto solve_part_2(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  const int n_same = 14;
  list<char> buff;
  while (getline(input, line)) {
  }
  return -1;
}

int main() {
  string const test_file = "../inputs/day_7_test.txt";
  string const deploy_file = "../inputs/day_7.txt";

  const bool USE_PART_1 = true;
  const bool USE_PART_2 = false;

  if (USE_PART_1) {
    auto out_test = solve_part_1(test_file);
    EXPECT_EQ(out_test, 95437);

    // auto out_sol = solve_part_1(deploy_file);
    // cout << "Part 1 solution: " << out_sol << '\n';
  }

  if (USE_PART_2) {
    auto out_test = solve_part_2(test_file);
    EXPECT_EQ(out_test, 19);

    auto out_sol = solve_part_2(deploy_file);
    cout << "Part 2 solution: " << out_sol << '\n';
  }
  return 0;
}