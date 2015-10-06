/**
*
*	Jednosmerny seznam
*	
*	This file is part of the 0VP course 
*
*	New BSD License
*	https://www.vutbr.cz/studis/student.phtml?gm=gm_detail_predmetu&apid=158780
*
*	C language is all about speed. Hot, nasty, bad-ass speed. - Eleanor Roosevelt, 1936.
*/

#if _MSC_VER
#define  _CRT_SECURE_NO_WARNINGS
#endif

#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    struct node *next;
    int   data;
} node_t;

// globalni promene, ktere budou udrzovat nas seznam
node_t *Head = NULL;
node_t *Last = NULL;
unsigned int Size = 0;


// projdeme seznam a vratime ptr na uzel na pozadovanem indexu nebo NULL
node_t* at(const unsigned int idx)
{
    node_t *result = NULL;

    if (idx == 0)
        result = Head;
    else if (idx < Size)
    {
        unsigned int i = 0;
        node_t *node = Head;

        for (i = 0; i < idx; ++i)
            node = node->next;

        result = node;
    }

    return result;
}

// funkce pro ziskani dat z uzlu na danem indexu
// fce. vraci uspesnost fce, data se ziskaji jako ptr v druhem argumentu
int get_data(const unsigned int idx, int *data)
{
    int result = 0;
    node_t *node = at(idx);

    if (node)
    {
        *data = node->data;
        result = 1;
    }

    return result;
}

// pridame do seznamu novy uzel 
int push_back(const int data)
{
    node_t *tmp = (node_t *)malloc(sizeof(node_t));
    int result = 0;

    if(tmp)
    {
        tmp->data = data;
        tmp->next = NULL;

        // List je prazdny, nove vytvoreny uzel tak bude tvorit zacatek 
        // (a zaroven i konec) noveho seznamu
        if(Head == NULL)
        {
            Last = Head = tmp;
        } 
        else
        {
            // pokud uz seznam obsahuje nejake uzly, 
            // je novy uzel pridan na jeho konec 
            Last->next = tmp;
            Last = tmp;
        }

        Size++;
        result = 1;
    }

    return result;
}

void print_list()
{
    node_t *node = Head;
    while(node)
    {
        printf("%d \n", node->data);
        node = node->next;
    }

}

// v teto funkci pridame uzel do seznamu na danou pozici (pocitame od 0)
// fce vraci 1 v pripade uspechu 
int insert(const unsigned int idx, int data)
{
    int result = 0;

    if (idx > 0 && idx < Size)
    {
        node_t *new_node = (node_t *)malloc(sizeof(node_t));

        if (new_node)
        {
            new_node->data = data;
            if (idx == 0)
            {
                new_node->next = Head;
                Head = new_node;
            }
            else
            {
                // najdeme si uzzel ktery predchazi uzlu na danem indexu a
                // hodnotu next ulozime do noveho uzlu, nasledne prepiseme
                // hodnotu next u tohoto predchoziho uzlu tak aby ukazoval 
                // na nove vytvoreny uzel
                node_t *prior_node = at(idx - 1);
                new_node->next = prior_node->next;
                prior_node->next = new_node;
            }
            Size++;
            result = 1;
        }
    }
    // tohle neni uplne nejvhodnejsi reseni 
    // slo by to resit podobne jako v matlabu, tj. cyklus by nam doplnil 
    // pripadne chybejici prvky
    //else if (idx >= Size)
    //    result = push_back(data);

    return result;
}

int remove_item(const unsigned int idx)
{
    int result = 0;

    if (idx < Size)
    {
        if (idx == 0)
        {
            // mame odstranit Head
            node_t *node = Head;
            Head = Head->next;
            free(node);
        }
        else
        {
            node_t *node = at(idx - 1);

            node_t *next_node = node->next->next;
            free(node->next);
            node->next = next_node;
        }

        Size--;
        result = 1;
    }

    return result;
}

void clear()
{
    while (Head)
    {
        // pred uvolnenim prvniho uzlu si ulozime ptr na nej do pomocne
        // prom. a Head posuneme na dalsi uzel v seznamu, az pote muzeme
        // uzel uvolnit
        node_t *node = Head;
        Head = Head->next;

        free(node);
        Size--;
    }

    // na zaver nastavime Head a Lst na NULL
    Last = Head = NULL;
}

void print_list_reverse()
{
    int i = 0;

    for (i = Size - 1; i >= 0; --i)
    {
        int data = 0;

        if (get_data(i, &data))
                printf("Item [%d]->data = %d \n", i, data);
        else
            printf("Item [%d] not found!\n", i);
    }
}

void print_list_custom(const node_t *start)
{
    node_t *node = Head;
    while (node != start)
        node = node->next;
        
    while (node)
    {
        printf("%d \n", node->data);
        node = node->next;
    }
}

int main(int argc, char *argv[])
{
    int i = 0;
    
    printf("Single linked list demo\n\n");

    push_back(0);
    push_back(1);
    push_back(2);

    insert(2, 8);

    print_list();

    printf("---------\n");
    remove_item(2);
    print_list();

    printf("---------\n");
    for (i = 3; i < 10; ++i)
        push_back(i);

    print_list();


    printf("---------\n");
    print_list_reverse();

    printf("---------\n");
    print_list_custom(at(1));

    clear();

	return 0;
}