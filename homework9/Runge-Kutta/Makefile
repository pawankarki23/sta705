# automatic variables defined on page 111 of make book
# $^ the names of all the prerequsites
# $@ the name of the target
# $< the name of the first prerequsite

INCLUDES    = -I${HOME}/usr/include
LIBRARY     = -L${HOME}/usr/lib
DEBUG       = -g -Wall

TARGET      =  driver
.PHONY   : clean install

VPATH = src

SRC_FILES   = $(TARGET).cpp Runge-Kutta.cpp 
OBJ_FILES   = $(patsubst %.cpp, %.o,   ${SRC_FILES})

$(TARGET): ${OBJ_FILES}
	$(CXX) ${DEBUG} $^ $(INCLUDES) ${LIBRARY} -lallen -o $(TARGET)  

%.o:%.cpp
	$(CXX) $(DEBUG)  $(INCLUDES) -c $< -o $@ 

clean:
	rm *.o ${TARGET}

install:
	ar -cru ${HOME}/usr/lib/liballen.a Runge-Kutta.o;\
	cp src/Runge-Kutta.h   ${HOME}/usr/include;\
	cp src/Runge-Kutta.cpp ${HOME}/usr/src


