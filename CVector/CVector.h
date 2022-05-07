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
#include <stdarg.h>

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
	vec.buffer = (TYPE*)calloc(10, sizeof(TYPE));\
	return vec;\
}

#define CVector_Func_Create_Malloc(TYPE) \
Vector_##TYPE* mallocCreateVector_##TYPE() {\
	Vector_##TYPE* vec = (Vector_##TYPE*)malloc(sizeof(Vector_##TYPE));\
	vec->count = 0;\
	vec->bufferSize = 10;\
	vec->bufferAmount = 10;\
	vec->buffer = (TYPE*)calloc(10, sizeof(TYPE));\
	return vec;\
}

#define CVector_Func_Resize(TYPE) \
void CVec_Resize_##TYPE(Vector_##TYPE* vec, int resizeTo) {\
	if(resizeTo < 0) return;\
	TYPE* bufStart = vec->buffer;\
	vec->bufferSize = resizeTo;\
	vec->buffer = (TYPE*)realloc(vec->buffer, sizeof(TYPE) * vec->bufferSize);\
	if(vec->buffer == NULL) { \
		vec->buffer = bufStart; \
	} \
}

#define CVector_Func_Add(TYPE) \
void CVec_Add_##TYPE(Vector_##TYPE* vec, ##TYPE valueToAdd) {\
	if (vec->count >= vec->bufferSize) {\
		CVec_Resize_##TYPE(vec, vec->bufferSize + vec->bufferAmount);\
	}\
	vec->buffer[vec->count] = valueToAdd;\
	vec->count++;\
}

#define CVector_Func_Add_All(TYPE) \
void CVec_Add_All_##TYPE(Vector_##TYPE* vec, int count, ...) {\
	va_list args;\
	int i;\
	va_start(args, count);\
	for (i = 0; i < count; i++) {\
		CVec_Add_##TYPE(vec, va_arg(args, TYPE));\
	}\
	va_end(args);\
}

#define CVector_Func_Add_Array(TYPE) \
void CVec_Add_Array_##TYPE(Vector_##TYPE* vec, TYPE* arr, int count) {\
	CVec_Resize_##TYPE(vec, ((int)((vec->count + count) / 10) + 1) * 10);\
	memcpy(vec->buffer + vec->count, arr, sizeof(TYPE) * count);\
	vec->count += count;\
}

#define CVector_Func_Add_Vector(TYPE) \
void CVec_Add_Vector_##TYPE(Vector_##TYPE* vec, Vector_##TYPE* vecToAdd) {\
	CVec_Resize_##TYPE(vec, ((int)((vec->count + vecToAdd->count) / 10) + 1) * 10);\
	memcpy(vec->buffer + vec->count, vecToAdd->buffer, sizeof(TYPE) * vecToAdd->count);\
	vec->count += vecToAdd->count;\
}

