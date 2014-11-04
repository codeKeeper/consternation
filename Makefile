CC		= g++
PFLAGS	= -std=c++11
AFLAGS	= -g

FILES	= consternation.cpp
SOURCES = World.o Area.o

consternation : ${FILES} ${SOURCES} consternation.h
	${CC} ${PFLAGS} ${FILES} ${SOURCES} -o consternation ${AFLAGS}

consternation.cpp : ${SOURCES} consternation.h
	${CC} ${PFLAGS} -c consternation.cpp ${AFLAGS}

World.o : World.cpp consternation.h
	${CC} ${PFLAGS} -c World.cpp ${AFLAGS}

Area.o : Area.cpp consternation.h
	${CC} ${PFLAGS} -c Area.cpp ${AFLAGS}

clean :
	rm ${FILES} ${SOURCES}