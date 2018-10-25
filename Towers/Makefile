# automatic variables
# $^ the names of all the prerequsites
# $@ the name of the target
# $< the name of the first prerequsite

INCLUDES    = `fltk-config --cxxflags`
LIBRARY     = `fltk-config --ldstaticflags`

# look for cpp and header file in directory called src
VPATH = src

.PHONY   : clean

hanoi : hanoi.o Towers.o TopMenu.o Peg.o
	g++ -g -Wall $^  ${LIBRARY} -o $@

hanoi.o : hanoi.cpp Towers.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

Peg.o : Peg.cpp Towers.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

TopMenu.o : TopMenu.cpp TopMenu.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

Towers.o : Towers.cpp Towers.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

clean:
	rm *.o hanoi

