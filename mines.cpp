#include "Board.hpp"

bool isNumber(const std::string& str) {
  if (str.empty())
    return false;
  for (const char c : str) {
    if (!std::isdigit(c))
      return false;
  }
  return true;
}

void parse_arg(const std::string& input,
               std::string& command,
               int& row,
               int& col) {
  std::istringstream iss(input);
  std::string command_buf;
  std::string rowStr, colStr;
  command.clear();
  iss >> command_buf >> rowStr >> colStr;
  if (command_buf == "open" || command_buf == "flag" || command_buf == "exit")
    command = command_buf;
  if (isNumber(rowStr) && isNumber(colStr)) {
    row = std::stoi(rowStr);
    col = std::stoi(colStr);
  }
}

bool is_game_over(const Board& board) {
  for (int row = 0; row < board.get_rows(); ++row) {
    for (int col = 0; col < board.get_cols(); ++col) {
      if (board.is_opened(row, col) && board.has_mine(row, col)) {
        return true;
      }
    }
  }
  return false;
}

bool is_won(const Board& board) {
  for (int row = 0; row < board.get_rows(); ++row) {
    for (int col = 0; col < board.get_cols(); ++col) {
      if (!board.is_opened(row, col) && !board.has_mine(row, col)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int rows, cols, mines;

  std::cout << "Введите количество строк и столбцов в игровом поле:" << '\n';
  std::cin >> rows >> cols;
  if (rows <= 0 || cols <= 0) {
    std::cerr
        << "Ошибка: количество строк и столбцов должно быть положительным."
        << '\n';
    return 1;
  }

  std::cout << "Введите количество мин (< размера поля):" << '\n';
  std::cin >> mines;
  if (mines < 0 || mines >= rows * cols) {
    std::cerr << "Ошибка: количество мин должно быть неотрицательным и меньше "
                 "размера поля."
              << '\n';
    return 1;
  }

  std::vector<std::pair<int, int>> mine_coordinates;
  std::cout << "Введите координаты мин в формате «номер_строки номер_столбца»:"
            << '\n';
  for (int i = 0; i < mines; ++i) {
    int mine_row, mine_col;
    std::cin >> mine_row >> mine_col;
    if (mine_row < 0 || mine_row >= rows || mine_col < 0 || mine_col >= cols) {
      std::cerr << "Ошибка: координаты мин должны быть в пределах поля."
                << '\n';
      return 1;
    }
    mine_coordinates.push_back({mine_row, mine_col});
  }

  Board board(rows, cols, mine_coordinates);
  board.print();

  std::string input;
  std::string command;
  int row, col;
  std::cin.ignore();
  while (true) {
    std::cout << "Введите команду: ";
    std::getline(std::cin, input);
    parse_arg(input, command, row, col);

    if (command == "exit")
      break;
    if (command == "open" && row != -1 && col != -1) {
      board.open(row, col);
    } else if (command == "flag" && row != -1 && col != -1) {
      board.flag(row, col);
    } else {
      std::cerr << "Ошибка: Неверная команда или параметры." << '\n';
      continue;
    }

    board.print();

    if (is_game_over(board)) {
      std::cout << "You lose!" << '\n';
      break;
    } else if (is_won(board)) {
      std::cout << "You win!" << '\n';
      break;
    }
  }
  return 0;
}