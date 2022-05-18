/*arguments: -l5 -p1 -f lab5in.pol -w 200 -h 200 -wl 50 -wt 50 -wr 150 -wb 150 -o lab5out.xpm
  for sutherland hodgman

  arguments: -l5 -p2 -f lab5in.pol -w 200 -h 200 -wl 50 -wt 50 -wr 150 -wb 150 -o lab5out.xpm
  for weiler atherton
 */

#include <string.h>
#include <stdlib.h>

#include "lab5.h"
#include "graphics2d.h"
#include "data_structures.h"

#define WHITE 0
#define BLACK 1

void do_lab5(int argc, char *argv[]) {
    XPM *img = NULL;
    unsigned int i, j, width = 0, height = 0;
    unsigned int left = 0, right = 0, top = 0, bottom = 0;
    char polname[400] = "", xpmname[400] = "";
    ppoly rad = NULL, aux = NULL;
    ppoly_l rad1;
    ppoly_l_it poly_l_it;

    int sh_or_wa = 0; /* 1 sutherland hodgman 2 weiler atherton */

    for (i = 1; i < argc; i++) {


        if (strcmp(argv[i], "-o") == 0 && argc >= i + 1) {
            strcpy(xpmname, argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-w") == 0 && argc >= i + 1) {
            width = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-h") == 0 && argc >= i + 1) {
            height = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-wl") == 0 && argc >= i + 1) {
            left = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-wr") == 0 && argc >= i + 1) {
            right = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-wt") == 0 && argc >= i + 1) {
            top = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-wb") == 0 && argc >= i + 1) {
            bottom = (unsigned int) strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-f") == 0 && argc >= i + 1) {
            strcpy(polname, argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-p1") == 0) {
            sh_or_wa = 1;
        }
        else if (strcmp(argv[i], "-p2") == 0) {
            sh_or_wa = 2;
        }
    }

    top = height - top;
    bottom = height - bottom;

    img = initXPM(right - left + 1, top - bottom + 1, 1, 2);

    setXPMColor(img, 0, 0xFF, 0xFF, 0xFF, "a");
    setXPMColor(img, 1, 0x00, 0x00, 0x00, "n");


    for (i = 0; i <= right - left; i++) {
        for (j = 0; j <= top - bottom; j++) {
            putXPMpixel(img, i, j, 0);
        }
    }

    if (strcmp(polname, "") != 0) {
        aux = parsepolfile_to_polygon(polname, height);

        if (sh_or_wa == 1) {
            rad = polygon_clipping_sutherland_hodgman(aux,
                    left, right, bottom, top);
            freepoly(&aux);

            aux = move_origin_to(rad, left, bottom);

            XPMpoly(img, aux, 1);
            freepoly(& rad);
            freepoly(& aux);
        } else if (sh_or_wa == 2) {
            rad1 = poly_clipping_weiler_atherton(aux,
                    left, right, bottom, top);
            freepoly(&aux);

            poly_l_it=newpoly_l_it(rad1);
            while((aux=next_poly_l_poly(poly_l_it)) != NULL){
                rad=aux;
                aux=move_origin_to(rad , left , bottom);
                XPMpoly(img,aux,1);
                freepoly(&aux);
            }
            freepoly_l_it(&poly_l_it);
            freepoly_l(&rad1);
        }

        
    }

    if (strcmp(xpmname, "") != 0) {
        writeXPMtofile(img, xpmname);
    }

    freeXPM(&img);
}

