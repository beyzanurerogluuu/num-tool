CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = numtool
OBJS = main.o parser.o math_utils.o records.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c parser.h records.h
	$(CC) $(CFLAGS) -c main.c

parser.o: parser.c parser.h math_utils.h records.h
	$(CC) $(CFLAGS) -c parser.c

math_utils.o: math_utils.c math_utils.h
	$(CC) $(CFLAGS) -c math_utils.c

records.o: records.c records.h
	$(CC) $(CFLAGS) -c records.c

clean:
	rm -f *.o $(TARGET)
