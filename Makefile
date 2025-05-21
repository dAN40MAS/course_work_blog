# Компилятор
CXX := g++

# Флаги компиляции
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Флаги линковки (добавляем JsonCpp)
LDFLAGS := -ljsoncpp

# Пути к JsonCpp (если установлен в нестандартное место)
# JSONCPP_INCLUDE := /path/to/jsoncpp/include
# JSONCPP_LIB := /path/to/jsoncpp/lib

# Если JsonCpp установлен в нестандартное место, раскомментируйте:
# CXXFLAGS += -I$(JSONCPP_INCLUDE)
# LDFLAGS += -L$(JSONCPP_LIB)

# Исходные файлы
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,obj/%.o,$(SRCS))

# Имя исполняемого файла
TARGET := blog_program

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла с линковкой JsonCpp
$(TARGET): $(OBJS) obj/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

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