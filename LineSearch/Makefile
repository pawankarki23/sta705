# It is required that triangular is installed in liballen
LDSTATIC    = -lallen 
INCLUDES    = -I${HOME}/usr/include
LIBRARY     = -L${HOME}/usr/lib

TARGET      =  driver
.PHONY   : clean install

VPATH = src

${TARGET} : ${TARGET}.o  LineSearch.o
	g++ -g -Wall $^ ${LIBRARY} -lallen $(LDSTATIC) -o $@

LineSearch.o : LineSearch.cpp LineSearch.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

${TARGET}.o : ${TARGET}.cpp LineSearch.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

clean:
	rm *.o ${TARGET}

install:
	ar -cru             ${HOME}/usr/lib/liballen.a LineSearch.o;\
	cp src/LineSearch.h   ${HOME}/usr/include;\
	cp src/LineSearch.cpp ${HOME}/usr/src

