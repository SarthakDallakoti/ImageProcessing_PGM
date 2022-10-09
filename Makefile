C=gcc
CFLAGS=-g -std=c99 -fmax-errors=1 -Werror
MODULES = pgmRead.o pgmWrite.o
MAINS = pgmEcho.o pgmComp.o pgma2b.o pgmb2a.o pgmReduce.o pgmTile.o pgmAssemble.o
TARGETS = pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble

all:		${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES} *.o

pgmEcho:		pgmEcho.o ${MODULES}
		${CC} 		${CCFLAGS} -o pgmEcho 	pgmEcho.o		${MODULES}

pgmComp:		pgmComp.o ${MODULES}
	${CC} 		${CCFLAGS} -o pgmComp 	pgmComp.o		${MODULES}

pgma2b:		pgma2b.o ${MODULES}
	${CC} 		${CCFLAGS} -o pgma2b 	pgma2b.o		${MODULES}

pgmb2a:		pgmb2a.o ${MODULES}
	${CC} 		${CCFLAGS} -o pgmb2a 	pgmb2a.o		${MODULES}

pgmReduce:		pgmReduce.o ${MODULES}
	${CC} 		${CCFLAGS} -o pgmReduce 	pgmReduce.o		${MODULES}

pgmTile:		pgmTile.o ${MODULES}
	${CC} 		${CCFLAGS} -o pgmTile 	pgmTile.o		${MODULES}

pgmAssemble:		pgmAssemble.o ${MODULES}
	${CC} 		${CCFLAGS} -o pgmAssemble 	pgmAssemble.o		${MODULES}

pgmEcho.o: pgmEcho.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmEcho.o pgmEcho.c

pgmComp.o: pgmComp.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmComp.o pgmComp.c

pgma2b.o: pgma2b.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgma2b.o pgma2b.c

pgmb2a.o: pgmb2a.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmb2a.o pgmb2a.c

pgmReduce.o: pgmReduce.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmReduce.o pgmReduce.c

pgmAssemble.o: pgmAssemble.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmAssemble.o pgmAssemble.c

gmReduce.o: pgmTile.c pgmRead.h pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmTile.o pgmTile.c

pgmRead.o: pgmRead.c pgmRead.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmRead.o pgmRead.c

pgmWrite.o: pgmWrite.c pgmWrite.h
	gcc -c -g -std=c99 -fmax-errors=1 -Werror -o pgmWrite.o pgmWrite.c
