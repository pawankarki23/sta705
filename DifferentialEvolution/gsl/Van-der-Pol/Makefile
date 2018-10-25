LDSTATIC    =  -lgsl -lgslcblas  
CXX         =  g++
DEBUG       = -g -Wall
TARGET      =  test
INCLUDES    = -I${HOME}/usr/include -I/usr/local/include/gsl
LIBRARY     = -L${HOME}/usr/lib     -L/usr/local/lib

.PHONY   : clean 

SRC_FILES   = $(TARGET).cpp 
OBJ_FILES   = $(patsubst %.cpp, %.o,   ${SRC_FILES})

VPATH       = src

$(TARGET): ${OBJ_FILES}
	$(CXX) ${DEBUG} ${LIBRARY} -o $(TARGET) ${OBJ_FILES}  $(LDSTATIC)

%.o:%.cpp
	$(CXX) -c $(DEBUG)  $(INCLUDES) -o $@ $<

clean:
	rm *.o $(TARGET)

