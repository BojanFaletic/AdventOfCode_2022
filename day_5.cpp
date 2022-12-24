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
    cerr << "Expected: " << num << " received: " << expected << '\n';
  }
}

vector<char> single_line(string &line) {
  int state = 0;
  int count_spaces = 0;
  vector<char> out;
  for (char ch : line) {
    if (state == 0) {
      if (ch == ' ') {
        count_spaces++;
        if (count_spaces == 4) {
          out.push_back(' ');
          count_spaces = 0;
        }
      }
      if (ch == '[') {
        count_spaces = 0;
        state = 1;
      }
    } else if (state == 1) {
      out.push_back(ch);
      state = 2;
    } else if (state == 2) {
      if (ch == ']') {
        state = 0;
      } else {
        cerr << "error\n";
      }
    }
  }
  return out;
}

void move_column(array<int, 3> &inst, vector<vector<char>> &col) {
  auto [size, from, to] = inst;
  int from_idx = from - 1;
  int to_idx = to - 1;

  for (int i = 0; i < size; i++) {
    if (col[from_idx].size() != 0) {
      int tmp = col[from_idx].back();
      col[from_idx].pop_back();
      col[to_idx].push_back(tmp);
    }
  }
}

void move_column_9001(array<int, 3> &inst, vector<vector<char>> &col) {
  auto [size, from, to] = inst;
  int from_idx = from - 1;
  int to_idx = to - 1;

  stack<char> buff;
  for (int i = 0; i < size; i++) {
    if (col[from_idx].size() != 0) {
      int tmp = col[from_idx].back();
      col[from_idx].pop_back();
      buff.push(tmp);
    }
  }

  for (int i = 0; i < size; i++) {
    while (buff.size() != 0){
      col[to_idx].push_back(buff.top());
      buff.pop();
    }
  }
}

void pad_vector(vector<vector<char>> &v) {
  size_t vector_len = 0;
  for (vector<char> const &c : v) {
    if (c.size() > vector_len) {
      vector_len = c.size();
    }
  }

  for (vector<char> &c : v) {
    for (int i = c.size(); i < vector_len; i++) {
      c.push_back(' ');
    }
  }
}

void transpose(vector<vector<char>> &v) {
  vector<vector<char>> transposed;
  for (size_t j = 0; j < v[0].size(); j++) {
    vector<char> tmp;
    for (size_t i = 0; i < v.size(); i++) {
      char el = v[v.size() - i - 1][j];
      if (el != ' ') {
        tmp.push_back(el);
      }
    }
    transposed.push_back(tmp);
  }
  swap(v, transposed);
}

auto solve_part_1(string file_name) {
  ifstream input = get_file(file_name);

  string line;
  int is_instruction = false;
  vector<vector<char>> map;
  while (getline(input, line)) {

    if (!is_instruction) {
      for (char ch : line) {
        if (isdigit(ch)) {
          is_instruction = true;
          break;
        }
      }
      if (!is_instruction) {
        // decode single line
        map.push_back(single_line(line));
      } else {
        // process input stack
        pad_vector(map);
        transpose(map);
      }
    }
    else {
      smatch sm;
      if (regex_match(line, sm, regex("move (\\d+) from (\\d+) to (\\d+)"))) {
        array<int, 3> instruction{stoi(sm[1]), stoi(sm[2]), stoi(sm[3])};
        move_column(instruction, map);
      }
    }
  }

  string msg = "";
  for (vector<char> const &el : map) {
    msg += el.back();
  }

  return msg;
}

auto solve_part_2(string file_name) {
    ifstream input = get_file(file_name);

  string line;
  int is_instruction = false;
  vector<vector<char>> map;
  while (getline(input, line)) {

    if (!is_instruction) {
      for (char ch : line) {
        if (isdigit(ch)) {
          is_instruction = true;
          break;
        }
      }
      if (!is_instruction) {
        // decode single line
        map.push_back(single_line(line));
      } else {
        // process input stack
        pad_vector(map);
        transpose(map);
      }
    }
    else {
      smatch sm;
      if (regex_match(line, sm, regex("move (\\d+) from (\\d+) to (\\d+)"))) {
        array<int, 3> instruction{stoi(sm[1]), stoi(sm[2]), stoi(sm[3])};
        move_column_9001(instruction, map);
      }
    }
  }

  string msg = "";
  for (vector<char> const &el : map) {
    msg += el.back();
  }

  return msg;
}

int main() {
  string const test_file = "../inputs/day_5_test.txt";
  string const deploy_file = "../inputs/day_5.txt";

  const bool USE_PART_1 = true;
  const bool USE_PART_2 = true;

  if (USE_PART_1) {
    auto out_test = solve_part_1(test_file);
    EXPECT_EQ(out_test, string("CMZ"));

    auto out_sol = solve_part_1(deploy_file);
    cout << "Part 1 solution: " << out_sol << '\n';
    EXPECT_EQ(out_sol, string("TQRFCBSJJ"));
  }

  if (USE_PART_2) {
    auto out_test = solve_part_2(test_file);
    EXPECT_EQ(out_test, string("MCD"));

    auto out_sol = solve_part_2(deploy_file);
    cout << "Part 2 solution: " << out_sol << '\n';
  }
  return 0;
}