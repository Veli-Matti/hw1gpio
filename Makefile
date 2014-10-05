CC = gcc
FILES = main.c gpio.c
OUT_EXE = mygpio.o

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)
     
clean:
	-rm -f *.o core   
