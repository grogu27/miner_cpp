#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Board {
 private:
  struct Cell {
    bool is_opened = false;
    bool has_flag = false;
    bool has_mine = false;
    size_t mines_count = 0;
  };

  int rows_, cols_;
  std::vector<std::vector<Cell>> field_;

 public:
  Board(int rows,
        int cols,
        const std::vector<std::pair<int, int>>& mine_coordinates);
  void open(int row, int col);
  void flag(int row, int col);
  void print() const;
  int get_rows() const;
  int get_cols() const;
  bool is_opened(int row, int col) const;
  bool has_mine(int row, int col) const;
  bool has_flag(int row, int col) const;
  size_t mines_count(int row, int col) const;
};
