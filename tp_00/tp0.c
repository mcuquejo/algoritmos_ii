#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap (int *x, int *y)
{
	int x_swap = *x;

	*x = *y;
	*y = x_swap;
}


int maximo(int vector[], int n)
{
	if (n > 0) {
		int max = vector[0];
		int pos_max = 0;

		for (int i = 1; i < n; i++) {
			if (vector[i] > max) {
				max = vector[i];
				pos_max = i;
			}
		}
		return pos_max;
	}
	return -1;
}


int comparar(int vector1[], int n1, int vector2[], int n2)
{
	int i = 0;

	while (n1 > i && n2 > i) {
		if (vector1[i] < vector2[i])
			return -1;
		else if(vector1[i] > vector2[i])
			return 1;
		i++;
	}

	if (n1 > i)
		return 1;
	if (n2 > i)
		return -1;
	return 0;
}


void seleccion(int vector[], int n)
{
	if (n > 1) {
		int cant = n;
		int pos_max = -1;

		while (cant > 1) {
			pos_max = maximo(vector, cant);
			swap(&vector[pos_max], &vector[cant - 1]);
			cant--;
		}
	}
}
