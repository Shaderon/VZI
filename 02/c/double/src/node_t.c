#include "node_t.h"
#include "stdio.h"

node_t *pFirst = NULL; 
node_t *pLast  = NULL; 

uint size = 0;


node_t* front()
{
	return pFirst;
}

node_t* back()
{
    return pLast;
}

uint get_size()
{
    return size;
}

// vraci ukazatel na node na pozadovanem indexu
node_t* at(const uint n)
{
	uint i;
	node_t *pCurrent = front(); // jsme na prvnim node

    for (i = 0; i < n; i++)
    {
        pCurrent = pCurrent->next;
    }

    return pCurrent;
}

// pridani dat na konec seznamu pomoci ukazatele
int push_back_ptr(data_t* data)
{
    	node_t *pNew;
    	pNew = (node_t *) malloc(sizeof(node_t));
    
    	if (pNew == NULL)
        {
    		printf("Cannot allocate node. \n");
    		return 0;
    	}
    
    	// pokud je posledni node NULL (tj. pridavame prvni node)
    	// nemuzeme do nej ukladat
    
    	if(pFirst == NULL)
    	{
    		pFirst = pNew;
    	}
    	
    	if(pLast) 
    		pLast->next = pNew;
    
        // nastavime hodnoty
    	pNew->prior = pLast;
    	pNew->next  = NULL;
    	pNew->data  = data;
    
    	// zvysime velikost seznamu o 1
    	size++;
    	// nastavime novy uzel jako last
    	pLast = pNew;

    	return 1;
}

// ulozime data do seznamu, resp. vytvorime novou promenou typu data_t a 
// tu teprv ulozime do seznamu
int push_back(data_t data)
{
    data_t *temp = (data_t *)malloc(sizeof(data_t));

    if (!temp) 
    {
        printf("Cannot allocate memory for data! \n");
        return 0;
    }

    *temp = data;
    return push_back_ptr(temp);
}


data_t* get_data(uint n)
{
    if (n >= 0 && n < size)
    {
        node_t *node = at(n);
        if (node)
            return node->data;
    }
    	
    return NULL;
}

// smazani pouze jednoho node ze seznamu
int erase(uint n)
{
	node_t *node = at(n);
	node_t *tmp;
		
	// pokud je node NULL nemuzeme jej smazat
	if (!node)
		return 0;

	// pred samotnym smazanim node musime 
	// upravit ukazatele na dalsi node, jako je predchozi a nasledujici
	if (node->prior != NULL)
	{
		// pokud je pred nasim uzel jeste jeden uzel 
		// a zaroven po nasem uzlu k smazani dalsi uzel
		// musime zajistit uvolneni naseho uzlu a napojeni techto dvou uzlu
		if(node->next != NULL)
		{
			node->prior->next = node->next;
			node->next->prior = node->prior;
			tmp = node->next;
		}
		else
		{
			// pokud neni po nasem uzlu jiz dalsi uzel
			node->prior->next = NULL;
			pLast = tmp = node->prior;
		}
	}
	else
	{
		// pred nasim uzlem neni jiz uzel
		// ale jeste nas uzel muze ukazovat na dalsi uzel 
		// proto v tomto nasledujicim uzlu 
		// musime nastavit ze je prior jiz NULL
		if (node->next != NULL)
		{
			node->next->prior = NULL;
			pFirst = tmp = node->next;
		} 
		else // pokud se jedna o posledni uzel
			tmp = NULL;
	}

    if(node->data)
        free(node->data);

	free(node);
	node = NULL;
	size--;
    
	return 1;
}

// smazani vsech uzlu v seznamu
int clear()
{
    if (size <= 0) return 0;
    
    while (size)
        erase(0);

	return 1;
}
