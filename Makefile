mygrep:features.o mains.o 
	cc mains.o features.o -o mygrep 
features.o:features.c features.h
	cc -c features.c -Wall
mains.o:mains.c features.h
	cc -c mains.c -Wall
