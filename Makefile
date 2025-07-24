SRC:=$(shell echo .\src)
INC:=$(shell echo .\include)
LIB:=$(shell echo .\lib)
BLD:=$(shell echo .\build)




build:
	g++ $(SRC)\main.cpp $(INC)\glad\glad.c -I$(INC) -L$(LIB) -lglfw3 -lopengl32 -lgdi32 -o$(BLD)\main.exe
.PHONY : build

run:
	$(BLD)\main.exe
.PHONY : run

