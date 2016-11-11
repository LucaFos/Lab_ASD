#include "alg.h"

void DFS (int *adjMat, int *roots, int s, int nrNodes) {
	int i;
	char color[nrNodes];
	int parent[nrNodes];
	int d[nrNodes];
	for (i=0;i<nrNodes;i++) {
		color[i] = 'w';
		d[i] = 0;
	}
	
	int max = 0;
	int maxNode;
	DFS_visit(adjMat, color, parent, d, roots, s, nrNodes, &max, &maxNode);
	roots[maxNode] = 1;
}

void DFS_visit (int *adjMat, char *color, int *parent, int *d, int *roots, int i, int nrNodes, int *max, int *maxNode) {
	color[i] = 'g';
	roots[i] = -1;
	int j;
	for (j=0;j<nrNodes;j++) {
		if (*(adjMat + i*nrNodes + j)==1 && color[j]=='w') {
			parent[j] = i;
			d[j] = d[i]+1;
			if (d[j]>*max) {
				*max = d[j];
				*maxNode = j;
			}
			roots[j] = -1;
			DFS_visit(adjMat, color, parent, d, roots, j, nrNodes, max, maxNode);
		} else if (color[j]!='g') {											// elimino cicli
			*(adjMat + i*nrNodes + j)=0;
			*(adjMat + j*nrNodes + i)=0;
		}
	}
	color[i] = 'b';
}

void BFS (int *adjMat, int r, int nrNodes, int *roots, int *heights) {
	int i;
	char color[nrNodes];
	int d[nrNodes];
	int parent[nrNodes];
	for (i=0;i<nrNodes;i++) {
		color[i] = 	'w';
		d[i] = nrNodes+1;
		parent[i] = -1;
	}
	color[r] = 'g';
	d[r] = 0;
	parent[r] = -1;
	roots[r] = -1;
	
	int myQueue[nrNodes];
	initQueue();
	enqueue(r, myQueue, nrNodes);
	
	int s;
	while (!isEmpty()) {
		s = dequeue(myQueue, nrNodes);
		for (i=0;i<nrNodes;i++) {
			if (*(adjMat + s*nrNodes + i)==1 && color[i]=='w') {
				roots[i] = -1;
				color[i] = 'g';
				d[i] = d[s]+1;
				parent[i] = s;
				enqueue(i, myQueue, nrNodes);
			}
		}
	}
	color[r] = 'b';
	int n = d[s];
	for (i=0;i<n/2;i++) s = parent[s];
	if (n%2==0) {
		heights[s] = n/2;
	} else {
		heights[s] = (n/2)+1;
	}
	roots[s] = 1;	
}

void BFS_tree (int *adjMat, int r, int nrNodes, int *parent) {
	int i;
	char color[nrNodes];
	for (i=0;i<nrNodes;i++) {
		color[i] = 	'w';
	}
	color[r] = 'g';
	parent[r] = -1;
	
	int myQueue[nrNodes];
	initQueue();
	enqueue(r, myQueue, nrNodes);
	
	while (!isEmpty()) {
		r = dequeue(myQueue, nrNodes);
		for (i=0;i<nrNodes;i++) {
			if (*(adjMat + r*nrNodes + i)==1 && color[i]=='w') {
				color[i] = 'g';
				parent[i] = r;
				enqueue(i, myQueue, nrNodes);
			}
		}
	}
	color[r] = 'b';
}
