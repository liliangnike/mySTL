CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

TESTS = test_vector test_list test_stack test_queue test_tree test_hashmap
PRACTICE = algo_practice container_practice modern_cpp

TEST_BINS = $(addsuffix $(EXE),$(TESTS))
PRACTICE_BINS = $(addsuffix $(EXE),$(PRACTICE))

.PHONY: all test practice clean

all: $(TESTS) $(PRACTICE)

test_vector: tests/test_vector.cpp include/my_vector.h
	$(CXX) $(CXXFLAGS) tests/test_vector.cpp -o $@

test_list: tests/test_list.cpp include/my_list.h
	$(CXX) $(CXXFLAGS) tests/test_list.cpp -o $@

test_stack: tests/test_stack.cpp include/my_stack.h include/my_vector.h
	$(CXX) $(CXXFLAGS) tests/test_stack.cpp -o $@

test_queue: tests/test_queue.cpp include/my_queue.h include/my_list.h
	$(CXX) $(CXXFLAGS) tests/test_queue.cpp -o $@

test_tree: tests/test_tree.cpp include/my_tree.h
	$(CXX) $(CXXFLAGS) tests/test_tree.cpp -o $@

test_hashmap: tests/test_hashmap.cpp include/my_hashmap.h
	$(CXX) $(CXXFLAGS) tests/test_hashmap.cpp -o $@

algo_practice: stl_practice/algo_practice.cpp
	$(CXX) $(CXXFLAGS) stl_practice/algo_practice.cpp -o $@

container_practice: stl_practice/container_practice.cpp
	$(CXX) $(CXXFLAGS) stl_practice/container_practice.cpp -o $@

modern_cpp: stl_practice/modern_cpp.cpp
	$(CXX) $(CXXFLAGS) stl_practice/modern_cpp.cpp -o $@

test: $(TESTS)
	./test_vector$(EXE)
	./test_list$(EXE)
	./test_stack$(EXE)
	./test_queue$(EXE)
	./test_tree$(EXE)
	./test_hashmap$(EXE)

practice: $(PRACTICE)
	./algo_practice$(EXE)
	./container_practice$(EXE)
	./modern_cpp$(EXE)

clean:
	rm -f $(TEST_BINS) $(PRACTICE_BINS)

