.PHONY: clean distclean default

CXX=c++
CXXFLAGS=-Wall -std=c++11 -g

default: gracec

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

parser.hpp parser.cpp: parser.y
	bison -dv -Wcounterexamples -o parser.cpp parser.y

lexer.o: lexer.cpp lexer.hpp parser.hpp ast.hpp

parser.o: parser.cpp lexer.hpp ast.hpp

general.o  : general.c general.h error.h

error.o    : error.c general.h error.h

symbol.o   : symbol.c symbol.h general.h error.h

gracec: lexer.o parser.o symbol.o general.o error.o
	$(CXX) $(CXXFLAGS) -o gracec lexer.o parser.o symbol.o general.o error.o

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o

distclean: clean
	$(RM) gracec
