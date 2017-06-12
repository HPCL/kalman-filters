CC = g++

all: data_gen test_gen
	./a.out

test_gen:
	$(CC) test_data_generator.cpp data_generator.o

data_gen: data_generator.cpp data_generator.hpp
	$(CC) -c data_generator.cpp



clean:
	rm -f *.o *.out *.csv