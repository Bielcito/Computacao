CC = g++
CFLAGS = -g -O2 -std=c++11
CLIBS = -lm $(shell sdl-config --cflags --libs) -lSDL_image
EXEC = render

#Get all source files recursively
SRC = $(shell find . -name '*.cpp')

#Generate object filenames from source files
OBJ = $(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(CLIBS)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(CLIBS)

clean:
	rm $(OBJ)
	rm $(EXEC)
