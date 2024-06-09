CC = gcc
CFLAGS = -Wall -Wextra -I.
SRC = main.c hardware_controller.c
TARGET = main
OBJ = $(SRC:.c=.o)

STATIC_LIBRARY = hardware_controller.a
DYNAMIC_LIBRARY = hardware_controller.so

all: $(TARGET)

$(TARGET): $(OBJ) $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)
	$(CC) $(CFLAGS) -o $@ main.o -L. -hardware_controller

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIBRARY): hardware_controller.o
	ar rcs $@ $^

$(DYNAMIC_LIBRARY): hardware_controller.o
	$(CC) -fPIC -shared -o $@ $^

# make run
run: $(TARGET)
	LD_LIBRARY_PATH=. ./$(TARGET)

# make clean
clean:
	rm -f $(OBJ) $(TARGET) $(STATIC_LIBRARY) $(DYNAMIC_LIBRARY)