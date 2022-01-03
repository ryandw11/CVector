#pragma once

/*
	======================[CVectors]====================
	    Version: 1.0
		Author: Ryandw11
		Copyright: MIT
	======================[CVectors]====================
*/

#ifndef CVector_H
#define CVector_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
	A macro to create the struct type for a vector.

	@param TYPE The type of vector.
*/
#define Vector(TYPE) Vector_##TYPE

#define CVector_Struct(TYPE) \
typedef struct {\
	TYPE* buffer;\
	size_t count;\
	size_t bufferSize;\
	size_t bufferAmount;\
} Vector_##TYPE;

#define CVector_Func_Create(TYPE) \
Vector_##TYPE CreateVector_##TYPE() {\
	Vector_##TYPE vec = { 0 };\
	vec.count = 0;\
	vec.bufferSize = 10;\
	vec.bufferAmount = 10;\
	vec.buffer = (int*)malloc(sizeof(int) * 10);\
	memset(vec.buffer, 0, sizeof(int) * 10);\
	return vec;\
}

#define CVector_Func_Resize(TYPE) \
void CVec_Resize_##TYPE(Vector_##TYPE* vec, int resizeTo) {\
	if(resizeTo < 0) return;\
	TYPE* bufStart = vec->buffer;\
	vec->bufferSize = resizeTo;\
	vec->buffer = (TYPE*)malloc(sizeof(TYPE) * vec->bufferSize);\
	memset(vec->buffer, 0, sizeof(TYPE)* vec->bufferSize);\
	memcpy(vec->buffer, bufStart, sizeof(TYPE)* vec->bufferSize);\
	free(bufStart);\
}

#define CVector_Func_Add(TYPE) \
void CVec_Add_##TYPE(Vector_##TYPE* vec, ##TYPE valueToAdd) {\
	if (vec->count >= vec->bufferSize) {\
		CVec_Resize_##TYPE(vec, vec->bufferSize + vec->bufferAmount);\
	}\
	vec->buffer[vec->count] = valueToAdd;\
	vec->count++;\
}

#define CVector_Func_Pop(TYPE) \
TYPE CVec_Pop_##TYPE(Vector_##TYPE* vec, TYPE* removeValue) {\
	if (vec->count < 1) return 0;\
	vec->count--;\
	if(removeValue != NULL) {\
		*removeValue = vec->buffer[vec->count];\
	}\
	memset(vec->buffer + vec->count, 0, sizeof(TYPE));\
	if (vec->count < vec->bufferSize - vec->bufferAmount && (vec->bufferSize - vec->bufferAmount >= vec->bufferAmount)) {\
		CVec_Resize_##TYPE(vec, vec->bufferSize - vec->bufferAmount);\
	}\
	return 1;\
}

#define CVector_Func_Remove(TYPE) \
int CVec_Remove_##TYPE(Vector_##TYPE* vec, size_t indexToRemove, TYPE* removeValue) {\
	if (vec->count < 1) return 0;\
	if (indexToRemove < 0 || indexToRemove >= vec->count) return 0;\
	if(removeValue != NULL) {\
		*removeValue = vec->buffer[indexToRemove];\
	}\
	memcpy(vec->buffer + indexToRemove, vec->buffer + indexToRemove + 1, sizeof(TYPE) * (vec->bufferSize - indexToRemove - 1));\
	vec->count--;\
	if (vec->count < vec->bufferSize - vec->bufferAmount && (vec->bufferSize - vec->bufferAmount >= vec->bufferAmount)) {\
		CVec_Resize_##TYPE(vec, vec->bufferSize - vec->bufferAmount);\
	}\
	return 1;\
}

#define CVector_Func_Get(TYPE) \
TYPE* CVec_Get_##TYPE(Vector_##TYPE* vec, size_t indexToGet) { \
	if (vec->count < 1) return NULL; \
	if (indexToGet < 0 || indexToGet >= vec->count) return NULL; \
	return &(vec->buffer[indexToGet]);\
}

#define CVector_Func_Free(TYPE) \
void CVec_Free_##TYPE(Vector_##TYPE* vec) { \
	free(vec->buffer); \
	vec->buffer = NULL; \
	vec->bufferAmount = 0; \
	vec->bufferSize = 0; \
	vec->count = 0; \
}

