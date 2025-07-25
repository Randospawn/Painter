SRC:=$(shell echo .\src)
INC:=$(shell echo .\include)
LIB:=$(shell echo .\lib)
BLD:=$(shell echo .\build)




build:
	g++ $(SRC)\main.cpp -I$(INC) -L$(LIB) -lgdi32 -o$(BLD)\main.exe
.PHONY : build

run:
	$(BLD)\main.exe
.PHONY : run

