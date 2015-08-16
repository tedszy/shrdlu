MARKDOWN = pandoc --from markdown_github --to html 

all: field_test 
	./field_test

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
	rm *.o field_test record_test
