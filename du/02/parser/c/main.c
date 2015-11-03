#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "parser.h"

#ifdef _MSC_VER
#define  _CRT_SECURE_NO_WARNINGS
#endif


int main(int argc, char *argv[])
{
    Problem_t prob;
    int i = 0;
    int j = 0;

    if (!parse("test.map", &prob))
        exit(1);

    printf("Name: %s \n", prob.name);
    printf("Commentary: %s \n", prob.comment);
    printf("Dimension: %d \n", prob.dimension);
    printf("Directed: %s \n", (prob.directed ? "true" : "false"));
    printf("\n");

    printf("Edges \n");
    for (i = 0; i < prob.dimension; ++i)
    {
        printf("%d -> ", i);
        for (j = 0; j < prob.edgeList[i].size; ++j)
        {
            printf("%d ", prob.edgeList[i].row[j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("Edges weights \n");
    for (i = 0; i < prob.dimension; ++i)
    {
        printf("%d -> ", i);
        for (j = 0; j < prob.weightList[i].size; ++j)
        {
            printf("%d ", prob.weightList[i].row[j]);
        }
        printf("\n");
    }
    printf("\n\n");
    
    // clean up
    for (i = 0; i < prob.dimension; ++i)
    {
        free(prob.edgeList[i].row);
        free(prob.weightList[i].row);
    }

    free(prob.edgeList);
    free(prob.weightList);
    free(prob.comment);
    free(prob.name);


    return 0;
}
