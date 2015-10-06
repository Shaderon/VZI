/**
*
*	Obousmerny seznam
*	
*	This file is part of the VZI course 
*
*	New BSD License
*	https://www.vutbr.cz/studis/student.phtml?gm=gm_detail_predmetu&apid=158780
*
*	C language is all about speed. Hot, nasty, bad-ass speed. - Eleanor Roosevelt, 1936.
*/

#ifdef _MSC_VER
#define  _CRT_SECURE_NO_WARNINGS
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "node_t.h"


void print_list()
{
    uint i = 0;
    uint sz = get_size();

    for (i = 0; i < sz; ++i)
    {
        data_t* data = get_data(i);
        printf("%d \n", (int) *data);
    }

}

int main(int argc, char *argv[])
{
    push_back(1);
    push_back(2);
    push_back(3);

    print_list();

    printf("%d \n", (int) *get_data(1));

    clear();

	return 0;
}