MARKDOWN = pandoc --from markdown_github --to html 

all: record_test
	./record_test

record_test: record_test.o record.o field.o testing.o 
	g++ record.o field.o testing.o record_test.o -o record_test

record.o: record.cc record.h
	g++ -c -std=c++11 record.cc

record_test.o: record_test.cc 
	g++ -c -std=c++11 record_test.cc

field_test: field.o testing.o field_test.o
	g++ field.o field_test.o testing.o -o field_test

field.o: field.cc field.h
	g++ -c -std=c++11 field.cc

field_test.o: field_test.cc testing.h field.h
	g++ -c -std=c++11 field_test.cc

testing.o: testing.cc testing.h
	g++ -c -std=c++11 testing.cc

doc: README.md
	$(MARKDOWN) $< --output README.html

clean:
	rm *.html *.o main field_test record record_test
