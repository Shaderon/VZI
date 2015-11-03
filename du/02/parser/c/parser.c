#include "parser.h"

char* strsep(char** stringp, const char* delim)
{
    char* start = *stringp;
    char* p;

    p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL)
    {
        *stringp = NULL;
    }
    else
    {
        *p = '\0';
        *stringp = p + 1;
    }

    return start;
}

int fileSize(FILE* pFile)
{
    int sz = 0;
    fseek(pFile, 0L, SEEK_END);
    sz = ftell(pFile);
    fseek(pFile, 0L, SEEK_SET);

    return sz;
}

int getRowSize(char* line)
{
    int count = 0;
    char* runing = line;
    unsigned int i = 0;

    for (i = 0; i < strlen(line); i++, runing++)
    {
        if (*runing == ' ')
            count++;
    }

    return ++count;
}

int parseList(FILE* pf, int dimension, edgeData_t *list)
{
    char line[LINE_BUFFER_SZ];
    int i = 0;

    for (i = 0; i < dimension; ++i)
    {
        char* runing = NULL;
        int* row = NULL;
        int count = 0;

        fgets(line, sizeof(line), pf);
        runing = line;

        row = (int*)calloc(getRowSize(line), sizeof(int));
        if (!row) return 0;

        while (runing != NULL)
        {
            int num = atoi(strsep(&runing, " "));
            row[count] = num;

            count++;
        }

        list[i].size = count;
        list[i].row = row;
    }

    return 1;
}

void fixIndexing(edgeData_t *list, int dimension)
{
    int i = 0;
    int j = 0;
    int a = 0;

    for (i = 0; i < dimension; ++i)
    {
        int sz = list[i].size;

        for (j = 0; j < sz; ++j)
        {
            list[i].row[j]--;
        }
    }
}

int parse(char* input, Problem_t* problem)
{
    FILE* pf = NULL;
    int sz = 0;
    int ret = 0;

    char* name_buf = NULL;
    char* cmt_buf = NULL;
    char* direction_buf = NULL;
    int dimension = 0;

    char* label_buf[LINE_BUFFER_SZ];

    edgeData_t* edgeList = NULL;
    edgeData_t* weightList = NULL;

    if (!problem)
        goto error;

    pf = fopen(input, "r");
    if (!pf)
        goto error;

    sz = fileSize(pf);

    name_buf = (char*)calloc(LINE_BUFFER_SZ, sizeof(char));
    ret = fscanf(pf, "NAME : %s\n", name_buf);
    if (ret != 1)
        goto error;
    problem->name = name_buf;

    cmt_buf = (char*)calloc(LINE_BUFFER_SZ, sizeof(char));
    ret = fscanf(pf, "COMMENT : %[^\t\n]\n", cmt_buf);
    if (ret != 1)
        goto error;
    problem->comment = cmt_buf;

    direction_buf = (char*)calloc(32, sizeof(char));
    ret = fscanf(pf, "GRAPH : %s\n", direction_buf);
    if (ret != 1)
        goto error;

    if (strcmp(direction_buf, "DIRECTED") == 0)
        problem->directed = 1;
    else
        problem->directed = 0;

    ret = fscanf(pf, "DIMENSION : %d\n", &dimension);
    if (ret != 1)
        goto error;
    problem->dimension = dimension;

    // EDGE_DIRECTIONS_SECTION
    fgets(label_buf, LINE_BUFFER_SZ, pf);
    edgeList = (edgeData_t*)calloc(dimension, sizeof(edgeData_t));
    ret = parseList(pf, dimension, edgeList);
    if (ret != 1)
        goto error;
    
    // v souboru je indexovani od 1, ale pro nas je lepsi indexovat od 0
    // proto jej upravime 
    fixIndexing(edgeList, dimension); 
    
    problem->edgeList = edgeList;

    // EDGE_WEIGHT_SECTION
    fgets(label_buf, LINE_BUFFER_SZ, pf);
    weightList = (edgeData_t*)calloc(dimension, sizeof(edgeData_t));
    ret = parseList(pf, dimension, weightList);
    if (ret != 1)
        goto error;
    problem->weightList = weightList;

    return 1;

error:

    if (pf)
    {
        fclose(pf);
    }

    return 0;
}
