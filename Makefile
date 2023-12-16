.PHONY: clean distclean default

LLVMCONFIG=llvm-config-12

CXX=clang++
CXXFLAGS=-Wall -g `$(LLVMCONFIG) --cxxflags`
LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`

default: gracec

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y

lexer.o: lexer.cpp lexer.hpp parser.hpp ast.hpp

parser.o: parser.cpp lexer.hpp ast.hpp

general.o  : general.c general.h error.h

error.o    : error.c general.h error.h

symbol.o   : symbol.c symbol.h general.h error.h

# Grabs list of .hpp files and replaces .hpp suffix with .o suffix
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

# Reminder: $^ deduplicates the target's prerequisites
# This is needed to avoid having parser.o/lexer.o two times, when parser.hpp exist from a previous make
gracec: $(objects) symbol.o parser.o lexer.o general.o error.o
	$(CXX) $(CXXFLAGS) -o gracec $^ $(LDFLAGS)

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o

distclean: clean
	$(RM) gracec
