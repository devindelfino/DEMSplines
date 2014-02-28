CLIBS= 		-lm -lglut -lGL -lGLU -lX11 # 2014
#CPATHS=	-L/usr/X11R6/lib -I/usr/X11R6/include # 2011
CPATHS=		-I/usr/include -L/usr/lib # 2014
CFLAGS=		$(CPATHS)$(CLIBS)

OBJECTS = DelfinoG3Main.o DEM.o

#targets-----------------------------
DelfinoG3:	$(OBJECTS)
			g++ $(OBJECTS) -o DelfinoG3 $(CFLAGS)

clean:
	rm *.o

#dependencies
DelfinoG3Main.o:	DEM.h
DEM.o:		DEM.h

