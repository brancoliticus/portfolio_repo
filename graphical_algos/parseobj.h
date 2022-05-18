#ifndef _PARSEOBJ_H
#define	_PARSEOBJ_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "xpmlib.h"
#include "stdlib.h"
#include "util.h"
#include <string.h>

void parseobj(XPM *img , char *objname , char *vizname);

void afispersp(XPM* img , pp3 vrp , pv3 vpn , pv3 vup ,
        pp3 prp , pp3 uvmin , pp3 uvmax , plistface radf);

void afisparalel(XPM* img , pp3 vrp , pv3 vpn , pv3 vup ,
        pp3 prp , pp3 uvmin , pp3 uvmax , plistface radf);

int faceinvolumepersp(plistface auxf , double zmin);

int faceinvolumepar(plistface auxf);

void computeuvn(pv3 u , pv3 v , pv3 n ,
        pv3 vpn , pv3 vup);

pp3 computeprpuvn(pv3 u , pv3 v , pv3 n , pp3 prp);

char cross(pp2 x ,
        pp2 p1d1u , pp2 p2d1u , pp2 p1d2u , pp2 p2d2u);


#ifdef	__cplusplus
}
#endif

#endif
