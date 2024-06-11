CFLAGS = -Wall -Wextra
PROG = main
SRC = main.c hardware_controller.c
OBJ = $(SRC:.c=.o)
STATIC_LIB = hardware_controller.a
DYNAMIC_LIB = hardware_controller.so

hardware_controller_pic.o: hardware_controller.c
	$(CC) $(CFLAGS) -fPIC -c hardware_controller.c -o hardware_controller_pic.o

$(STATIC_LIB): hardware_controller.o
	ar rcs $(STATIC_LIB) hardware_controller.o

$(DYNAMIC_LIB): hardware_controller_pic.o
	gcc -shared -o $(DYNAMIC_LIB) hardware_controller_pic.o

static: $(STATIC_LIB) $(PROG)

dynamic: $(DYNAMIC_LIB) $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

run: $(PROG)
	./$(PROG)

clean:
	rm -f *.o *.so *.a $(PROG)