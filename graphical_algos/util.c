#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "util.h"

int strtrimr(char *pszStr){
      int   i, j;

      j = i = strlen(pszStr) - 1;
      while (isspace(pszStr[i]) && (i >= 0))
            pszStr[ i-- ] = '\0';

      return(j - i);
}

int strtriml(char *pszStr){
      int   i = 0, j;

      j = strlen(pszStr) - 1;
      while (isspace(pszStr[i]) && (i <= j))
            i++;

      if (0 < i)
            strcpy(pszStr, &pszStr[i]);

      return(i);
}


int strtrim(char *pszStr){
      int   iBlank;

      iBlank  = strtrimr(pszStr);
	  iBlank += strtriml(pszStr);

      return(iBlank);
}

char *rTrim ( char * p )
{
    char * temp;
    if (!p) return p;
    temp = (char *)(p + strlen(p)-1);
    while ( temp && isspace(*temp) ) temp--;
    *(temp+1) = '\0';
    return p;
}

char *lTrim ( char * p )
{
    while ( p && isspace(*p) ) p++ ;
    return p ;
}


char *Trim ( char * p )
{
    return lTrim(rTrim(p));
}

int max(int a , int b){
	return a > b ? a : b;
}

boolean_array new_boolean_array(int boolean_value){
    boolean_array b=malloc(sizeof(struct boolean_store_info));

    b->booleans_in_store=sizeof(unsigned int);
    
    b->current_boolean_index=1;
    b->last_boolean_index=1;
    
    b->first_boolean_store=malloc(sizeof(struct boolean_store));
    b->first_boolean_store->next_boolean_store=NULL;
    b->current_boolean_store=b->first_boolean_store;
    b->last_boolean_store=b->first_boolean_store;
    
    b->first_boolean_store->store_area=boolean_value;

    return b;
}

void store_next_boolean_value(boolean_array b , unsigned int boolean_value){
    
    pboolean_store aux_bs;

    b->last_boolean_index++;
    if(b->last_boolean_index > b->booleans_in_store){
        /* add a new boolean_store */
        aux_bs=malloc(sizeof(struct boolean_store));
        b->last_boolean_store->next_boolean_store=aux_bs;
        b->last_boolean_store=aux_bs;
        b->last_boolean_index=1;
    }

    /* shift left boolean_value to store place
     * complement to get all 1's except store place
     * bitwise and to store boolean_value in store_area */
    b->last_boolean_store->store_area &=
            ~(boolean_value << b->last_boolean_index);
}

int read_next_boolean_value(boolean_array b){

    unsigned int aux_1=1;

    b->current_boolean_index++;

    if(b->current_boolean_store == b->last_boolean_store &&
            b->current_boolean_index > b->last_boolean_index){

        return -1;
    }

    if(b->current_boolean_index > b->booleans_in_store){
        if(b->current_boolean_store == b->last_boolean_store){
            return -1;
        }

        b->current_boolean_store=
                b->current_boolean_store->next_boolean_store;
        b->current_boolean_index=1;
    }

    /* shift 1 left by boolean index
     * bitwise and make bits 0 except the one at boolean index
     * and shift right to get 0 or 1 for return */
    return (int)
            ((b->current_boolean_store->store_area &
            (aux_1 << b->current_boolean_index))
            >>
            b->current_boolean_index);
}

void reset_boolean_array(boolean_array b){
    b->current_boolean_store=b->first_boolean_store;
}

void free_boolean_array(boolean_array *b){
    pboolean_store aux;

    aux=(*b)->first_boolean_store;
    while(aux != NULL){
        (*b)->first_boolean_store=
                (*b)->first_boolean_store->next_boolean_store;
        free(aux);
        aux=(*b)->first_boolean_store;
    }
    
    free(*b);
    *b=NULL;
}
