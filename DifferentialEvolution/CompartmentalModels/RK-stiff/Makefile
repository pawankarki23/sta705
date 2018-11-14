INCLUDES    = -I${HOME}/usr/include
LIBRARY     = -L${HOME}/usr/lib
TARGET      =  driver
.PHONY   : clean install

VPATH = src

${TARGET} : ${TARGET}.o  
	g++ -g -Wall $^ ${LIBRARY} -lallen -o $@

${TARGET}.o : ${TARGET}.cpp 
	g++ -g -Wall ${INCLUDES} -c $< -o $@

clean:
	rm *.o ${TARGET}