#define CVector_Func_Print_Primitive(TYPE) \
void CVec_Print_Primitive_##TYPE(Vector_##TYPE* vec, char* printFormat) {\
	printf("[");\
	size_t i;\
	for (i = 0; i < vec->count; i++) {\
		printf(printFormat, vec->buffer[i]);\
	}\
	printf("]\n");\
}\

/*
	======================================

			   Manditory Macros

	======================================
*/

#ifdef CVEC_UPPERCASE
/**
	This macro will insert in the vector's struct and its helper functions for the specified type.

	@param TYPE The type of vector to create.
*/
#define InitializeVector(TYPE) CVector_Struct(TYPE) CVector_Func_Create(TYPE) CVector_Func_Resize(TYPE) CVector_Func_Add(TYPE) CVector_Func_Pop(TYPE) CVector_Func_Remove(TYPE) CVector_Func_Get(TYPE) CVector_Func_Free(TYPE) CVector_Func_Print_Primitive(TYPE)
#elif defined CVEC_CAMMELCASE
/**
	This macro will insert in the vector's struct and its helper functions for the specified type.

	@param TYPE The type of vector to create.
*/
#define initializeVector(TYPE) CVector_Struct(TYPE) CVector_Func_Create(TYPE) CVector_Func_Resize(TYPE) CVector_Func_Add(TYPE) CVector_Func_Pop(TYPE) CVector_Func_Remove(TYPE) CVector_Func_Get(TYPE) CVector_Func_Free(TYPE) CVector_Func_Print_Primitive(TYPE)
#else
/**
	This macro will insert in the vector's struct and its helper functions for the specified type.

	@param TYPE The type of vector to create.
*/
#define Initialize_Vector(TYPE) CVector_Struct(TYPE) CVector_Func_Create(TYPE) CVector_Func_Resize(TYPE) CVector_Func_Add(TYPE) CVector_Func_Pop(TYPE) CVector_Func_Remove(TYPE) CVector_Func_Get(TYPE) CVector_Func_Free(TYPE) CVector_Func_Print_Primitive(TYPE)
#endif


/*
	======================================

			   Helper Macros

	======================================
*/

#ifndef CVEC_NO_MACRO

#ifdef CVEC_UPPERCASE
// Macro Definitions using uppercase


/**
	Create a vector of the specified type.

	@param TYPE The type of vector to create.

	@returns A struct created on the stack.
*/
#define CreateVector(TYPE) CreateVector_##TYPE()

/**
	Resize the vector to the specified size.

	Note: If you resize the vector to be smaller than the number of items it can hold, items outside of the bounds of the resize are effectively deleted.

	@param TYPE The type of vector to resize.
	@param VEC The pointer to the vector to resize.
	@param SIZE The size to resize the vector to. (Must be larger than 0)
*/
#define CVecResize(TYPE, VEC, SIZE) CVec_Resize_##TYPE(VEC, SIZE)

/**
	Add an item to a vector.

	@param TYPE The type of Vector to add to.
	@param VEC The vector to add to.
	@param VALUE The value that should be added.
*/
#define CVecAdd(TYPE, VEC, VALUE) CVec_Add_##TYPE(VEC, VALUE);

