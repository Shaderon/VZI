#pragma once
#include <stdlib.h>

typedef unsigned int uint;
typedef struct node node_t;
typedef int   data_t;

struct node
{
	node_t *prior;
	node_t *next;

	data_t *data;
};


int     push_back(const data_t data);
int     push_back_ptr(data_t *data);

int	    clear();
int	    erase(const uint n);

uint    get_size();
data_t* get_data(const uint n);
node_t* get_node(const uint n);




