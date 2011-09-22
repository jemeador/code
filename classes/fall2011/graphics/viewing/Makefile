CC= gcc
#CFLAGS= -ansi -pedantic -Wall -O2
CFLAGS= -ansi -pedantic -Wall -g

#-------------------------------------------------------------------------------
# Configure the lacation of the cube, image, plane, and math3d utilities.
# MODIFY THIS as needed.

UTILDIR= ../util3d

UTILS= 	$(UTILDIR)/obj.o \
	$(UTILDIR)/cube.o \
	$(UTILDIR)/image.o \
	$(UTILDIR)/plane.o 

DEMOS= 	opengl-test \
	viewing-hello-cube \
	viewing-tumble-1 \
	viewing-tumble-2 \
	viewing-tumble-3 \
	viewing-tumble-4 \
	viewing-tumble-5 \
	viewing-look-1 \
	viewing-look-2 \
	viewing-look-3 \
	viewing-look-4 \
	viewing-look-5 \
	viewing-look-6 \
	viewing-point-1 \
	viewing-point-2 \
	viewing-point-3 \
	viewing-obj

#-------------------------------------------------------------------------------
# Configure the image handling and GL libraries and headers. This assumes that
# Mac OS X dependencies are installed using Macports. MODIFY THIS as needed.

INCS = -I$(UTILDIR)
LIBS = -lIlmImf -ljpeg -lpng -lz -lGLEW 

ifeq ($(shell uname), Darwin)
#	INCS += -I/opt/local/include
#	LIBS += -L/opt/local/lib
	LIBS += -framework OpenGL -framework GLUT
else
	LIBS += -lGL -lglut
endif

#-------------------------------------------------------------------------------
# Define implicit rules building all demos. Should be no need to modify this.

all : $(DEMOS)

%   : %.c
%.o : %.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

%   : %.o $(UTILS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

clean :
	rm -f $(DEMOS) $(UTILS) *.o

#-------------------------------------------------------------------------------