/**
	Remove an item from the end of the vector.

	@param TYPE The type of vector to pop from.
	@param VEC The vector to pop from.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVecPop(TYPE, VEC) CVec_Pop_##TYPE(VEC, NULL)

/**
	Remove an item from the end of the vector.

	@param TYPE The type of vector to pop from.
	@param VEC The vector to pop from.
	@param VALUE_PTR The pointer to the variable where the value popped off of the end of the vector is stored.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVecPopV(TYPE, VEC, VALUE_PTR) CVec_Pop_##TYPE(VEC, VALUE_PTR)

/**
	Remove an item from the vector.

	@param TYPE The type of vector to remove from.
	@param VEC The vector to remove from.
	@param INDEX The index of the item to remove.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVecRemove(TYPE, VEC, INDEX) CVec_Remove_##TYPE(VEC, INDEX, NULL)

/**
	Remove an item from the vector and obtain the value of the removed item.

	@param TYPE The type of vector to remove from.
	@param VEC The vector to remove from.
	@param INDEX The index of the item to remove.
	@param VALUE_PTR The pointer to the variable where the removed value will be stored.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVecRemoveV(TYPE, VEC, INDEX, VALUE_PTR) CVec_Remove_##TYPE(VEC, INDEX, VALUE_PTR)

/**
	Get an item from the vector at a specified index.

	@param TYPE The type of vector to get a value from.
	@param VEC The vector to get a value from.
	@param INDEX The index of the item to get from the vector.

	@returns A pointer to the specified item.
*/
#define CVecGet(TYPE, VEC, INDEX) CVec_Get_##TYPE(VEC, INDEX)

/**
	Free the memory used up by a vector.

	@param TYPE The type of vector.
	@param VEC The vector to free.
*/
#define CVecFree(TYPE, VEC) CVec_Free_##TYPE(VEC)

/**
	Print a vector that is a primitive type to the console. (Mainly used for debugging)

	@param TYPE The type of the vector.
	@param VEC The vector.
	@param FORMAT  The format to use for printing. For example: With an int vector it would be " %d "
*/
#define CVecPrintPrimitive(TYPE, VEC, FORMAT) CVec_Print_Primitive_##TYPE(VEC, FORMAT)

#elif defined CVEC_CAMMELCASE

/**
	Create a vector of the specified type.

	@param TYPE The type of vector to create.

	@returns A struct created on the stack.
*/
#define createVector(TYPE) CreateVector_##TYPE()

/**
	Resize the vector to the specified size.

	Note: If you resize the vector to be smaller than the number of items it can hold, items outside of the bounds of the resize are effectively deleted.

	@param TYPE The type of vector to resize.
	@param VEC The pointer to the vector to resize.
	@param SIZE The size to resize the vector to. (Must be larger than 0)
*/
#define cVecResize(TYPE, VEC, SIZE) CVec_Resize_##TYPE(VEC, SIZE)

/**
	Add an item to a vector.

	@param TYPE The type of Vector to add to.
	@param VEC The vector to add to.
	@param VALUE The value that should be added.
*/
#define cVecAdd(TYPE, VEC, VALUE) CVec_Add_##TYPE(VEC, VALUE);

/**
	Remove an item from the end of the vector.

	@param TYPE The type of vector to pop from.
	@param VEC The vector to pop from.

	@returns The error code, 0 if fail, 1 if success.
*/
#define cVecPop(TYPE, VEC) CVec_Pop_##TYPE(VEC, NULL)

/**
	Remove an item from the end of the vector.

	@param TYPE The type of vector to pop from.
	@param VEC The vector to pop from.
	@param VALUE_PTR The pointer to the variable where the value popped off of the end of the vector is stored.

	@returns The error code, 0 if fail, 1 if success.
*/
#define cVecPopV(TYPE, VEC, VALUE_PTR) CVec_Pop_##TYPE(VEC, VALUE_PTR)

/**
	Remove an item from the vector.

	@param TYPE The type of vector to remove from.
	@param VEC The vector to remove from.
	@param INDEX The index of the item to remove.

	@returns The error code, 0 if fail, 1 if success.
*/
#define cVecRemove(TYPE, VEC, INDEX) CVec_Remove_##TYPE(VEC, INDEX, NULL)

/**
	Remove an item from the vector and obtain the value of the removed item.

	@param TYPE The type of vector to remove from.
	@param VEC The vector to remove from.
	@param INDEX The index of the item to remove.
	@param VALUE_PTR The pointer to the variable where the removed value will be stored.

	@returns The error code, 0 if fail, 1 if success.
*/
#define cVecRemoveV(TYPE, VEC, INDEX, VALUE_PTR) CVec_Remove_##TYPE(VEC, INDEX, VALUE_PTR)

/**
	Get an item from the vector at a specified index.

	@param TYPE The type of vector to get a value from.
	@param VEC The vector to get a value from.
	@param INDEX The index of the item to get from the vector.

	@returns A pointer to the specified item.
*/
#define cVecGet(TYPE, VEC, INDEX) CVec_Get_##TYPE(VEC, INDEX)

