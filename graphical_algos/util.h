#ifndef _UTIL_H
#define	_UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

int strtrimr(char *pszStr);
int strtriml(char *pszStr);
int strtrim(char *pszStr);

char *rTrim ( char * p );
char *lTrim ( char * p );
char *Trim ( char * p );

int max(int a , int b);

typedef struct boolean_store{
    unsigned int store_area;
    struct boolean_store *next_boolean_store;
}*pboolean_store;

typedef struct boolean_store_info{
    pboolean_store first_boolean_store;
    pboolean_store current_boolean_store;
    pboolean_store last_boolean_store;
    int booleans_in_store; /* number of boolean values in each
                            * boolean_store */
    int current_boolean_index; /* index of boolean value
                                * in the current boolean_store */
    int last_boolean_index; /* index of last boolean value
                             * in the last boolean_store
                             * used to to detect array end */
}*pboolean_store_info;

typedef pboolean_store_info boolean_array;

/* return a boolean data type that stores
 * the boolean values in individual bits
 * unoptimal for large sized arrays
 *
 * boolean=0 represents false
 * boolean=1 represents true recommended to use
 *      for consistency with store_next_boolean_value
 *      any value != 0 also works */
boolean_array new_boolean_array(int first_boolean_value);

/* store a boolean value */
void store_next_boolean_value(boolean_array b , unsigned int boolean_value);

/* read the next boolean value
 * return value
 * 0 false
 * 1 true
 * -1 no more boolean values - last one was read in a previous call */
int read_next_boolean_value(boolean_array b);

/* reset the boolean_array to point to the first boolean value in the array */
void reset_boolean_array(boolean_array b);

/* free memory */
void free_boolean_array(boolean_array *b);

#ifdef	__cplusplus
}
#endif

#endif
