INCLUDES    = -I${HOME}/usr/include
LIBRARY     = -L${HOME}/usr/lib
DEBUG       = -g -Wall

TARGET      =  driver
.PHONY   : clean install

VPATH = src

SRC_FILES   = $(TARGET).cpp DEsystem.cpp 
OBJ_FILES   = $(patsubst %.cpp, %.o,   ${SRC_FILES})

$(TARGET): ${OBJ_FILES}
	$(CXX) ${DEBUG} ${LIBRARY} -o $(TARGET) $(LDSTATIC) ${OBJ_FILES}

%.o:%.cpp
	$(CXX) -c $(DEBUG)  $(INCLUDES) -o $@ $<

clean:
	rm *.o ${TARGET}

install:
	ar -cru ${HOME}/usr/lib/liballen.a DEsystem.o;\
	cp src/DEsystem.h   ${HOME}/usr/include;\
	cp src/DEsystem.cpp ${HOME}/usr/src