/**
	Free the memory used up by a vector.

	@param TYPE The type of vector.
	@param VEC The vector to free.
*/
#define cVecFree(TYPE, VEC) CVec_Free_##TYPE(VEC)

/**
	Print a vector that is a primitive type to the console. (Mainly used for debugging)

	@param TYPE The type of the vector.
	@param VEC The vector.
	@param FORMAT  The format to use for printing. For example: With an int vector it would be " %d "
*/
#define cVecPrintPrimitive(TYPE, VEC, FORMAT) CVec_Print_Primitive_##TYPE(VEC, FORMAT)

#else
// Macro Definitions using underscore casing.
/**
	Create a vector of the specified type.

	@param TYPE The type of vector to create.
	
	@returns A struct created on the stack.
*/
#define Create_Vector(TYPE) CreateVector_##TYPE()

/**
	Resize the vector to the specified size.  
	  
	Note: If you resize the vector to be smaller than the number of items it can hold, items outside of the bounds of the resize are effectively deleted.
	  
	@param TYPE The type of vector to resize.
	@param VEC The pointer to the vector to resize.
	@param SIZE The size to resize the vector to. (Must be larger than 0)
*/
#define CVec_Resize(TYPE, VEC, SIZE) CVec_Resize_##TYPE(VEC, SIZE)

/**
	Add an item to a vector.

	@param TYPE The type of Vector to add to.
	@param VEC The vector to add to.
	@param VALUE The value that should be added.
*/
#define CVec_Add(TYPE, VEC, VALUE) CVec_Add_##TYPE(VEC, VALUE);

/**
	Remove an item from the end of the vector.
	
	@param TYPE The type of vector to pop from.
	@param VEC The vector to pop from.
	
	@returns The error code, 0 if fail, 1 if success.
*/
#define CVec_Pop(TYPE, VEC) CVec_Pop_##TYPE(VEC, NULL)

/**
	Remove an item from the end of the vector.

	@param TYPE The type of vector to pop from.
	@param VEC The vector to pop from.
	@param VALUE_PTR The pointer to the variable where the value popped off of the end of the vector is stored.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVec_PopV(TYPE, VEC, VALUE_PTR) CVec_Pop_##TYPE(VEC, VALUE_PTR)

/**
	Remove an item from the vector.

	@param TYPE The type of vector to remove from.
	@param VEC The vector to remove from.
	@param INDEX The index of the item to remove.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVec_Remove(TYPE, VEC, INDEX) CVec_Remove_##TYPE(VEC, INDEX, NULL)

/**
	Remove an item from the vector and obtain the value of the removed item.

	@param TYPE The type of vector to remove from.
	@param VEC The vector to remove from.
	@param INDEX The index of the item to remove.
	@param VALUE_PTR The pointer to the variable where the removed value will be stored.

	@returns The error code, 0 if fail, 1 if success.
*/
#define CVec_RemoveV(TYPE, VEC, INDEX, VALUE_PTR) CVec_Remove_##TYPE(VEC, INDEX, VALUE_PTR)

/**
	Get an item from the vector at a specified index.

	@param TYPE The type of vector to get a value from.
	@param VEC The vector to get a value from.
	@param INDEX The index of the item to get from the vector.

	@returns A pointer to the specified item.
*/
#define CVec_Get(TYPE, VEC, INDEX) CVec_Get_##TYPE(VEC, INDEX)

/**
	Free the memory used up by a vector.

	@param TYPE The type of vector.
	@param VEC The vector to free.
*/
#define CVec_Free(TYPE, VEC) CVec_Free_##TYPE(VEC)

/**
	Print a vector that is a primitive type to the console. (Mainly used for debugging)

	@param TYPE The type of the vector.
	@param VEC The vector.
	@param FORMAT  The format to use for printing. For example: With an int vector it would be " %d "
*/
#define CVec_Print_Primitive(TYPE, VEC, FORMAT) CVec_Print_Primitive_##TYPE(VEC, FORMAT)

#endif

#endif


#endif