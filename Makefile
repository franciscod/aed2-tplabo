all: clean tests

clean:
	rm -f tests

tests:
	g++ -g -o tests -Wall -fmessage-length=0 tests.cpp
	./tests

valgrind: all
	valgrind --leak-check=full ./tests
