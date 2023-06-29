test.o: main.o sem_thread.o
	gcc -o test main.o sem_thread.o -pthread

main.o: main.c
	gcc -c main.c 

sem_thread.o: sem_thread.c
	gcc -c sem_thread.c 

clean:
	rm *.o test
