
all: test
	./test

test: test.o field.o record.o document.o
	g++ test.o field.o record.o document.o -o test

test.o: test.cc
	g++ -c -std=c++11 test.cc

document.o: document.cc
	g++ -c -std=c++11 document.cc

record.o: record.cc
	g++ -c -std=c++11 record.cc

field.o: field.cc field.h
	g++ -c -std=c++11 field.cc

clean:
	rm *.o test
