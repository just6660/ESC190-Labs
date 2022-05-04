CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJFILES = lab2_task7.o
TARGET = task7

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~