MARKDOWN = pandoc --from markdown_github --to html 

all: main
	./main

main: shrdlu.o main.o
	g++ shrdlu.o main.o -o main

shrdlu.o: shrdlu.cc shrdlu.h
	g++ -c -std=c++11 shrdlu.cc

main.o: main.cc shrdlu.h
	g++ -c -std=c++11 main.cc

doc: README.md
	$(MARKDOWN) $< --output README.html

clean:
	rm *.html *.o main
