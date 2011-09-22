CC= gcc
CFLAGS= -std=c99 -pedantic -Wall -g

#-------------------------------------------------------------------------------

ifeq ($(shell uname), Linux)
LIBS= -lglut -lGLEW -lGL
else ifeq ($(shell uname), Darwin)
LIBS= -lGLEW -framework GLUT -framework OpenGL
else
LIBS= -L/c/MinGW/lib -lfreeglut -lglew32 -lopengl32 -lwinmm -lgdi32
endif


#-------------------------------------------------------------------------------

%.o : %.c
	$(CC) $(CFLAGS) -c $<

trivial : trivial.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

hello-world : hello-world.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean :
	rm -f  trivial trivial.o
