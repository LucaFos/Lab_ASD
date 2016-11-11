#include <math.h>
#include "prepara.h"

void prepara(int *adjMat, int nrNodes) {
	long int n1, n2, i, j;
	
	double seed = fabs(fmod(123456789.0, 2147483647.0));
	
	for (i=0; i<nrNodes; i++) {
		for (j=0; j<nrNodes; j++) {
			*(adjMat + i*nrNodes + j) = 0;
		}
	}
	

	for (i=0; i < (pow(nrNodes, 2))/5; i++) {
		n1 = (floor(get(&seed) * (nrNodes-1) + 0.5));
		n2 = (floor(get(&seed) * (nrNodes-1) + 0.5));
		if (n1!=n2 && *(adjMat + n1*nrNodes + n1)!=1) {
			*(adjMat + n1*nrNodes + n2) = 1;
			*(adjMat + n2*nrNodes + n1) = 1;
		} else {
			i--;
		}
	}
}

double get(double *seed) {
	double a = 16087.0;
	double m = 2147483647.0;
	double q = 127773.0;
	double r = 2836.0;

	double lo, hi, test;

	hi = ceil(*seed/q);
	
	lo = *seed - q * hi;
	
	test = a * lo - r * hi;
	if (test < 0.0) {
		*seed = test + m;
	} else {
		*seed = test;
	}
	
	return *seed / m;
}
