#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CVEC_UPPERCASE
#include "CVector.h"

InitializeVector(int);
InitializeVector(float);

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
	CVecAddAll(int, &vec, 5, 43, 2, 32, 43, 32);
	CVecPrintPrimitive(int, &vec, " %d ");
	CVecRemove(int, &vec, 1);
	CVecPrintPrimitive(int, &vec, " %d ");
	printf("Vec Size: %d, Vec Buffer Size: %d", vec.count, vec.bufferSize);

	Vector(float) floatVec = CreateVector(float);
	CVecAdd(float, &floatVec, 25.5);
	CVecAdd(float, &floatVec, 29.5);
	CVecAdd(float, &floatVec, 110.232);
	CVec_Insert_float(&floatVec, 3, 420.69);
	CVecPrintPrimitive(float, &floatVec, " %.2f ");
	CVecFree(float, &floatVec);

	printf("Vector Add All Test:");
	CVecPrintPrimitive(int, &vec, " %d ");
	Vector(int) intVec = CreateVector(int);
	CVecAdd(int, &intVec, 20);
	CVecAdd(int, &intVec, 10);
	CVecPrintPrimitive(int, &intVec, " %d ");
	CVecAddVector(int, &intVec, &vec);
	CVecPrintPrimitive(int, &intVec, " %d ");

	int testArr[] = {-23, -43, -3, 4};
	CVecAddArray(int, &intVec, testArr, 4);
	CVecPrintPrimitive(int, &intVec, " %d ");

	CVecFree(int, &vec);
	CVecFree(int, &intVec);

	return 0;
}