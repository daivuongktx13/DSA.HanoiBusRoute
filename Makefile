

CC=gcc
GTKFLAGS= `pkg-config --cflags gtk+-3.0`
GTKLIBS= `pkg-config --libs gtk+-3.0`

all:test

test: jrb.o jval.o pqueue.o reader.o stack.o state.o state1.o state2.o state3.o DirectedGraph.o state_ults.o
	${CC} ${GTKFLAGS}  Main/main.c -o test jrb.o jval.o pqueue.o reader.o stack.o state.o state1.o state2.o state3.o DirectedGraph.o state_ults.o  ${GTKLIBS} -w 
	
jrb.o: JVAL_JRB/jrb.c
	${CC} -c JVAL_JRB/jrb.c -w

jval.o: JVAL_JRB/jval.c
	${CC} -c JVAL_JRB/jval.c -w

pqueue.o: QandS/Queue/pqueue.c
	${CC} -c QandS/Queue/pqueue.c -w

reader.o: Reader/reader.c
	${CC} -c Reader/reader.c -w

stack.o: QandS/Stack/stack.c
	${CC} -c QandS/Stack/stack.c -w

state.o: GUI/state.c 
	${CC} ${GTKFLAGS} -c GUI/state.c -w ${GTKLIBS}

state1.o: GUI/state1.c 
	${CC} ${GTKFLAGS} -c GUI/state1.c -w ${GTKLIBS}

state2.o: GUI/state2.c 
	${CC} ${GTKFLAGS} -c GUI/state2.c -w ${GTKLIBS}

state3.o: GUI/state3.c 
	${CC} ${GTKFLAGS} -c GUI/state3.c -w ${GTKLIBS}

DirectedGraph.o: Graph/DirectedGraph.c
	${CC} ${GTKFLAGS} -c Graph/DirectedGraph.c -w

state_ults.o: Path/state_ults.c
	${CC} ${GTKFLAGS} -c Path/state_ults.c -w ${GTKLIBS}

clean:
	rm -f *.exe *~ *.o