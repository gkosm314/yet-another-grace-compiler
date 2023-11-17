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

gracec: lexer.o parser.o
	$(CXX) $(CXXFLAGS) -o gracec lexer.o parser.o

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o

distclean: clean
	$(RM) gracec
