#include "util.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <list>
#include <regex>
using namespace std;

ifstream get_file(string file)
{
  ifstream data{file};
  if (!data.is_open())
  {
    cerr << "Unable to find file\n";
    exit(1);
  }
  return data;
}

template <typename T>
void EXPECT_EQ(T num, T expected)
{
  if (num != expected)
  {
    cerr << "Expected: " << expected << " received: " << num << '\n';
  }
}

class Dir
{
public:
  Dir *parent = nullptr;

  string name;
  vector<Dir> folders;
  vector<pair<int, string>> files;

  Dir() = default;

  Dir(string name) : name{name}, parent{nullptr} {}
  Dir(string name, Dir *parent) : name{name}, parent{parent} {}

  void add_dir(string name, Dir *self) { folders.push_back(Dir(name, self)); }

  void add_file(int size, string name) { files.push_back({size, name}); }

  int size()
  {
    int sz = 0;
    for_each(files.begin(), files.end(), [&sz](auto f)
             { sz += f.first; });
    return sz;
  }

  int total_size(){
    vector<Dir> map;
    map_all_dir(map);

    int sz = size();
    for (Dir &d : map){
      sz += d.size();
    }
    return sz;
  }

  void map_all_dir(vector<Dir> &d){
    for (Dir &dd : folders){
      d.push_back(dd);
      dd.map_all_dir(d);
    }
  }
};

class FileSystem{
  Dir base;
  Dir *current_dir = &base;
  public:

  void add_directory(string name){
    current_dir->add_dir(name, current_dir);
  }

  void add_file(int size, string name){
    current_dir->add_file(size, name);
  }

  vector<Dir> &ls(){
    return current_dir->folders;
  }

  int size(){
    return current_dir->size();
  }


  int size(int threshold){
    vector<Dir> tmp;
    current_dir->map_all_dir(tmp);
    int cnt = 0;
    for (auto f : tmp){
      int sz = f.total_size();
      if (sz >= threshold){
        sz = 0;
      }
      cnt += sz;
    }
    return cnt;
  }

  void tree(){
    vector<Dir> tmp;
    vector<pair<string, int>> summary;
    current_dir->map_all_dir(tmp);
    for (auto f : tmp){
      int sz = f.total_size();
      summary.push_back({f.name, sz});
    }

    int full_size = 70000000;
    int candidate = 30000000;
    vector<pair<string, int>> in_range;
    for (auto el: summary){
      //cout << el.first << " : " << el.second << '\n';
      cout << "Remaining: " << full_size - el.second << " : "<< el.first << '\n';
      if (full_size - el.second < candidate){
        in_range.push_back(el);
      }
    }
    sort(in_range.begin(), in_range.end(), [](auto a, auto b) {return a.second < b.second;});
    for (auto el : in_range){
      cout << el.first << " : " << el.second << '\n';
    }
  }

  void cd(string cmd)
  {
    if (cmd == "/")
    {
      current_dir = &base;
      return;
    }
    if (cmd == "..")
    {
      current_dir = (current_dir->parent != nullptr) ? current_dir->parent : &base;
      return;
    }
    for (auto &el : current_dir->folders)
    {
      if (el.name == cmd)
      {
        current_dir = &el;
        return;
      }
    }
    cout << "Unknown cmd\n";
  }
};

void process_line(vector<string> lines, FileSystem &fs)
{
  for (int i = 0; i < lines.size(); i++)
  {
    string &line = lines[i];
    smatch sm;

    if (line[0] != '$')
    {
      // instruction
      if (regex_match(line, sm, regex("dir (\\w+)")))
      {
        fs.add_directory(sm[1]);
      }
      if (regex_match(line, sm, regex("(\\d+) (.*)")))
      {
        fs.add_file(stoi(sm[1]), sm[2]);
      }
    }
    else
    {
      if (regex_match(line, sm, regex("\\$ cd (.*)")))
      {
        fs.cd(sm[1]);
      }
    }
  }
}

auto solve_part_1(string file_name)
{
  ifstream input = get_file(file_name);

  string line;
  const int n_same = 4;
  list<char> buff;
  vector<string> s_lines;
  while (getline(input, line))
  {
    s_lines.push_back(line);
  }
  FileSystem fs;
  process_line(s_lines, fs);

  // calculate size
  fs.cd("/");
  return fs.size(100000);
}

auto solve_part_2(string file_name)
{
  ifstream input = get_file(file_name);

  string line;
  const int n_same = 4;
  list<char> buff;
  vector<string> s_lines;
  while (getline(input, line))
  {
    s_lines.push_back(line);
  }
  FileSystem fs;
  process_line(s_lines, fs);

  // calculate size
  fs.cd("/");
  fs.tree();
  return -1;
}

int main()
{
  string const test_file = "../inputs/day_7_test.txt";
  string const deploy_file = "../inputs/day_7.txt";

  const bool USE_PART_1 = false;
  const bool USE_PART_2 = true;

  if (USE_PART_1)
  {
    auto out_test = solve_part_1(test_file);
    EXPECT_EQ(out_test, 95437);

    auto out_sol = solve_part_1(deploy_file);
    cout << "Part 1 solution: " << out_sol << '\n';
  }

  if (USE_PART_2)
  {
    auto out_test = solve_part_2(test_file);
    EXPECT_EQ(out_test, 19);

    //auto out_sol = solve_part_2(deploy_file);
    //cout << "Part 2 solution: " << out_sol << '\n';
  }
  return 0;
}