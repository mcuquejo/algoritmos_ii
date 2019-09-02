#include <stdio.h>
#include <stdlib.h>


void swap (int *x, int *y) {	
	int x_swap = *x;		
	*x = *y;
	*y = x_swap;
}

int maximo(int vector[], int n) {
	
	if (n == 0){
		return -1;
	} else if (n == 1){
		return 0;
	}
	
	int max = vector[0];
	int pos_max = 0;
	
	for (int i=1; i < n; i++){
		if (vector[i] > max){
			max = vector[i]; 
			pos_max = i;
		}		
	}
	return pos_max;
}

/* Compara dos arreglos de longitud especificada.
 *
 * Devuelve -1 si el primer arreglo es menor que el segundo; 0 si son
 * iguales; o 1 si el primero es el mayor.
 *
 * Un arreglo es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */

int comparar(int vector1[], int n1, int vector2[], int n2) {
	int i = 0;
	while (n1 > i && n2 > i){
		printf("n1%d, n2%d, i%d\n", n1,n2,i);
		if (vector1[i] < vector2[i]){
			return -1;
		}else if(vector1[i] > vector2[i]){
			return 1;
		}
		i++;
	}
	if (n1 > i)
		return 1;
	if (n2 > i)
		return -1;
	return 0;
}

/* Ordena el arreglo recibido mediante el algoritmo de selección.
 *
 * Debe usarse swap() y maximo() en la implementación.
 */
void seleccion(int vector[], int n) {
	
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

int main()
{
    int a = 5, b = 6;
	swap(&a,&b);
	printf("%d,%d\n", a,b);
	
	a = 10, b = -10;
	swap(&a,&b);
	printf("%d,%d\n", a,b);
	
	a = 3, b = 3;
	swap(&a,&b);
	printf("%d,%d\n", a,b);
	
	printf("SALIDA: %d\n", 7 /	 2);
	
	int vector2[] = { -2000, -1500, -1000, -3000 };
	int nvector2 = 4;
	
	int vector3[] = { -2000, -1500, -1000, -3005 };
	int nvector3 = 4;
	printf("maximo = %d\n", maximo(vector2, nvector2));
	
	printf("resultado comparacion %d\n",comparar(vector2, nvector2, vector3, nvector3));
	int prueba[] = {1,2};
	printf("arreglo = %d\n", prueba[0]);
	printf("arreglo = %d\n", prueba[1]);
	printf("arreglo = %d\n", prueba[2]);
	printf("arreglo = %d\n", prueba[3]);
	
	int vec4[] = {4, 8, 15, 16, 23, 42};
	int nvec4 = 6;
	int vec4_ord[] = {4, 8, 15, 16, 23, 42};
	
	seleccion(vec4, nvec4);
	printf("{ ");
	for(int i = 0; i < nvec4; i++) {    
        printf("%d ", vec4[i]);
    }
    printf(" }\n");
    
	printf("Prueba seleccion vec4 %d\n",
	comparar(vec4, nvec4, vec4_ord, nvec4));
	return 0;
}
