# CVector
CVector is a very simple vector library for the C programming language.

## Installation
All the code for CVector is contained in the `CVector.h` file. Just download that file and put it in your project.

## General Usage
Unlike other Vector libraries, CVector creates a struct and set of functions for each data type you want to use. So, you must first initalize the vector for the data types you wish to use using the `Initialize_Vector()` macro.
```c
#include "CVector.h"

InitializeVector(int)
InitializeVector(float)
```

That will create the struct and functions needed to use the vector for those data types. The struct is name `Vector_(type)`, so for an int vector: `Vector_int`. You can also use the `Vector(int)` macro.  
  
The functions are labeled in a similar format: `CVec_[Operation]_[type]()`. Valid operations are: `Resize`, `Add`, `Pop`, `Remove`, `Get`, `Free`, and `Print_Primitive`. The only function that does not follow this format is the one used to create the vector struct for use: `CreateVector_[type]()`.  
  
There are also macros to simplify the functions. They have the following format: `CVec_[Operation]([type], ...)`. **Note:** The helper macros can be disabled by putting `#define CVEC_NO_MACRO` before the inclusion of the header file. You can also define the naming convention used by defining a macro before the inclusion of the header file. The options are: `#define CVEC_UPPERCASE` and `#define CVEC_CAMMELCASE`, which will format the macros as `CVec[Operation]` and `cVec[Operation]` respectively. Not including either definitions will default to the underscore format shown above.

### General Example
```C
#define CVEC_UPPERCASE
#include "CVector.h"

InitializeVector(int);

int main (char** args, int argv) {
    Vector(int) vec = CreateVector(int);
    
    CVecAdd(int, &vec, 5);
    CVecAdd(int, &vec, 10);
    CVecAdd(int, &vec, 20);
    
    CVecPrintPrimitive(int, &vec, " %d ");
    
    CVecPop(int, &vec);
    CVecRemove(int, &vec, 0);
    
    printf("Size of Vector: %d", vec.count);
    CVecFree(int, &vec);
    
    return 0;
}
```
