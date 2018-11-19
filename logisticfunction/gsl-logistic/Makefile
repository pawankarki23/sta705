# The GNU make manual is available in several forms from
# https://www.gnu.org/software/make/manual/
# Automatic variables are defined in section 10.5.3

# remove static and it will work in mac 
LDSTATIC    = -lgsl -lgslcblas -lallen #-static
CXX         = g++
DEBUG       = -g -Wall
INCLUDES    = -I${HOME}/usr/include
LIBRARY     = -L${HOME}/usr/lib
LINK       := $(CXX)

TARGET      = driver

SRC_FILES   = driver.cpp Logistic.cpp
OBJ_FILES   = $(patsubst %.cpp, %.o,   ${SRC_FILES})

VPATH       = src

$(TARGET): ${OBJ_FILES}
	$(CXX) ${DEBUG} -o $(TARGET) ${OBJ_FILES} ${LIBRARY} $(LDSTATIC)

%.o:%.cpp
	$(CXX) -c $(DEBUG)  $(INCLUDES) -o $@ $<

.PHONY   : clean
clean:
	rm *.o $(TARGET)

