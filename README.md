# DSA.HanoiBusRoute
Mini Project 2: Bus Map and Shortest Path

Subject: Data Structure And Algorithms Advanced Lab

## Dataset
All the dataset is crawled from **OpenStreetMap**, **OpenRouteService** through their **API** in Python.

[Overpass API](https://wiki.openstreetmap.org/wiki/Overpass_API)
[OpenRouteService](https://openrouteservice.org/)

## Requirements
- gtk-3.0
- pqueue (Volkan Yazıcı- 2014) [libpqueue](https://github.com/vy/libpqueue)
- jval
- jrb
- make (Optional)

## Compile & Run

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
### How to delete temporary file .o
```shell
make clean
```
## (**Bonus**) Set up coding environment VSCode Windows
Install `gtk-3.0` by `MSYS2` and then add follow code to `.vscode/c_cpp_properties.json` inside `configurations`:
```shell
"includePath": [
                "${workspaceFolder}/**",
                "C:\\msys64\\mingw64\\include\\gtk-3.0",
                "C:\\msys64\\mingw64\\include\\glib-2.0",
                "C:\\msys64\\mingw64\\lib\\glib-2.0\\include",
                "C:\\msys64\\mingw64\\include\\pango-1.0\\pango",
                "C:\\msys64\\mingw64\\include\\cairo",
                "C:\\msys64\\mingw64\\include\\gdk-pixbuf-2.0",
                "C:\\msys64\\mingw64\\include\\pango-1.0",
                "C:\\msys64\\mingw64\\include\\harfbuzz",
                "C:\\msys64\\mingw64\\include\\atk-1.0"
            ]
```

