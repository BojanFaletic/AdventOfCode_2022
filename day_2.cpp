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

enum Moves { rock, paper, scissors };
enum Outcomes { lose, draw, win };
const int WIN_SCORE = 6;
const int DRAW_SCORE = 3;


void assign_moves_player_1(char a, Moves &player_1) {
  if (a == 'A') {
    player_1 = rock;
  } else if (a == 'B') {
    player_1 = paper;
  } else if (a == 'C') {
    player_1 = scissors;
  } else {
    cerr << "unable to decode player_1";
  }
}

void assign_outcomes_player_2(char b, Outcomes &player_2) {
  if (b == 'X') {
    player_2 = lose;
  } else if (b == 'Y') {
    player_2 = draw;
  } else if (b == 'Z') {
    player_2 = win;
  } else {
    cerr << "unable to decode player_2";
  }
}

namespace part_one {
void assign_moves_player_2(char b, Moves &player_2) {
  if (b == 'X') {
    player_2 = rock;
  } else if (b == 'Y') {
    player_2 = paper;
  } else if (b == 'Z') {
    player_2 = scissors;
  } else {
    cerr << "unable to decode player_2";
  }
}

int match(Moves player_1, Moves player_2) {
  int score = 0;
  if (player_2 == rock) {
    score += 1;
    if (player_1 == scissors)
      score += WIN_SCORE;
    else if (player_1 == rock) {
      score += DRAW_SCORE;
    }
  }

  if (player_2 == paper) {
    score += 2;
    if (player_1 == rock)
      score += WIN_SCORE;
    else if (player_1 == paper) {
      score += DRAW_SCORE;
    }
  }

  if (player_2 == scissors) {
    score += DRAW_SCORE;
    if (player_1 == paper)
      score += WIN_SCORE;
    else if (player_1 == scissors) {
      score += DRAW_SCORE;
    }
  }
  return score;
}

int solution(ifstream &in) {
  string line;
  int score = 0;
  while (getline(in, line)) {
    char a, b;
    sscanf(line.c_str(), "%c %c", &a, &b);

    Moves player_1, player_2;
    assign_moves_player_1(a, player_1);
    assign_moves_player_2(b, player_2);

    score += match(player_1, player_2);
  }
  return score;
}

void test() {
  ifstream input = get_file("../inputs/day_2_test.txt");
  auto out = solution(input);
  EXPECT_EQ(out, 15);
}

void program() {
  ifstream input = get_file("../inputs/day_2.txt");
  auto out = solution(input);
  cout << "Solution: " << out << '\n';
  EXPECT_EQ(out, 12276);
}
}; // namespace part_one

namespace part_two {

int reverse_match(Moves &player_1, Outcomes &player_2) {
  int score = 0;
  if (player_2 == lose) {
    score += (player_1 + 2) % DRAW_SCORE + 1;
  }
  if (player_2 == win) {
    score += (player_1 + 1) % DRAW_SCORE + 1 + 6;
  }

  if (player_2 == draw) {
    score += (player_1 + 1) + DRAW_SCORE;
  }
  return score;
}

int solution(ifstream &in) {
  string line;
  int score = 0;
  while (getline(in, line)) {
    char a, b;
    sscanf(line.c_str(), "%c %c", &a, &b);

    Moves player_1;
    Outcomes player_2;
    assign_moves_player_1(a, player_1);
    assign_outcomes_player_2(b, player_2);

    score += reverse_match(player_1, player_2);
  }
  return score;
}

void test() {
  ifstream input = get_file("../inputs/day_2_test.txt");
  auto out = solution(input);
  EXPECT_EQ(out, 12);
}

void program() {
  ifstream input = get_file("../inputs/day_2.txt");
  auto out = solution(input);
  cout << "Solution: " << out << '\n';
  EXPECT_EQ(out, 9975);
}
}; // namespace part_two

int main() {
  part_one::test();
  part_one::program();

  part_two::test();
  part_two::program();
  return 0;
}