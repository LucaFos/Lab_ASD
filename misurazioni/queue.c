#include "queue.h"

int head, tail;

void initQueue() {										// inizializza
	head = tail = -1;
}

void enqueue(int i, int myQueue[], int nrNodes) {		// aggiunge il nodo i alla coda
	tail++;
	myQueue[tail % nrNodes] = i;
}

int dequeue(int myQueue[], int nrNodes) {				// torna il nodo tolto dalla coda
	head++;
	return myQueue[head % nrNodes];
}

int isEmpty() {											// torna un bool (un int)
	return (head == tail);
}