#define CVector_Func_Insert(TYPE) \
TYPE CVec_Insert_##TYPE(Vector(TYPE)* vec, size_t index, TYPE value) {\
	if (index < 0 || index > vec->count) return 0;\
	if (vec->count >= vec->bufferSize) {\
		CVec_Resize_##TYPE(vec, vec->bufferSize + vec->bufferAmount);\
	}\
	memcpy(vec->buffer + index + 1, vec->buffer + index, sizeof(TYPE) * (vec->count - index));\
	vec->buffer[index] = value;\
	vec->count++;\
	return 1;\
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
#define InitializeVector(TYPE) CVector_Struct(TYPE) CVector_Func_Create(TYPE) CVector_Func_Create_Malloc(TYPE) CVector_Func_Resize(TYPE) CVector_Func_Add(TYPE) CVector_Func_Add_All(TYPE) CVector_Func_Add_Array(TYPE) CVector_Func_Add_Vector(TYPE) CVector_Func_Insert(TYPE) CVector_Func_Pop(TYPE) CVector_Func_Remove(TYPE) CVector_Func_Get(TYPE) CVector_Func_Free(TYPE) CVector_Func_Print_Primitive(TYPE)
#elif defined CVEC_CAMELCASE
/**
	This macro will insert in the vector's struct and its helper functions for the specified type.

	@param TYPE The type of vector to create.
*/
#define initializeVector(TYPE) CVector_Struct(TYPE) CVector_Func_Create(TYPE) CVector_Func_Create_Malloc(TYPE) CVector_Func_Resize(TYPE) CVector_Func_Add(TYPE) CVector_Func_Add_All(TYPE) CVector_Func_Add_Array(TYPE) CVector_Func_Add_Vector(TYPE) CVector_Func_Insert(TYPE) CVector_Func_Pop(TYPE) CVector_Func_Remove(TYPE) CVector_Func_Get(TYPE) CVector_Func_Free(TYPE) CVector_Func_Print_Primitive(TYPE)
#else
/**
	This macro will insert in the vector's struct and its helper functions for the specified type.

	@param TYPE The type of vector to create.
*/
#define Initialize_Vector(TYPE) CVector_Struct(TYPE) CVector_Func_Create(TYPE) CVector_Func_Create_Malloc(TYPE) CVector_Func_Resize(TYPE) CVector_Func_Add(TYPE) CVector_Func_Add_All(TYPE) CVector_Func_Add_Array(TYPE) CVector_Func_Add_Vector(TYPE) CVector_Func_Insert(TYPE) CVector_Func_Pop(TYPE) CVector_Func_Remove(TYPE) CVector_Func_Get(TYPE) CVector_Func_Free(TYPE) CVector_Func_Print_Primitive(TYPE)
#endif


/*
	======================================

			   Helper Macros

	======================================
*/

#ifndef CVEC_NO_MACRO

/**
	Helper macro for an easy for each.

	@param TYPE The type of vector to loop through.
	@param VEC The vector to loop through.
	@param NAME The name of the variable which contains the current item in the vector.
*/
#define CVEC_FOR_EACH(TYPE, VEC, NAME, INNER_CONTENT) { \
	int cvecForEachI; \
	for (cvecForEachI = 0; cvecForEachI < (VEC)->count; cvecForEachI++) { \
		TYPE NAME = (VEC)->buffer[cvecForEachI]; \
		INNER_CONTENT \
	}\
}


#ifdef CVEC_UPPERCASE
// Macro Definitions using uppercase


/**
	Create a vector of the specified type.

	@param TYPE The type of vector to create.

	@returns A struct created on the stack.
*/
#define CreateVector(TYPE) CreateVector_##TYPE()

/**
	Allocate and create a vector of the specified type on the heap.  

	Note: this must be freed using CVecFree() followed by free().

	@param TYPE The type of vector to create.

	@returns A pointer to the vector struct created on the heap.
*/
#define MallocVector(TYPE) mallocCreateVector_##TYPE()

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
#define CVecAdd(TYPE, VEC, VALUE) CVec_Add_##TYPE(VEC, VALUE)

/**
	Add a list of items to a vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param COUNT The number of items to add.
	@param __VA_ARGS__ The list of items to add (must be the same amount as specified by the count argument).
*/
#define CVecAddAll(TYPE, VEC, COUNT, ...) CVec_Add_All_##TYPE(VEC, COUNT, __VA_ARGS__)

/**
	Add an entire array to a vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param ARRAY The array to add. (Not Mutated)
	@param SIZE The size of the array.
*/
#define CVecAddArray(TYPE, VEC, ARRAY, SIZE) CVec_Add_Array_##TYPE(VEC, ARRAY, SIZE)

/**
	Add an entire vector to another vector.

	@param TYPE The type of both Vectors.
	@param VEC The base vector that will be added to.
	@param ADD_VEC The vector which all of its items will be copied into VEC. (Not Mutated)
*/
#define CVecAddVector(TYPE, VEC, ADD_VEC) CVec_Add_Vector_##TYPE(VEC, ADD_VEC)

