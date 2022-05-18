#ifndef _GRAPHICS2D_H
#define	_GRAPHICS2D_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "data_structures.h"
#include "mathlib.h"

#include "xpmlib.h"
#include "malloc.h"

#define LINEOUTSIDERECTANGLE 0
#define LINEINSIDERECTANGLE 1
	
	unsigned int clip_line_to_image(pp2 p , pp2 q ,
		unsigned int left , unsigned int right ,
		unsigned int top , unsigned int bottom);

	void clip_lines_to_image(plistline2 *rad, XPM *img, unsigned int color,
		unsigned int left, unsigned int right,
		unsigned int top, unsigned int bottom);

        /* the polygon must have a clockwise
         * orientation of the contained points*
         * and the clipping polygon is the viewport rectangle */
	ppoly polygon_clipping_sutherland_hodgman(ppoly rad ,
		int left , int right , int bottom , int top);

        /* the polygons must have a counter-clockwise
         * orientation of the contained points
         * and the result is a boolean geometric intersection
         * the clipping rectangle is the viewport rectangle */
	ppoly_l poly_clipping_weiler_atherton(ppoly clipped_polygon ,
                int left , int right , int bottom , int top);

        /* general code for testing of the intersection of 2 segments
         * return NULL if the segments do not intersect
         * return the intersection point if the segments do intersect
         * TODO move to mathlib */
	pp2 intersect_segments(pp2 seg1start , pp2 seg1end ,
		pp2 seg2start , pp2 seg2end);

        /* code to determine if 2 segments are intersecting
         * return 0 if segments are not intersecting
         *        != 0 if segments are intersecting */
        int are_segments_intersecting(pp2 seg1start , pp2 seg1end ,
                pp2 seg2start , pp2 seg2end);

        ppoly_l poly_l_2d_vis_transf(ppoly_l rad2 ,
                    int wl , int wr , int wb , int wt ,
                    int vl , int vr , int vb , int vt);

#ifdef	__cplusplus
}
#endif

#endif
