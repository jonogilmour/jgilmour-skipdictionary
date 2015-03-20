# Basic Makfile for comp20003 AlgDS assignment 1, semester 2, 2013
# Makes two dictionaries: listdict, based on linked list, skipdict, based on
#           skiplist
#Assumes two separate files with main() functions-- dict.c for the linked list
#           implementation and dict2.c for the skiplist
#These two .c files share a common header .h
# Also assumes list functions are in list.c, which includes list.h
#        and skiplist functions are in skiplist.c, which includes skiplist.h
# This file organization can be changed, but the Makefile need to be
# changed correspondingly

skipdict: skipmain.o skipdict.o stringlib.o
	gcc -o skipdict skipmain.o skipdict.o stringlib.o

listdict: listmain.o dict.o stringlib.o
	gcc -o listdict listmain.o dict.o stringlib.o

dict.o: dict.c dict.h
	gcc -c -Wall dict.c

skipdict.o: skipdict.c skipdict.h
	gcc -c -Wall skipdict.c

listmain.o: listmain.c
	gcc -c -Wall listmain.c

skipmain.o: skipmain.c
	gcc -c -Wall skipmain.c

stringlib.o: stringlib.c stringlib.h
	gcc -c -Wall stringlib.c