/**
	Insert an item into the vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param INDEX The index to insert the item at.
	@param VALUE The value to insert into the Vector.

	@returns 0 if fail, 1 is success.
*/
#define CVecInsert(TYPE, VEC, INDEX, VALUE) CVec_Insert_##TYPE(VEC, INDEX, VALUE)

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

#elif defined CVEC_CAMELCASE

/**
	Create a vector of the specified type.

	@param TYPE The type of vector to create.

	@returns A struct created on the stack.
*/
#define createVector(TYPE) CreateVector_##TYPE()

/**
	Allocate and create a vector of the specified type on the heap.

	Note: this must be freed using cVecFree() followed by free().

	@param TYPE The type of vector to create.

	@returns A pointer to the vector struct created on the heap.
*/
#define mallocVector(TYPE) mallocCreateVector_##TYPE()

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
#define cVecAdd(TYPE, VEC, VALUE) CVec_Add_##TYPE(VEC, VALUE)

/**
	Add a list of items to a vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param COUNT The number of items to add.
	@param __VA_ARGS__ The list of items to add (must be the same amount as specified by the count argument).
*/
#define cVecAddAll(TYPE, VEC, COUNT, ...) CVec_Add_All_##TYPE(VEC, COUNT, __VA_ARGS__)

/**
	Add an entire array to a vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param ARRAY The array to add. (Not Mutated)
	@param SIZE The size of the array.
*/
#define cVecAddArray(TYPE, VEC, ARRAY, SIZE) CVec_Add_Array_##TYPE(VEC, ARRAY, SIZE)

/**
	Add an entire vector to another vector.

	@param TYPE The type of both Vectors.
	@param VEC The base vector that will be added to.
	@param ADD_VEC The vector which all of its items will be copied into VEC. (Not Mutated)
*/
#define cVecAddVector(TYPE, VEC, ADD_VEC) CVec_Add_Vector_##TYPE(VEC, ADD_VEC)

/**
	Insert an item into the vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param INDEX The index to insert the item at.
	@param VALUE The value to insert into the Vector.

	@returns 0 if fail, 1 is success.
*/
#define cVecInsert(TYPE, VEC, INDEX, VALUE) CVec_Insert_##TYPE(VEC, INDEX, VALUE)

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
	Allocate and create a vector of the specified type on the heap.

	Note: this must be freed using CVec_Free() followed by free().

	@param TYPE The type of vector to create.

	@returns A pointer to the vector struct created on the heap.
*/
#define Malloc_Vector(TYPE) mallocCreateVector_##TYPE()

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
#define CVec_Add(TYPE, VEC, VALUE) CVec_Add_##TYPE(VEC, VALUE)

/**
	Add a list of items to a vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param COUNT The number of items to add.
	@param __VA_ARGS__ The list of items to add (must be the same amount as specified by the count argument).
*/
#define CVec_Add_All(TYPE, VEC, COUNT, ...) CVec_Add_All_##TYPE(VEC, COUNT, __VA_ARGS__)

/**
	Add an entire array to a vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param ARRAY The array to add. (Not Mutated)
	@param SIZE The size of the array.
*/
#define CVec_Add_Array(TYPE, VEC, ARRAY, SIZE) CVec_Add_Array_##TYPE(VEC, ARRAY, SIZE)

/**
	Add an entire vector to another vector.

	@param TYPE The type of both Vectors.
	@param VEC The base vector that will be added to.
	@param ADD_VEC The vector which all of its items will be copied into VEC. (Not Mutated)
*/
#define CVec_Add_Vector(TYPE, VEC, ADD_VEC) CVec_Add_Vector_##TYPE(VEC, ADD_VEC)

/**
	Insert an item into the vector.

	@param TYPE The type of Vector.
	@param VEC The vector to add to.
	@param INDEX The index to insert the item at.
	@param VALUE The value to insert into the Vector.

	@returns 0 if fail, 1 is success.
*/
#define CVec_Insert(TYPE, VEC, INDEX, VALUE) CVec_Insert_##TYPE(VEC, INDEX, VALUE)

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