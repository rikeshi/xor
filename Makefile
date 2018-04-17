CC=gcc

INCLUDES=-Iinclude
LIBS=-lm -lSDL2

SRCS=xor.c window.c matrix.c nn.c
OBJS=$(SRCS:.c=.o)

TARGET=xor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o $(TARGET)
