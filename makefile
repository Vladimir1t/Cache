TARGET = ./cache.x
CC = g++

FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat \
		-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion \
		-Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness \
		-Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith \
		-Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
		-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
		-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
		-fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
		-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla 

CSRC = src/cache/cpp main.cpp
COBJ = $(CSRC : %.c = %.o)

test_data : test_big_data.o
	$(CC) test_big_data.o -o test_data.x

all : main.o tests.o
	$(CC) main.o tests.o -I./include -o $(TARGET)
	$(TARGET)

main.o : main.cpp
	$(CC) $(FLAGS) -I./include -c main.cpp

test_big_data.o : src/test_big_data.cpp
	$(CC) $(FLAGS) -c src/test_big_data.cpp

tests.o : src/tests.cpp
	$(CC) $(FLAGS) -I./include -c src/tests.cpp

.PHONY clear :
	rm -rf *.o *.log *.x
