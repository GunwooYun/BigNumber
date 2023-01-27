CC = gcc
TARGET = main
OBJS = main.o bigNumber.o

$(TARGET) : $(OBJS)
	$(CC) -g -o main main.o bigNumber.o
main.o : main.c
	$(CC) -g -c -o main.o main.c
bigNumber.o : bigNumber.c
	$(CC) -g -c -o bigNumber.o bigNumber.c
clean:
	rm -rf main main.o bigNumber.o
