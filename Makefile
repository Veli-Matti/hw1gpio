CC = gcc
FILES = main.c gpio.c
OUT_EXE = hw1gpio.o

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
     
clean:
	-rm -f *.o core   
