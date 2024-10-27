CXX = g++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++20

TARGET = mines
OBJECTS = Board.o mines.o

# Правило по умолчанию для сборки исполняемого файла
all: $(TARGET)

# Правило для создания исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для компиляции .cpp файлов в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Правило для форматирования кода
format:
	clang-format -i mines.cpp Board.cpp Board.hpp

# Правило для очистки файлов
clean:
	rm -f $(OBJECTS) $(TARGET)
