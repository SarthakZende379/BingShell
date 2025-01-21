CC = gcc
CFLAGS = -Wall -Wextra
SOURCES = main.c execute.c io.c globals.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = bingshell
TEST_TARGET = test_shell
TEST_SOURCES = test_shell.c execute.c io.c globals.c

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)

%.o: %.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_TARGET) test_output.txt

test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: clean test all