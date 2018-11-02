LDSTATIC    = -lgsl -lgslcblas 
CXX         =  g++
DEBUG       = -g -Wall
TARGET      =  driver
INCLUDES    = -I${HOME}/usr/include -I/usr/local/include/gsl
LIBRARY     = -L${HOME}/usr/lib     -L/usr/local/lib
LINK       := $(CXX)

.PHONY   : clean install

SRC_FILES   = driver.cpp GSLlinear.cpp CompModel.cpp Table.cpp
OBJ_FILES   = $(patsubst %.cpp, %.o,   ${SRC_FILES})

VPATH       = src

$(TARGET): ${OBJ_FILES}
	$(CXX) ${DEBUG}  ${LIBRARY}  ${OBJ_FILES}  $(LDSTATIC) -o $(TARGET)

%.o:%.cpp
	$(CXX) -c $(DEBUG)  $(INCLUDES) -o $@ $<

clean:
	rm *.o $(TARGET)

install:
	ar -cru              ${HOME}/usr/lib/liballen.a GSLlinear.o;\
	cp src/GSLlinear.h   ${HOME}/usr/include;\
	cp src/GSLlinear.cpp ${HOME}/usr/src

