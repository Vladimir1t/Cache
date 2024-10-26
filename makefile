TARGET = ./cache.x
CXX = g++

CSRC = src/cache/cpp main.cpp
COBJ = $(CSRC : %.c = %.o)

all : main.o ideal_cache.o
	$(CXX) main.o -I./include -o $(TARGET)
	$(CXX) ideal_cache.o -I./include -o ideal_cache.x

test : tests.o
	$(CXX) tests.o -I./include -o test.x

ideal_cache : ideal_cache.o
	$(CXX) ideal_cache.o -I./include -o ideal_cache.x

test_big_data : test_big_data.o
	$(CXX) test_big_data.o -o test_big_data.x

ideal_cache.o : src/ideal_cache.cpp
	$(CXX) -std=c++20 -O2 -I./include -D NDEBUG -c src/ideal_cache.cpp

tests.o : src/tests.cpp
	$(CXX) -std=c++20 -O2 -I./include -D NDEBUG -c src/tests.cpp

main.o : main.cpp
	$(CXX) -std=c++20 -O2 -I./include -D NDEBUG -c main.cpp

test_big_data.o : src/test_big_data.cpp
	$(CXX) -std=c++20 -O2 -D NDEBUG -c src/test_big_data.cpp

.PHONY clear :
	rm -rf *.o *.log *.x
