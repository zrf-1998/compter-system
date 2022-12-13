FILES = main0.c vec.c
CC = gcc
TARGET = proc0
LIBS = 
CLFAGS = -O1 -g -Wall -DIDENT=0 -DOP=*
OBJ = $(patsubst %.c, %.o, $(FILES))

$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(CLFAGS) $(LIBS)

$(OBJ):%.o:%.c
	$(CC) -c $< -o $@ $(CLFAGS)

clean:
	rm -rf $(OBJ) $(TARGET)
