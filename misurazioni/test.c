#include <stdio.h>
#include <time.h>
#include <math.h>
#include "prepara.h"
#include "alg.h"
#include "queue.h"

double granularita();
int calcolaRipTara(int d, double tMin);
int calcolaRipLordo(int d, double tMin);
double tempoMedioNetto(int d, double tMin);
void misurazione(int d, double tMin);

int main(void){
	double gran = granularita();
	double tMin = 20*gran;							// errore tollerato: 5%
	misurazione(100, tMin);							// primo parametro: numero di nodi
	return 0;
}

double granularita() {
	clock_t t0, t1;
	t0 = clock();
	t1 = clock();
	while (t1 == t0) {
		t1 = clock();
	}
	return ((double)(t1-t0))/CLOCKS_PER_SEC;
}

int calcolaRipTara(int d, double tMin) {
	int i;
	int rip = 1;
	int e[d][d];
	
	clock_t t0, t1;
	
	while (t1-t0 <= tMin) {
		rip = rip*2; 								// stima di rip con crescita esponenziale
		t0 = clock();
		for (i=0;i<rip;i++) {
			prepara((int *)e, d);
		}
		t1 = clock();
	}
	// ricerca esatta del numero di ripetizioni per bisezione
	// approssimiamo a 5 cicli
	int max = rip;
	int min = rip/2;
	int cicliErrati = 5;
	while (max-min >= cicliErrati) {
		rip = (max + min)/2; 						// valore mediano
		t0 = clock();
		for (i=0;i<rip;i++) {
			prepara((int *)e, d);
		}
		t1 = clock();
		if (((double)(t1-t0))/CLOCKS_PER_SEC <= tMin) {
			min = rip;
		} else {
			max = rip;
		}
	}
	return max;
}

int calcolaRipLordo(int d, double tMin) {
	int i;
	int rip = 1;
	int e[d][d];
	
	clock_t t0, t1;
	
	while (t1-t0 <= tMin) {
		rip = rip*2; 								// stima di rip con crescita esponenziale
		t0 = clock();
		for (i=0;i<rip;i++) {
			prepara((int *)e, d);
			execute((int *)e, d);
		}
		t1 = clock();
	}
	// ricerca esatta del numero di ripetizioni per bisezione
	// approssimiamo a 5 cicli
	int max = rip;
	int min = rip/2;
	int cicliErrati = 5;
	while (max-min >= cicliErrati) {
		rip = (max + min)/2; 						// valore mediano
		t0 = clock();
		for (i=0;i<rip;i++) {
			prepara((int *)e, d);
			execute((int *)e, d);
		}
		t1 = clock();
		if (((double)(t1-t0))/CLOCKS_PER_SEC <= tMin) {
			min = rip;
		} else {
			max = rip;
		}
	}
	return max;
}

double tempoMedioNetto(int d, double tMin) {
	int i;

	int ripTara = calcolaRipTara(d, tMin);
	int ripLordo = calcolaRipLordo(d, tMin);
	
	int e[d][d];
	
	clock_t t0, t1;
	
	t0 = clock();
	for (i=0;i<ripTara;i++) {
		prepara((int *)e, d);
	}
	t1 = clock();
	double ttara = ((double)(t1-t0))/CLOCKS_PER_SEC; 						// tempo totale di esecuzione della tara
	
	t0 = clock();
	for (i=0;i<ripLordo;i++) {
		prepara((int *)e, d);
		execute((int *)e, d);
	}
	t1 = clock();
	double tlordo = ((double)(t1-t0))/CLOCKS_PER_SEC; 						// tempo totale di esecuzione del lordo
	
	double tmedio = tlordo/(double)ripLordo - ttara/(double)ripTara;		// tempo medio di esecuzione
	
	return tmedio;
}

void misurazione(int d, double tMin) {
	int n = 10;
	double za = 1.96;
	double DELTA;
	double t = 0.0;
	double sum2 = 0.0;
	int cn = 0;
	double delta;
	double m, e, s;
	int i;
	
	do {
		for (i=0;i<n;i++) {
			m = tempoMedioNetto(d, tMin);
			t += m;
			sum2 += pow(m, 2);
		}
		cn += n;
		e = t/cn;
		DELTA = e/10;
		s = sqrt(sum2/cn - pow(e,2) );
		delta = 1/sqrt(cn) * za * s;
	} while (delta>=DELTA);
	
	printf("%f\n%f\n", e*1000, delta*1000);				// stampo in millisecondi
	//return (e, delta)
}
