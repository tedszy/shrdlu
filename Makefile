all: field_test record_test document_test
	./field_test && ./record_test && ./document_test

document_test: document.o record.o field.o document_test.o
	g++ document.o field.o record.o document_test.o -o document_test

document_test.o: document_test.cc
	g++ -c -std=c++11 document_test.cc

document.o: document.cc
	g++ -c -std=c++11 document.cc

record_test: record.o field.o record_test.o
	g++ record.o field.o record_test.o -o record_test

record_test.o: record_test.cc
	g++ -c -std=c++11 record_test.cc

record.o: record.cc
	g++ -c -std=c++11 record.cc

field_test: field.o testing.o field_test.o
	g++ field.o field_test.o testing.o -o field_test

field.o: field.cc field.h
	g++ -c -std=c++11 field.cc

field_test.o: field_test.cc testing.h field.h
	g++ -c -std=c++11 field_test.cc

testing.o: testing.cc testing.h
	g++ -c -std=c++11 testing.cc

clean:
	rm *.o field_test record_test document_test
