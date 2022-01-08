# DSA.HanoiBusRoute
Mini Project 2: Bus Map and Shortest Path

Subject: Data Structure And Algorithms Advanced Lab

## Requirements
- gtk-3.0
- jval
- jrb
- make (Optional)

### How to compile

#### With `make`
If you have `make`, change current working directory to project by `cd`. And compile:
```shell
cd <project_folder>
make
```
These commands will create `test.exe` file in that folder.
#### Without `make`
Without make will be a very long command.
```shell
cd <project_folder>
Gcc `pkg-config --cflags gtk+-3.0` Main/main.c -o test  JVAL_JRB/jrb.c JVAL_JRB/jval.c QandS/Queue/pqueue.c Reader/reader.c QandS/Stack/stack.c GUI/state.c GUI/state1.c GUI/state2.c GUI/state3.c Graph/DirectedGraph.c Path/state_ults.c `pkg-config --libs gtk+-3.0` -w
```
### How to run
Just run this command
```shell
./test
```
