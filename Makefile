# Компилятор
CXX := g++
# Флаги компиляции
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Исходные файлы
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,obj/%.o,$(SRCS))

# Имя исполняемого файла
TARGET := blog_program

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS) obj/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Компиляция main.cpp
obj/main.o: main.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция .cpp файлов из src
obj/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf obj $(TARGET)

.PHONY: all clean
