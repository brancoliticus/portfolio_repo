/*arguments: -l4 -f lab4in.ps -w 200 -h 200 -o lab4out.xpm -t ./transforms_lab4.tsf */

/*
 *
 *-----------------------------------------------------------------------
 * note about the 2d transformations file :
 * the transformations are applied backwards to the image
 * so the last transformation in file is the first one to be applied
 * and the first one in file the last one to be applied
 *
 * ex:
 * translate 100 100
 * rotate 200 200 90 clockwise in image , trigonometric internally (because of
 * the image library)
 * translate -100 -100
 * to rotate an image around point 100 100 by 90 degrees
 *
 * would be in the transformations file :
 * t -100 -100
 * r 200 200 90
 * t 100 100
 *
 * without the reversed file order there would be a translation by -100 -100 ,
 * then a rotation around 200 200 ie at +300 +300 from the desired spot in the
 * image layout and than a translation by 100 100
 *----------------------------------------------------------------------------
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab4.h"
#include "xpmlib.h"
#include "data_structures.h"

void do_lab4(int argc , char *argv[]){

	XPM *img = NULL;
	plistline2 rad=NULL;
	unsigned int i, j, width = 0, height = 0;
	char psname [400] = "", trname[400] = "", xpmname[400] = "";
	pm3 transform_matrice=NULL;

	for (i = 1; i < argc; i = i + 1) {


		if (strcmp(argv[i], "-o") == 0 && argc >= i + 1) {
			strcpy(xpmname, argv[i + 1]);
			i = i + 1;
		}
		else if (strcmp(argv[i], "-t") == 0 && argc >= i + 1) {
			strcpy(trname, argv[i + 1]);
			i = i + 1;
		}
		else if (strcmp(argv[i], "-w") == 0 && argc >= i + 1) {
			width = (unsigned int) strtol(argv[i + 1], NULL, 10);
			i = i + 1;
		}
		else if (strcmp(argv[i], "-h") == 0 && argc >= i + 1) {
			height = (unsigned int) strtol(argv[i + 1], NULL, 10);
			i = i + 1;
		}
		else if (strcmp(argv[i], "-f") == 0 && argc >= i + 1) {
			strcpy(psname, argv[i + 1]);
			i = i + 1;
		}
	}

	img = initXPM(width + 1, height + 1, 1, 2);
	setXPMColor(img, 0, 0xFF, 0xFF, 0xFF, "a");
	setXPMColor(img, 1, 0x00, 0x00, 0x00, "n");


	for (i = 0; i <= width; i++) {
		for (j = 0; j <= height; j++) {
			putXPMpixel(img , i , j , 0);
		}
	}

	if (strcmp(psname , "") != 0) {
		rad = parsepsfile_to_line2_list(psname);
		transform_matrice=parse_transformations_file(trname);

		XPMlines_transform(img , rad , transform_matrice , 1);

		free_line2_list(&rad);
                freem3(&transform_matrice);
                if (strcmp(xpmname , "") != 0) {
			writeXPMtofile(img , xpmname);
		}
	}

	if (strcmp(xpmname, "") != 0) {
		writeXPMtofile(img , xpmname);
	}
	
	freeXPM(&img);

}

