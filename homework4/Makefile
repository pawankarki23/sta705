# automatic variables
# $^ the names of all the prerequsites
# $@ the name of the target
# $< the name of the first prerequsite

INCLUDES    = `fltk-config --cxxflags`
LIBRARY     = `fltk-config --ldstaticflags`

.PHONY   : clean

poly : poly.o  Polygon.o 
	g++ -g -Wall $^  ${LIBRARY} -o $@

Polygon.o : Polygon.cpp Polygon.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

poly.o : poly.cpp Polygon.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

clean:
	rm *.o poly

