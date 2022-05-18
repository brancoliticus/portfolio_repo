#ifndef _XPMLIB_H
#define	_XPMLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>

#include "data_structures.h"
			 
#define XPM_WHITE 0
#define XPM_BLACK 1
#define XPM_INPUT_COLOR 1000

typedef struct{
	unsigned char	r,g,b;
	unsigned char	*pchars;
}Color;

typedef struct{
	unsigned int	width;		/*width in number of pixels*/
	unsigned int	height;		/*height in number of pixels*/
	unsigned int	cpp;		/*number of characters per pixel*/
	unsigned int	ncolors;	/*number of used colors*/
	Color		*colta;		/*color table*/
	unsigned int	**data;		/*image represented by a table*/
                                        /*of indexes in the color table*/
}XPM;

XPM* initXPM(unsigned int width, unsigned int height,
        unsigned int cpp,
        unsigned int ncolors);
void freeXPM(XPM **imagine);
void setXPMColor(XPM *img, unsigned int index,
        unsigned char r, unsigned char g, unsigned char b,
        char *charpattern);
void putXPMpixel(XPM *imagine,
        unsigned int x, unsigned int y,
        unsigned int colorindex);
void writeXPMtofile(XPM *imagine , char *filepath);



void XPMline(XPM *img ,
        pp2 p , pp2 q ,
        unsigned int color);
void XPMlines(XPM *img , plistline2 rad , unsigned int color);
void XPMpoly(XPM *img , ppoly rad , unsigned int color);
void XPMpoly_fill(XPM *img , ppoly rad , unsigned int color);
void XPMlines_transform(XPM *img , plistline2 rad ,
	pm3 tr , unsigned int color);

/* the image and polygon points must have the same maximum height */
void XPMpoly_filee(XPM *img , ppoly rad , unsigned int color);
void XPMpoly_l_fill(XPM *img , ppoly_l rad , unsigned int color);

/*void zXPMline(XPM *img , point2 p , point2 q ,
			  double deptha , double depthb , double depthproj , double **zbuf);*/


#ifdef	__cplusplus
}
#endif

#endif	/* _XPMLIB_H */

