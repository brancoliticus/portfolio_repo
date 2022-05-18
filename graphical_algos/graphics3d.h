/* 
 * File:   graphics3d.h
 * Author: branco
 *
 * Created on December 21, 2008, 6:12 PM
 */

#ifndef _GRAPHICS3D_H
#define	_GRAPHICS3D_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#include "data_structures.h"
#include "mathlib.h"

#include "xpmlib.h"
#include "malloc.h"

#define PERSPECTIVE_PROJECTION 1
#define PARALEL_PROJECTION 2
/*
void clip3d(plistobject3d *obj , view3d *v);

void afispersp(XPM* img , point3 vrp , vector3 vpn , vector3 vup ,
			   point3 prp , point3 uvmin , point3 uvmax , plistface radf);

void afisparalel(XPM* img , point3 vrp , vector3 vpn , vector3 vup ,
				 point3 prp , point3 uvmin , point3 uvmax , plistface radf);

void updatezbuf(unsigned int i , unsigned int j , point2 p , point2 q
				, double depth , double deptha , double depthb , double **zbuf);

plistline2 display_scene3d_to_screen(scene3d *s , int projection_type);
*/

#ifdef	__cplusplus
}
#endif

#endif	/* _GRAPHICS3D_H */

