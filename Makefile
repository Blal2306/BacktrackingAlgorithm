all : p1

p1 : 
	gcc brute.c -o brute.out -std=c99
	gcc backtrack.c -o backtrack.out -std=c99
	
clean :
	rm *.o