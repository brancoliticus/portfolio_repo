COMMON_FILES=data_structures.c \
	graphics2d.c \
	graphics3d.c \
	mathlib.c \
	parseobj.c \
	util.c \
	xpmlib.c

SOURCES=lab1.c \
	lab2.c \
	lab3.c \
	lab4.c \
	lab5.c \
	lab6.c \
	lab7.c \
	lab8.c \
	lab9.c \
	lab10.c \
	main.c \
	
TESTSOURCES=testmain.c

CC=gcc

graphicengine:
	$(CC) -g -lm -O0 -Wall -pedantic -ansi \
	$(COMMON_FILES) $(SOURCES) -o graphicengine

clean:
	rm graphicengine

graphicengine_test:
	$(CC) -g -lm -O0 -Wall -pedantic -ansi \
	$(COMMON_FILES) $(TESTSOURCES) -o graphicengine

clean_test:
	rm graphicengine