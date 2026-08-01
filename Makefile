CXX			:= g++
CXXFLAGS	:= -Wall -Wextra -std=c++17 -g -O2 -Iinclude

TESTS := tests/test_vector

PRACTICES := stl_practice/algo_practice

.PHONY: all test practice clean

all: test practice

test: $(TESTS)
	@echo "\n=== Running Tests ==="
	@for t in $(TESTS); do ./$$t; done

practice: $(PRACTICES)
	@echo "\n=== Running STL Practice ==="
	@for p in $(PRACTICES); do ./$$p; done

tests/test_vector: tests/test_vector.cpp include/my_vector.h
	$(CXX) $(CXXFLAGS) $< -o $@

stl_practice/algo_practice: stl_practice/algo_practice.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TESTS) $(PRACTICES)
	@echo ">>> Cleaned"
