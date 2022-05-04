CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJFILES = test1.o lab1.o
TARGET = test1

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~