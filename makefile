TARGET = ./cache.x
CXX = g++

CSRC = src/cache/cpp main.cpp
COBJ = $(CSRC : %.c = %.o)

all : main.o tests.o
	$(CXX) main.o -I./include -o $(TARGET)

test : tests.o
	$(CXX) tests.o -I./include -o test.x

ideal_cache : ideal_cache.o
	$(CXX) ideal_cache.o -I./include -o ideal_cache.x

test_big_data : test_big_data.o
	$(CXX) test_big_data.o -o test_big_data.x

ideal_cache.o : src/ideal_cache.cpp
	$(CXX) -O2 -I./include -c src/ideal_cache.cpp

tests.o : src/tests.cpp
	$(CXX) -O2 -I./include -c src/tests.cpp

main.o : main.cpp
	$(CXX) -O2 -I./include -c main.cpp

test_big_data.o : src/test_big_data.cpp
	$(CXX) -O2 -c src/test_big_data.cpp

.PHONY clear :
	rm -rf *.o *.log *.x
