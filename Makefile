CXX      := g++
CXXFLAGS := -std=c++23 -Wall -Wextra
SRC_DIR  := src
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
TARGET   := main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) results.csv results.png

venv: graph/requirements.txt
	python3 -m venv graph/.venv
	graph/.venv/bin/pip install -q -r graph/requirements.txt

benchmark: $(TARGET)
	./$(TARGET)

graph: venv benchmark
	graph/.venv/bin/python graph/plot.py

.PHONY: all run clean venv benchmark graph compile_commands.json
