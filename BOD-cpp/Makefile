# It is required that triangular  and line search are 
# installed in liballen

LDSTATIC    = -lallen 
INCLUDES    = -I${HOME}/usr/include
LIBRARY     = -L${HOME}/usr/lib

TARGET      =  driver
.PHONY   : clean install

VPATH = src

${TARGET} : ${TARGET}.o  
	g++ -g -Wall $^ ${LIBRARY} -lallen $(LDSTATIC) -o $@

${TARGET}.o : ${TARGET}.cpp 
	g++ -g -Wall ${INCLUDES} -c $< -o $@

clean:
	rm *.o ${TARGET}

