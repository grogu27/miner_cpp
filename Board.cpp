#include "Board.hpp"

Board::Board(int rows,
             int cols,
             const std::vector<std::pair<int, int>>& mine_coordinates)
    : rows_(rows), cols_(cols), field_(rows, std::vector<Cell>(cols)) {
  // Установка мин на поле
  for (const auto& mine : mine_coordinates) {
    const int mine_row = mine.first;
    const int mine_col = mine.second;
    field_[mine_row][mine_col].has_mine = true;

    // Увеличиваем счетчик мин вокруг соседних клеток
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        if (dr == 0 && dc == 0)
          continue;  // Пропустить саму мину
        const int neighbor_row = mine_row + dr;
        const int neighbor_col = mine_col + dc;
        if (neighbor_row >= 0 && neighbor_row < rows_ && neighbor_col >= 0 &&
            neighbor_col < cols_) {
          field_[neighbor_row][neighbor_col].mines_count++;
        }
      }
    }
  }
}

void Board::open(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_ ||
      field_[row][col].is_opened || field_[row][col].has_flag)
    return;

  field_[row][col].is_opened = true;

  if (field_[row][col].has_mine) {
    // Игра проиграна, если открыта клетка с миной
    return;
  }

  // Если в клетке нет мин вокруг, открываем соседние клетки
  if (field_[row][col].mines_count == 0) {
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        if (dr != 0 || dc != 0) {
          open(row + dr, col + dc);
        }
      }
    }
  }
}

void Board::flag(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    return;

  field_[row][col].has_flag = !field_[row][col].has_flag;
}

void Board::print() const {
  for (int row = 0; row < rows_; ++row) {
    for (int col = 0; col < cols_; ++col) {
      const Cell& cell = field_[row][col];
      if (cell.is_opened) {
        if (cell.has_mine) {
          std::cout << "* ";
        } else if (cell.mines_count > 0) {
          std::cout << cell.mines_count << " ";
        } else {
          std::cout << ". ";
        }
      } else if (cell.has_flag) {
        std::cout << "F ";
      } else {
        std::cout << "# ";
      }
    }
    std::cout << '\n';
  }
}
int Board::get_rows() const {
  return rows_;
}

int Board::get_cols() const {
  return cols_;
}
bool Board::has_mine(int row, int col) const {
  return field_[row][col].has_mine;
}

bool Board::has_flag(int row, int col) const {
  return field_[row][col].has_flag;
}

size_t Board::mines_count(int row, int col) const {
  return field_[row][col].mines_count;
}
bool Board::is_opened(int row, int col) const {
  return field_[row][col].is_opened;
}