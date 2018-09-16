FILE=v5.cpp
EXE=a.out

all: run

compile: $(FILE)
	g++ $(FILE) -o $(EXE)

run: compile $(EXE)
	./$(EXE)

clean: all
	rm $(EXE)
