CC = g++
EXEC = main.one
OBJS = main.o utils.o scaner.o
HEADERS = include/*.h

.PHONY: all
all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS)

utils.o: src/utils.cpp $(HEADERS)
	$(CC) -c src/utils.cpp
scaner.o: src/scaner.cpp $(HEADERS)
	$(CC) -c src/scaner.cpp

.PHONY: clean
clean:
	rm -rf $(EXEC) *.elf *.gdb *.o
