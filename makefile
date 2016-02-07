CC=g++
CFLAGS=-g -Wall --std=c++11
SOURCES=lifegame.cpp
DEPS=
OBJS=$(SOURCES:.cpp=.o)
EXECUTABLE=life
LDFLAGS=-g
LDLIBS=

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# $@ is the filename of the target of the rule
# $< the name of the first prerequisite
# $^ the names of all prerequisites, with spaces in between
.cpp.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm *o $(EXECUTABLE)
