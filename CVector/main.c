#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CVEC_UPPERCASE
#include "CVector.h"


InitializeVector(int)
InitializeVector(float)

int main(char** args, int argv) {

	Vector(int) vec = CreateVector(int);

	CVecAdd(int, &vec, 10);
	CVec_Add_int(&vec, 9);
	CVec_Add_int(&vec, 8);
	CVec_Add_int(&vec, 7);
	CVec_Add_int(&vec, 6);
	CVec_Add_int(&vec, 5);
	CVec_Add_int(&vec, 4);
	CVec_Add_int(&vec, 3);
	CVec_Add_int(&vec, 2);
	CVec_Add_int(&vec, 1);
	CVec_Add_int(&vec, 0);
	CVec_Add_int(&vec, -1);
	printf("%d\n", *CVec_Get_int(&vec, 11));
	CVecPop(int, &vec);
	CVec_Pop_int(&vec, NULL);
	int value = 0;
	CVecPopV(int, &vec, &value);
	printf("Popped Value: %d\n", value);

	printf("%d\n", *CVec_Get_int(&vec, 4));
	CVecPrintPrimitive(int, &vec, " %d ");
	CVecRemove(int, &vec, 1);
	CVecPrintPrimitive(int, &vec, " %d ");
	printf("Vec Size: %d, Vec Buffer Size: %d", vec.count, vec.bufferSize);

	CVecFree(int, &vec);


	Vector(float) floatVec = CreateVector(float);
	CVecAdd(float, &floatVec, 25.5);
	CVecAdd(float, &floatVec, 29.5);
	CVecAdd(float, &floatVec, 110.232);
	CVecPrintPrimitive(float, &floatVec, " %f ");
	CVecFree(float, &floatVec);

	return 0;
}