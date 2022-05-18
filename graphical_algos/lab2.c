/*arguments: -l2 -f lab2in.ps -w 200 -h 200 -o lab2out.xpm*/

#include <stdlib.h>
#include <string.h>

#include "lab2.h"

#include "data_structures.h"
#include "xpmlib.h"

void do_lab2(int argc , char *argv[]){
    XPM *img = NULL;
    plistline2 rad=NULL;
    unsigned int i, j, width = 0, height = 0;
    char psname[400] = "", xpmname[400] = "";

    for (i = 1; i < argc; i++) {


        if (strcmp(argv[i], "-o") == 0 && argc >= i + 1) {
            strcpy(xpmname, argv[i + 1]);
            i = i + 1;
        }
        else if (strcmp(argv[i], "-f") == 0 && argc >= i + 1) {
            strcpy(psname, argv[i + 1]);
            i = i + 1;
        }
        else if (strcmp(argv[i], "-w") == 0 && argc >= i + 1) {
            width = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i = i + 1;
        }
        else if (strcmp(argv[i], "-h") == 0 && argc >= i + 2) {
            height = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i = i + 1;
        }
    }

    img = initXPM(width, height, 1, 2);
    setXPMColor(img, 0, 0xFF, 0xFF, 0xFF, "a");
    setXPMColor(img, 1, 0x00, 0x00, 0x00, "n");


    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            putXPMpixel(img, i, j, 0);
        }
    }

    if (strcmp(psname, "") != 0) {
        rad=parsepsfile_to_line2_list(psname);
        XPMlines(img , rad , 1);
        free_line2_list(&rad);
        if (strcmp(xpmname, "") != 0) {
            writeXPMtofile(img, xpmname);
        }
    }

    freeXPM(&img);
}

