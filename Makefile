MARKDOWN = pandoc --from markdown_github --to html 

all: field_test
	./field_test

field_test: field.o field_test.o
	g++ field.o field_test.o -o field_test

field.o: field.cc field.h
	g++ -c -std=c++11 field.cc

field_test.o: field_test.cc field.h
	g++ -c -std=c++11 field_test.cc

main: shrdlu.o main.o
	g++ shrdlu.o main.o -o main

shrdlu.o: shrdlu.cc shrdlu.h
	g++ -c -std=c++11 shrdlu.cc

main.o: main.cc shrdlu.h
	g++ -c -std=c++11 main.cc

doc: README.md
	$(MARKDOWN) $< --output README.html

clean:
	rm *.html *.o main field_test
