#include <stdio.h>
#include <string.h>
#include "alg.h"
#include "queue.h"

int main(void) {
	
	int MAX_NUMBER_OF_NODES = 20000;							// massimo numero di nodi
	
	//// lettura input
	
	int i, j;
	
	char nodeNames[MAX_NUMBER_OF_NODES][30];					// posso usarlo per la corrispondenza indici-nodi
	char garbage[30];
	char graphName[30];
	scanf("%[^-^ ^	^;]", garbage);
	scanf("%[^a-zA-Z0-9]", garbage);
	scanf("%[^ ^	^{^\n]", graphName);
	scanf("%[^a-zA-Z0-9]", garbage);
	
	i = 0;
	scanf("%[^-^ ^	^;]", nodeNames[i]);
	i++;
	scanf("%[^a-zA-Z0-9]", garbage);
	while (garbage[0]!='}' && garbage[1]!='}' && garbage[2]!='}' && garbage[3]!='}') {
		scanf("%[^-^ ^	^;]", nodeNames[i]);
		scanf("%[^a-zA-Z0-9]", garbage);
		for (j=0;j<i;j++) {
			if (strcmp(nodeNames[j], nodeNames[i])==0) break;
			if (j==i-1) {
				i++;
				break;
			}
		}
	}
	
	int nrNodes = i;
	
	int adjMat[nrNodes][nrNodes];									// matrice di adiacenza
	for (i=0;i<nrNodes;i++) {
		for (j=0;j<nrNodes;j++) {
			adjMat[i][j]=0;
		}
	}
	
	rewind(stdin);
	
	char node1[30];													// popolo la matrice
	char node2[30];
	scanf("%[^{]", garbage);
	scanf("%[^a-zA-Z0-9]", garbage);
	while (garbage[1]!='}' && garbage[2]!='}' && garbage[3]!='}') {
		scanf("%[^-^ ^	^;]", node2);
		scanf("%[^a-zA-Z0-9]", garbage);
		while (garbage[0]!=';' && garbage[1]!=';' && garbage[2]!=';') {
			strcpy(node1, node2);
			scanf("%[^-^ ^	^;]", node2);
			scanf("%[^a-zA-Z0-9]", garbage);
			for (i=0;i<nrNodes;i++) {
				for (j=0;j<nrNodes;j++) {
					if (strcmp(nodeNames[i], node1)==0 && strcmp(nodeNames[j], node2)==0) {
						adjMat[i][j]=1;
						adjMat[j][i]=1;
					}
				}
			}
		}
	}
	
	////

	int roots[nrNodes];										// 0 = nodo non visitato, 1 = nodo su cui lancio BFS
	int heights[nrNodes];									// altezze delle radici
	for (i=0;i<nrNodes;i++) {
		roots[i]=0;
		heights[i]=0;
	}
	
	for (i=0;i<nrNodes;i++) {
		if (roots[i]==0)
			DFS ((int *)adjMat, roots, i, nrNodes);
	}
	
	for (i=0;i<nrNodes;i++) {
		if (roots[i]==1)
			BFS ((int *)adjMat, i, nrNodes, roots, heights);
	}
	
	int parent[nrNodes];										// uso l'array parent per orientare l'albero
	for (i=0;i<nrNodes;i++) {
		if (roots[i]==1)
			BFS_tree ((int *)adjMat, i, nrNodes, parent);
	}
	
	//// printer
	
	printf("digraph %s {\n", graphName);
	
	for (i=0;i<nrNodes;i++) {
		if (roots[i]==1) {
			printf("%s [label=\"%s: h(%s)=%i\"];\n", nodeNames[i], nodeNames[i], nodeNames[i], heights[i]);
		} else {
			printf("%s->%s;\n", nodeNames[parent[i]], nodeNames[i]);
		}
	}
	
	printf("}\n");
	
	////
	
	return 0;
}

