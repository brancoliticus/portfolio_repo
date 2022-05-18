#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argc, char** argv) {
	if(argc > 1){

	if(! strcmp(argv[1] , "-l1")){
		do_lab1(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l2")){
		do_lab2(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l3")){
		do_lab3(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l4")){
		do_lab4(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l5")){
		do_lab5(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l6")){
		do_lab6(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l7")){
		do_lab7(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l8")){
		do_lab8(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l9")){
		do_lab9(argc-1 , argv+1);
        }
        if(! strcmp(argv[1] , "-l10")){
		do_lab10(argc-1 , argv+1);
        }

    }

    return (EXIT_SUCCESS);
}

