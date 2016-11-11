#ifndef ALG_H
#define ALG_H

void execute(int *adjMat, int nrNodes);
void DFS (int *adjMat, int *roots, int s, int nrNodes);
void DFS_visit (int *adjMat, char *color, int *parent, int *d, int *roots, int i, int nrNodes, int *max, int *maxNode);
void BFS (int *adjMat, int s, int nrNodes, int *roots, int *heights);
void BFS_tree (int *adjMat, int r, int nrNodes, int *parent);

#endif
