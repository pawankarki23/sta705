# The GNU make manual is available in several forms from
# https://www.gnu.org/software/make/manual/
# Automatic variables are defined in section 10.5.3.
# Selected ones are:
# $^ the names of all the prerequsites
# $@ the name of the target
# $< the name of the first prerequsite

.PHONY   : clean install

DEBUG       = -g -Wall
TARGET      =  rosenbrock

VPATH = src

SRC_FILES   = $(TARGET).cpp Evolution.cpp 
OBJ_FILES   = $(patsubst %.cpp, %.o,   ${SRC_FILES})

$(TARGET): ${OBJ_FILES}
	$(CXX) ${DEBUG} $^  -o $@  

%.o:%.cpp
	$(CXX) $(DEBUG)  $(INCLUDES) -c $< -o $@ 

clean:
	rm *.o $(TARGET)

install:
	ar -cru ${HOME}/usr/lib/liballen.a Evolution.o;\
	cp src/Evolution.h ${HOME}/usr/include
	cp src/Evolution.cpp ${HOME}/usr/src

