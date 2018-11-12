# The GNU make manual is available in several forms from
# https://www.gnu.org/software/make/manual/
# Automatic variables are defined in section 10.5.3.
# Selected ones are:
# $^ the names of all the prerequsites
# $@ the name of the target
# $< the name of the first prerequsite

TARGET      =  driver
.PHONY   : clean install

VPATH = src

${TARGET} : ${TARGET}.o Triangular.o
	g++ -g -Wall $^   -o $@

# -fPIC required for possible shared object linkage
Triangular.o : Triangular.cpp Triangular.h
	g++ -g -Wall -fPIC  -c $< -o $@

${TARGET}.o : ${TARGET}.cpp         Triangular.h
	g++ -g -Wall ${INCLUDES} -c $< -o $@

clean:
	rm *.o ${TARGET}

install:
	ar -cru               ${HOME}/usr/lib/liballen.a Triangular.o
	cp src/Triangular.h   ${HOME}/usr/include
	cp src/Triangular.cpp ${HOME}/usr/src


