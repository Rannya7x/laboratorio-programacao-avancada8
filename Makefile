CC = gcc
CFLAGS = -Wall
OBJ = main.o mpeg.o
EXEC = mpeg_info

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c mpeg.h
	$(CC) -c main.c $(CFLAGS)

mpeg.o: mpeg.c mpeg.h
	$(CC) -c mpeg.c $(CFLAGS)

clean:
	rm -f *.o $(EXEC)