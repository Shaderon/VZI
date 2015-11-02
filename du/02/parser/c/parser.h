#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

#ifdef _MSC_VER
#define  _CRT_SECURE_NO_WARNINGS
#endif

typedef struct
{
    int size;
    int *row;
} edgeData_t;

typedef struct
{
    char       *name;      // nazev grafu
    char       *comment;   // pripadny komentar ke grafu
    int         dimension; // velikost grafu
    int         directed;  // je graf orientovany or not?
    edgeData_t *edgeList;  // matice, kde kazdy radek (radek 0 je uzel 0 atd.)
                           // je pole structu edgeData_t, ktery ma polozky size
                           // a pa samotne pole hodnot
    edgeData_t *weightList;// to same co predchozi jen obsahuje ohodnoceni dane hrany
} Problem_t;

#define LINE_BUFFER_SZ 500

int parse(char *input, Problem_t *problem);
