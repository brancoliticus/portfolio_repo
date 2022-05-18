/*arguments : -l3 -f lab3in.ps -w 200 -h 200 -wl 50 -wr 150 -wb 150 -wt 50 -o lab3out.xpm*/

#include <stdlib.h>
#include <string.h>

#include "lab3.h"

#include "xpmlib.h"
#include "data_structures.h"
#include "graphics2d.h"

void do_lab3(int argc , char *argv[]){
	XPM *img=NULL;
	unsigned int i , j , width=0 , height=0 , top=0 , bottom=0 , left=0 , right=0;
	char psname[400]="" , xpmname[400]="";
        plistline2 rad=NULL;

	for(i=1 ; i < argc ; i++){


		if( strcmp(argv[i] , "-o") == 0  && argc >= i+1){
			strcpy(xpmname , argv[i+1]);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-f") == 0  && argc >= i+1){
			strcpy(psname , argv[i+1]);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-w") == 0  && argc >= i+1){
			width=(unsigned int) strtol(argv[i+1] , NULL , 10);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-h") == 0  && argc >= i+1){
			height=(unsigned int) strtol(argv[i+1] , NULL , 10);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-wl") == 0  && argc >= i+1){
			left=(unsigned int) strtol(argv[i+1] , NULL , 10);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-wr") == 0  && argc >= i+1){
			right=(unsigned int) strtol(argv[i+1] , NULL , 10);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-wt") == 0  && argc >= i+2){
			top=(unsigned int) strtol(argv[i+1] , NULL , 10);
			i=i+1;
		}

		else if( strcmp(argv[i] , "-wb") == 0  && argc >= i+1){
			bottom=(unsigned int) strtol(argv[i+1] , NULL , 10);
			i=i+1;
		}
	}
	
	top=height-top;
	bottom=height-top;

	img=initXPM( right - left + 1 , top - bottom + 1 , 1 , 2);
	setXPMColor(img , 0 , 0xFF , 0xFF , 0xFF , "a");
	setXPMColor(img , 1 , 0x00 , 0x00 , 0x00 , "n");


	for(i=0 ; i < right - left + 1 ; i++){
		for(j=0 ; j < top - bottom + 1 ; j++){
			putXPMpixel(img, i , j , 0);
		}
	}

	if(strcmp(psname , "") != 0){
            rad=parsepsfile_to_line2_list(psname);
            clip_lines_to_image(&rad , img , 1 , left , right , bottom , top);
            free_line2_list(&rad);
	}

	if(strcmp(xpmname , "") != 0){
		writeXPMtofile(img , xpmname);
	}

	freeXPM(&img);

}

