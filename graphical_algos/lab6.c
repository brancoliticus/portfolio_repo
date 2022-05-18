/*
 * arguments part1 : -l6 -p1 -f lab6in.pol -o lab6out.xpm
 *  -r red_component -g green_component -b blue_component
 *
 * arguments part2 : -l6 -p2 -f lab6in.pol -o lab6out.xpm
 * -wl window_left -wt window_top
 * -wr window_right -wb window_bottom
 * -vl viewport_left -vt viewport_top
 * -vr viewport_right -vb viewport_bottom
 * -r red_component -g green_component -b blue_component
 * -w xpm_width -h xpm_height
 *
 * actual arguments part1 : -l6 -p1 -f lab6in.pol -o lab6out.xpm -r red -g green -b blue
 *
 * actual arguments part2 : -l6 -p2 -f lab6in.pol -o lab6out.xpm -wl 0 -wr 1 -wb 2 -wt 3 -vl 4 -vr 5 -vb 6 -vt 7 -r 8 -g 9 -b 10 -w 11 -h 12
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lab6.h"
#include "xpmlib.h"
#include "graphics2d.h"

void do_lab6(int argc , char *argv[]){
    int i,j;
    
    int wl,wr,wb,wt;
    int vl,vr,vb,vt;
    unsigned char r,g,b;
    int w,h;
    char infilename[100],outfilename[100];

    int p1_or_p2;
    XPM *img;
    ppoly aux;
    
    ppoly_l rad1,rad2,rad3;
    ppoly_l_it poly_l_it;

    vl=-1 ; vr=-1 ; vb=-1 ; vt=-1;
    img=NULL;

    for(i=1 ; i<argc ; i++){
        if(strcmp(argv[i] , "-f")==0 && argc >= i+1){
            strcpy(infilename , argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i] , "-o")==0 && argc >= i+1){
            strcpy(outfilename , argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i] , "-wl")==0 && argc >= i+1){
            wl=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-wr")==0 && argc >= i+1){
            wr=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-wb")==0 && argc >= i+1){
            wb=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-wt")==0 && argc >= i+1){
            wt=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-vl")==0 && argc >= i+1){
            vl=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-vr")==0 && argc >= i+1){
            vr=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-vb")==0 && argc >= i+1){
            vb=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-vt")==0 && argc >= i+1){
            vt=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-r")==0 && argc >= i+1){
            r=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-g")==0 && argc >= i+1){
            g=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-b")==0 && argc >= i+1){
            b=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-w")==0 && argc >= i+1){
            w=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-h")==0 && argc >= i+1){
            h=strtol(argv[i+1],NULL,10);
            i++;
        }
        else if(strcmp(argv[i] , "-p1")==0 && argc >= i+1){
            p1_or_p2=1;
        }
        else if(strcmp(argv[i] , "--p2")==0 && argc >= i+1){
            p1_or_p2=2;
        }
    }

    if(vl==-1)vl=0;
    if(vr==-1)vr=w;
    if(vb==-1)vb=0;
    if(vt==-1)vt=h;

    img=initXPM(vr-vl+1 , vt-vb+1 , 1 , 3);
    setXPMColor(img , XPM_WHITE       ,0xFF , 0xFF , 0xFF , "a");
    setXPMColor(img , XPM_BLACK       ,0x00 , 0x00 , 0x00 , "n");
    setXPMColor(img , XPM_INPUT_COLOR , r   , g    ,    b , "c");

    for (i = 0; i <= vr - vl; i++)
        for (j = 0; j <= vt - vb; j++)
            putXPMpixel(img, i, j, XPM_WHITE);

    if(strcmp(infilename,"") != 0){
        /* read data from disk */
        aux=parsepolfile_to_polygon(infilename , h);

        /* do clipping to clipping window and visualisation transform */
        if(p1_or_p2 == 2){
            rad1=poly_clipping_weiler_atherton(aux,
                    wl,wr,wb,wt);
            freepoly(&aux);

            poly_l_it=newpoly_l_it(rad1);
            aux=next_poly_l_poly(poly_l_it);
            aux=move_origin_to(aux , vl , vb);
            rad2=newpoly_l(aux);
            while((aux=next_poly_l_poly(poly_l_it)) != NULL){
                aux=move_origin_to(aux , vl , vb);
                add_poly_to_poly_l(aux , &rad2);
            }
            freepoly_l(&rad1);
            freepoly_l_it(&poly_l_it);
            
            rad3=poly_l_2d_vis_transf(rad2 ,
                    wl , wr , wb , wt ,
                    vl , vr , vb , vt);
            freepoly_l(&rad2);
        }

        /* write xpm pixels from polygon data */
        if(p1_or_p2 == 1){
            XPMpoly_fill(img , aux , XPM_INPUT_COLOR);
            freepoly(&aux);
        }
        else{/* p1_o2_p2=2 rad2 have to use */
            XPMpoly_l_fill(img , rad3 , XPM_INPUT_COLOR);
            freepoly_l(&rad3);
        }
    }

    if(strcmp(outfilename,"") != 0)
        writeXPMtofile(img,outfilename);
    freeXPM(&img);
}
