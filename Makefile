CC=g++
CFLAGS=-g -Wall -Wpedantic -std=c++11
BIN=read-word-lists
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/*.cpp, $(OBJ)/*.o, $(SRCS))
HDRS=$(wildcard $(SRC)/*.h)

all: $(BIN)

$(BIN): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $@

clean:
	rm -r $(OBJ)
	rm $(BIN)

echo: $(SRC)/%.cpp
	echo $<

