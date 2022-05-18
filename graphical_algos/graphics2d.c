#include "graphics2d.h"

#include <stdlib.h>
#include <math.h>

#include "data_structures.h"
#include "xpmlib.h"
#include "util.h"

#define TOP_OUT_DIRECTION '1'
#define TOP_IN_DIRECTION '2'
#define BOTTOM_OUT_DIRECTION '3'
#define BOTTOM_IN_DIRECTION '4'
#define LEFT_OUT_DIRECTION '5'
#define LEFT_IN_DIRECTION '6'
#define RIGHT_OUT_DIRECTION '7'
#define RIGHT_IN_DIRECTION '8'

void intersectie(pp2 p , pp2 q, unsigned int coord, char directie) {

    float mxdx, mxdy;

    if (directie == 'w') /*directie = 'w' */ {
        if (p->x < q->x) {
            if (p->y == q->y) {
                p->x = coord;
            } else {

                if (p->y < q->y) {
                    mxdx = (coord - p->x) * ((float) (q->y - p->y) / (q->x - p->x));
                    p->y = p->y + mxdx;
                } else {
                    mxdx = (coord - p->x) * ((float) (p->y - q->y) / (q->x - p->x));
                    p->y = p->y - mxdx;
                }

                p->x = coord;

            }
        } else /***************p->x > q.x*/ {
            if (p->y == q->y) {
                p->x = coord;
            } else {

                /*dx * m;*/

                if (p->y < q->y) {
                    mxdx = (p->x - coord) * ((float) (q->y - p->y) / (p->x - q->x));
                    p->y = p->y + mxdx;
                } else {
                    mxdx = (p->x - coord) * ((float) (p->y - q->y) / (p->x - q->x));
                    p->y = p->y - mxdx;
                }

                p->x = coord;


            }
        }
    } else /**************************************directie = 'h'*/ {
        if (p->y < q->y) {
            if (p->x == q->x) {
                p->y = coord;
            } else {

                if (p->x < q->x) {
                    mxdy = (coord - p->y) * ((float) (q->x - p->x) / (q->y - p->y));
                    p->x = p->x + mxdy;
                } else {
                    mxdy = (coord - p->y) * ((float) (p->x - q->x) / (q->y - p->y));
                    p->x = p->x - mxdy;
                }

                p->y = coord;

            }
        } else /*************p->y > q.y*/ {
            if (p->x == q->x) {
                p->y = coord;
            } else {

                if (p->x < q->x) {
                    mxdy = (p->y - coord) * ((float) (q->x - p->x) / (p->y - q->y));
                    p->x = p->x + mxdy;
                } else {
                    mxdy = (p->y - coord) * ((float) (p->x - q->x) / (p->y - q->y));
                    p->x = p->x - mxdy;
                }

                p->y = coord;

            }
        }
    }

}

unsigned int clip_line_to_image(pp2 p , pp2 q,
        unsigned int left, unsigned int right,
        unsigned int bottom, unsigned int top) {

    unsigned char codep = 0x00;
    unsigned char codeq = 0x00;

    if (p->x < left) /*pt pct-ul p*/ {
        codep = codep | 0x08;
    }

    if (p->x > right) {
        codep = codep | 0x04;
    }

    if (p->y < top) {
        codep = codep | 0x02;
    }

    if (p->y > bottom) {
        codep = codep | 0x01; /******************************/
    }

    if (q->x < left) /*pt pct-ul q*/ {
        codeq = codeq | 0x08;
    }

    if (q->x > right) {
        codeq = codeq | 0x04;
    }

    if (q->y < top) {
        codeq = codeq | 0x02;
    }

    if (q->y > bottom) {
        codeq = codeq | 0x01; /*********************************/
    }


    if ((codep | codeq) == 0x00) {
        p->x = p->x - left;
        p->y = p->y - top;

        q->x = q->x - left;
        q->y = q->y - top;


        return LINEINSIDERECTANGLE;
    } else if ((codep & codeq) != 0x00) {

        return LINEOUTSIDERECTANGLE;
    } else if (codep != 0x00) {

        if ((codep & 0x08) == 0x08) {
            intersectie(p, q, left, 'w');
        } else if ((codep & 0x04) == 0x04) {
            intersectie(p, q, right, 'w');
        } else if ((codep & 0x02) == 0x02) {
            intersectie(p, q, top, 'h');
        } else {
            intersectie(p, q, bottom, 'h');
        }

    } else /********************codep = 0x00 && codeq != 0x00 */ {

        if ((codeq & 0x08) == 0x08) {
            intersectie(q, p, left, 'w');
        } else if ((codeq & 0x04) == 0x04) {
            intersectie(q, p, right, 'w');
        } else if ((codeq & 0x02) == 0x02) {
            intersectie(q, p, top, 'h');
        } else {
            intersectie(q, p, bottom, 'h');
        }

    }

    /*printf("\n %u %u %u %u" , p->x , p->y , q->x , q->y);*/
    return clip_line_to_image(p, q, left, right, top, bottom);

}

void clip_lines_to_image(plistline2 *rad, XPM *img, unsigned int color,
        unsigned int left, unsigned int right,
        unsigned int top, unsigned int bottom) {

    plistline2 aux = *rad;
    pp2 a = NULL , b = NULL;
    unsigned int result;
    while (aux != NULL) {
        a = newp2(aux->line->a->x, aux->line->a->y);
        b = newp2(aux->line->b->x, aux->line->b->y);

        result = clip_line_to_image(a, b,
                left, right, bottom, top);
        if (result == LINEINSIDERECTANGLE) {
            a->y = img->height - a->y;
            b->y = img->height - b->y;

            XPMline(img, a, b, color);
        }

        freep2(&a);
        freep2(&b);

        aux = aux->next;
    }
}

pp2 intersect(pp2 p , pp2 q, unsigned int coord, char direction) {
    int aux, aux1;

    /*
	
    |Ix-Qx| |Iy-Qy|
    -------=------- ; Ix , Iy intersection point coordinates , one of them coord
    |Px-Qx| |Py-Qy|
	
     */

    switch (direction) {
        case TOP_OUT_DIRECTION: /* p->y < q->y ; pointy <= coord is interior*/
            aux = abs(p->x - q->x);
            aux1 = aux * (q->y - coord) / (q->y - p->y);
            return newp2(q->x + aux1 > max(p->x, q->x) ? q->x - aux1 : q->x + aux1, coord);
        case TOP_IN_DIRECTION: /* p->y > q->y ; pointy <= coord is interior*/
            aux = abs(p->x - q->x);
            aux1 = aux * (coord - q->y) / (p->y - q->y);
            return newp2(q->x + aux1 > max(p->x, q->x) ? q->x - aux1 : q->x + aux1, coord);
        case BOTTOM_OUT_DIRECTION: /* p->y > q->y ; poiny >= coord is interior*/
            aux = abs(p->x - q->x);
            aux1 = aux * (coord - q->y) / (p->y - q->y);
            return newp2(q->x + aux1 > max(p->x, q->x) ? q->x - aux1 : q->x + aux1, coord);
        case BOTTOM_IN_DIRECTION: /* p->y < q->y ; pointy >= coord is interior*/
            aux = abs(p->x - q->x);
            aux1 = aux * (q->y - coord) / (q->y - p->y);
            return newp2(q->x + aux1 > max(p->x, q->x) ? q->x - aux1 : q->x + aux1, coord);
        case LEFT_OUT_DIRECTION: /* p->x > q->x ; pointx >= coord is interior*/
            aux = abs(p->y - q->y);
            aux1 = aux * (coord - q->x) / (p->x - q->x);
            return newp2(coord, q->y + aux1 > max(p->y, q->y) ? q->y - aux1 : q->y + aux1);
        case LEFT_IN_DIRECTION: /* p->x < q->x ; pointx >= coord is interior*/
            aux = abs(p->y - q->y);
            aux1 = aux * (q->x - coord) / (q->x - p->x);
            return newp2(coord, q->y + aux1 > max(p->y, q->y) ? q->y - aux1 : q->y + aux1);
        case RIGHT_OUT_DIRECTION: /* p->x < q->x ; pointx <= coord is interior*/
            aux = abs(p->y - q->y);
            aux1 = aux * (q->x - coord) / (q->x - p->x);
            return newp2(coord, q->y + aux1 > max(p->y, q->y) ? q->y - aux1 : q->y + aux1);
        case RIGHT_IN_DIRECTION: /* p->x > q->x ; pointx <= coord is interior*/
            aux = abs(p->y - q->y);
            aux1 = aux * (coord - q->x) / (p->x - q->x);
            return newp2(coord, q->y + aux1 > max(p->y, q->y) ? q->y - aux1 : q->y + aux1);
    }

    return NULL;
}

ppoly polygon_clipping_sutherland_hodgman(ppoly rad,
        int left, int right, int bottom, int top) {

    ppoly aux = NULL, aux1 = NULL;
    int i;
    ppoly_it it = NULL;
    pp2 a = NULL , b = NULL ,
            pointtoadd = NULL , pointtoadd2 = NULL , firstpoint = NULL;

    if (rad == NULL) {
        return NULL;
    }
    aux1 = rad;

    for (i = 0; i < 4; i++) {
        aux = NULL;
        it = newpoly_it(aux1);
        if (it == NULL) {
            break;
        }

        a = next_polyp(it);
        firstpoint = a;

        switch (i) {
            case 0: /* left ; point.x >= left => in , else out */

                while (1) {
                    b = next_polyp(it);
                    if (b == NULL) {
                        if (firstpoint == a) {
                            break;
                        }
                        b = firstpoint;
                    }
                    if (a->x >= left && b->x >= left) {
                        pointtoadd = newp2(b->x, b->y);
                    } else if (!(a->x < left && b->x < left)) {
                        if (a->x < b->x) {
                            pointtoadd = intersect(a, b, left, LEFT_IN_DIRECTION);
                            pointtoadd2 = newp2(b->x, b->y);
                        } else {
                            pointtoadd = intersect(a, b, left, LEFT_OUT_DIRECTION);
                        }
                    }
                    a = b;

                    if (pointtoadd != NULL) {
                        if (aux == NULL) {
                            aux = newpoly(pointtoadd);
                        } else {
                            add_p2_to_poly(pointtoadd, aux);
                        }
                        if (pointtoadd2 != NULL) {
                            add_p2_to_poly(pointtoadd2, aux);
                        }
                        pointtoadd = NULL;
                        pointtoadd2 = NULL;
                    }

                    if (b == firstpoint) {
                        break;
                    }
                }
                break;
            case 1: /* right ; point.x <= left => in , else out */

                while (1) {
                    b = next_polyp(it);
                    if (b == NULL) {
                        if (firstpoint == a) {
                            break;
                        }
                        b = firstpoint;
                    }

                    if (a->x <= right && b->x <= right) {
                        pointtoadd = newp2(b->x, b->y);
                    } else if (!(a->x > right && b->x > right)) {
                        if (a->x < b->x) {
                            pointtoadd = intersect(a, b, right, RIGHT_OUT_DIRECTION);
                        } else {
                            pointtoadd = intersect(a, b, right, RIGHT_IN_DIRECTION);
                            pointtoadd2 = newp2(b->x, b->y);
                        }
                    }
                    a = b;

                    if (pointtoadd != NULL) {
                        if (aux == NULL) {
                            aux = newpoly(pointtoadd);
                        } else {
                            add_p2_to_poly(pointtoadd, aux);
                        }
                        if (pointtoadd2 != NULL) {
                            add_p2_to_poly(pointtoadd2, aux);
                        }
                        pointtoadd = NULL;
                        pointtoadd2 = NULL;
                    }

                    if (b == firstpoint) {
                        break;
                    }
                }
                break;
            case 2: /* bottom ; point.y >= bottom => in , else out */

                while (1) {
                    b = next_polyp(it);
                    if (b == NULL) {
                        if (firstpoint == a) {
                            break;
                        }
                        b = firstpoint;
                    }

                    if (a->y >= bottom && b->y >= bottom) {
                        pointtoadd = newp2(b->x, b->y);
                    } else if (!(a->y < bottom && b->y < bottom)) {
                        if (a->y < b->y) {
                            pointtoadd = intersect(a, b, bottom, BOTTOM_IN_DIRECTION);
                            pointtoadd2 = newp2(b->x, b->y);
                        } else {
                            pointtoadd = intersect(a, b, bottom, BOTTOM_OUT_DIRECTION);
                        }
                    }
                    a = b;

                    if (pointtoadd != NULL) {
                        if (aux == NULL) {
                            aux = newpoly(pointtoadd);
                        } else {
                            add_p2_to_poly(pointtoadd, aux);
                        }
                        if (pointtoadd2 != NULL) {
                            add_p2_to_poly(pointtoadd2, aux);
                        }
                        pointtoadd = NULL;
                        pointtoadd2 = NULL;
                    }

                    if (b == firstpoint) {
                        break;
                    }
                }
                break;
            case 3: /* top ; point.y <= top => in , else out */

                while (1) {
                    b = next_polyp(it);
                    if (b == NULL) {
                        if (firstpoint == a) {
                            break;
                        }
                        b = firstpoint;
                    }

                    if (a->y <= top && b->y <= top) {
                        pointtoadd = newp2(b->x, b->y);
                    } else if (!(a->y > top && b->y > top)) {
                        if (a->y < b->y) {
                            pointtoadd = intersect(a, b, top, TOP_OUT_DIRECTION);
                        } else {
                            pointtoadd = intersect(a, b, top, TOP_IN_DIRECTION);
                            pointtoadd2 = newp2(b->x, b->y);
                        }
                    }
                    a = b;

                    if (pointtoadd != NULL) {
                        if (aux == NULL) {
                            aux = newpoly(pointtoadd);
                        } else {
                            add_p2_to_poly(pointtoadd, aux);
                        }
                        if (pointtoadd2 != NULL) {
                            add_p2_to_poly(pointtoadd2, aux);
                        }
                        pointtoadd = NULL;
                        pointtoadd2 = NULL;
                    }

                    if (b == firstpoint) {
                        break;
                    }
                }
                break;
        } /* end switch */

        freepoly_it(&it);
        if (aux1 != rad) {
            freepoly(&aux1);
        }

        aux1 = aux;
    } /* end for */

    return aux;
}

typedef struct intp2l{
    pp2 p;
    struct intp2l *nextp;
    struct intp2l *prevp;
    /* NULL if an own point */
    struct intp2l *farp;
    /* is the point inside or outside the other polygon
     * 1 point is interior to the other polygon
     * 0 point is exterior to the other polygon */
    int is_interior;
}*pintp2l;

typedef struct intp2l_info{
    pintp2l startp;
    /* needed for ordered insertion of intersection points */
    pintp2l ownp;
}*poly_int;

/* 2 intersecting polygons with links to each other woven in
 *
 * at the intersection points
 * must have a separate object for each polygon
 * also know if a point is interior to the other polygon
 * a intersecting point must be added to both polygons
 * remembers a current own node (non intersection point)
 * designed for use in the weiler atherton code */
poly_int new_poly_int(pp2 first_ownp){
    poly_int pol;

    pol=malloc(sizeof(struct intp2l_info));

    pol->startp=malloc(sizeof(struct intp2l));
    pol->startp->p=newp2(first_ownp->x , first_ownp->y);

    pol->startp->nextp=pol->startp;
    pol->startp->prevp=pol->startp;
    pol->startp->farp=NULL;

    pol->ownp=pol->startp;

    return pol;
}

/* insert initial points that make up a polygon */
void insert_ownp(pp2 p , poly_int pol){
    pintp2l index;
    index=pol->ownp;

    while(index->nextp != pol->startp){
        index=index->nextp;
    }

    index->nextp=malloc(sizeof(struct intp2l));
    index->nextp->prevp=index;
    index=index->nextp;
    index->nextp=pol->startp;
    pol->startp->prevp=index;

    index->farp=NULL;
    index->p=newp2(p->x , p->y);

    pol->ownp=index;
}

void advance_ownp(poly_int pol){

    pintp2l aux;
    aux=pol->ownp;
    
    while(1){
        aux=aux->nextp;
        if(aux==pol->startp)return;
        if(aux->farp == NULL)break;
    }
    pol->ownp=aux;
}

void reset_ownp(poly_int pol){
    pol->ownp=pol->startp;
}

/* insert the intersection point in both polygons
 * ordering according to increasing distance to current own node */
void push_intp_ordered(pp2 p , poly_int pol1 ,
        poly_int pol2){

    pintp2l auxp1 , auxp2 , index;
    double dist;

    auxp1=malloc(sizeof(struct intp2l));
    auxp2=malloc(sizeof(struct intp2l));
    auxp1->farp=auxp2;
    auxp2->farp=auxp1;
    auxp1->p=newp2(p->x , p->y);
    auxp2->p=newp2(p->x , p->y);

    index=pol1->ownp;
    dist=distpoints2(pol1->ownp->p , p);
    while(index->nextp->farp != NULL){
        if(distpoints2(pol1->ownp->p ,
                index->nextp->p) > dist){
            break;
        }
        index=index->nextp;
    }
    index->nextp->prevp=auxp1;
    auxp1->nextp=index->nextp;
    auxp1->prevp=index;
    index->nextp=auxp1;

    index=pol2->ownp;
    dist=distpoints2(pol2->ownp->p , p);
    while(index->nextp->farp != NULL){
        if(distpoints2(pol2->ownp->p ,
                index->nextp->p) > dist){
            break;
        }
        index=index->nextp;
    }
    index->nextp->prevp=auxp2;
    auxp2->nextp=index->nextp;
    auxp2->prevp=index;
    index->nextp=auxp2;
}

/* use the initial structure of the other polygon
 * and alternating inside/outside for each intersection point
 * to determine if points in the intersection_polygon
 * are outside or inside the other polygon
 * 
 * must receive reset polygon_iterator */
void is_int_ext_info(poly_int pol ,
        ppoly_it it){

    int val;
    pintp2l index;
    index=pol->startp;
    
    if(isp2_in_poly(pol->startp->p , it)){
        val=1;
    }
    else{
        val=0;
    }
    
    index->is_interior=val;
    while(index->nextp != pol->startp){
        index=index->nextp;
        if(index->farp != NULL){
            val= val==1 ? 0:1;
        }
        index->is_interior=val;
    }
}

void rem_intp(pintp2l aux){
    aux->prevp->nextp=aux->nextp;
    aux->nextp->prevp=aux->prevp;
    freep2(& aux->p);
    free(aux);
}

/* go through the points and return
 * the first polygon that is an intersection polygon
 * NULL if there is no intersection polygon
 *
 * must select the same order for the polygons when calling the function */
ppoly next_ret_poly(poly_int pol){
    
    ppoly ret_poly;
    pintp2l base_point , index , aux , aux1;
    int intersecting;

    intersecting=0;
    index=pol->ownp;
    base_point=index;
    ret_poly=NULL;
    
    while(index->nextp != pol->startp){
        index=index->nextp;
        if(! index->farp)base_point=index;
        else if(! index->is_interior){
            intersecting=1;
            break;
        }
    }
    if(! intersecting)return NULL;

    ret_poly=newpoly(
            newp2(index->p->x , index->p->y));
    aux=index;
    if(!index->farp)index=index->nextp;
    else index=index->farp->nextp;
    while(index->p->x != aux->p->x ||
            index->p->y != aux->p->y){
        add_p2_to_poly(
                newp2(index->p->x , index->p->y) ,
                ret_poly);

        if(! index->farp)index=index->nextp;
        else{
            aux1=index;
            index=index->farp->nextp;
            rem_intp(aux1->farp);
            rem_intp(aux1);
        }
    }
    rem_intp(aux->farp);
    rem_intp(aux);

    pol->ownp=base_point;
    return ret_poly;
}

/* free memory */
void free_int_poly(poly_int *p){
    pintp2l aux , aux1;

    aux=(*p)->startp;
    aux1=aux->nextp;
    while(aux1 != aux){
        aux1=aux1->nextp;
        freep2(& aux1->prevp->p);
        free(aux1->prevp);
    }
    freep2(& aux->p);
    free(aux);

    free(*p);
    *p=NULL;
}

 /* end intersection_polygon */

/* insert the intersection points in their respective
 * proper place in the 2 resulting intersection_polygon structures */
void push_int_points(
        ppoly clipped_polygon , ppoly clipping_polygon ,
        poly_int *first_int_poly ,
        poly_int *second_int_poly){

    pp2 aux1_pol1=NULL , aux2_pol1=NULL ,
            aux1_pol2=NULL , aux2_pol2=NULL , aux ,
            pol1_firstpoint=NULL , pol2_firstpoint=NULL;

    pp2 int_point=NULL;

    ppoly_it it1=newpoly_it(clipped_polygon);
    ppoly_it it2=newpoly_it(clipping_polygon);

    int onemorepass=1;

    aux1_pol1=next_polyp(it1);
    aux1_pol2=next_polyp(it2);
    pol1_firstpoint=aux1_pol1;
    pol2_firstpoint=aux1_pol2;
    *first_int_poly=new_poly_int(aux1_pol1);
    *second_int_poly=new_poly_int(aux1_pol2);

    while(1){
        aux=next_polyp(it2);
        if(aux==NULL)break;
        insert_ownp(aux , *second_int_poly);
    }
    reset_poly_it(it2);
    next_polyp(it2);
    reset_ownp(*second_int_poly);

    while(1){
        aux2_pol1=next_polyp(it1);
        if(aux2_pol1 == NULL){
            onemorepass=0;
            aux2_pol1=pol1_firstpoint;
        }
        
        while(1){
            aux2_pol2=next_polyp(it2);
            if(aux2_pol2==NULL)break;

            int_point=intersect_segments(aux1_pol1 , aux2_pol1 ,
                    aux1_pol2 , aux2_pol2);
            if(int_point != NULL){
                push_intp_ordered(int_point ,
                        *first_int_poly ,
                        *second_int_poly);
                free(int_point);
            }
            aux1_pol2=aux2_pol2;

            advance_ownp(*second_int_poly);
        }
        int_point=intersect_segments( aux1_pol1 , aux2_pol1 ,
                aux1_pol2 , pol2_firstpoint);
        if(int_point != NULL){
            push_intp_ordered(int_point ,
                    *first_int_poly , *second_int_poly);
            free(int_point);
        }
        if(! onemorepass)break;

        reset_poly_it(it2);
        reset_ownp(*second_int_poly);
        aux1_pol2=next_polyp(it2);
        
        aux1_pol1=aux2_pol1;
        insert_ownp(aux2_pol1 , *first_int_poly);
    }

    reset_ownp(*first_int_poly);
    reset_ownp(*second_int_poly);
    freepoly_it(& it1);
    freepoly_it(& it2);
}

ppoly build_clipping_polygon(int left , int right , int bottom , int top){
    ppoly aux;
    pp2 left_top , right_top , left_bottom , right_bottom;

    /* counterclockwise */
    left_top=newp2(left , top);
    left_bottom=newp2(left , bottom);
    right_bottom=newp2(right , bottom);
    right_top=newp2(right , top);

    aux=newpoly(left_top);
    add_p2_to_poly(left_bottom , aux);
    add_p2_to_poly(right_bottom , aux);
    add_p2_to_poly(right_top , aux);

    return aux;
}

ppoly_l poly_clipping_weiler_atherton(ppoly clipped_poly ,
        int left, int right, int bottom, int top) {

    ppoly_l ret_poly_list=NULL;
    ppoly aux;
    ppoly clipping_poly;
    poly_int clipped_int_poly ,
            clipping_int_poly;
    ppoly_it clippedit , clippingit;

    if(! clipped_poly)return NULL;
    
    clipping_poly=build_clipping_polygon(left , right , bottom , top);
    
    push_int_points(clipped_poly , clipping_poly,
        &clipped_int_poly , &clipping_int_poly);

    clippedit=newpoly_it(clipped_poly);
    clippingit=newpoly_it(clipping_poly);
    is_int_ext_info(clipped_int_poly ,
            clippingit);
    is_int_ext_info(clipping_int_poly ,
            clippedit);

    aux=next_ret_poly(clipped_int_poly);
    if(aux != NULL){
        ret_poly_list=newpoly_l(aux);
        while((aux=next_ret_poly(clipped_int_poly)) != NULL){

            add_poly_to_poly_l(aux , &ret_poly_list);
        }
    }

    /*free alocated memory for auxiliary polygons*/
    freepoly_it(& clippedit);
    freepoly_it(& clippingit);
    freepoly(& clipping_poly);
    free_int_poly(& clipped_int_poly);
    free_int_poly(& clipping_int_poly);

    return ret_poly_list;
}

pp2 intersect_segments(pp2 seg1start , pp2 seg1end ,
        pp2 seg2start , pp2 seg2end) {

    double dxa , dya, dxb, dyb;
    double ta , tb;
    double denominator = 0;
    double intx , inty;

    dxa = seg1end->x - seg1start->x;
    dya = seg1end->y - seg1start->y;
    dxb = seg2end->x - seg2start->x;
    dyb = seg2end->y - seg2start->y;

    denominator = dxa*dyb - dxb*dya;

    if (denominator == 0) {
        return NULL;
    }

    ta = ((seg2start->x - seg1start->x) * dyb +
            (seg1start->y - seg2start->y) * dxb) / denominator;
    tb = ((seg2start->x - seg1start->x) * dya +
            (seg1start->y - seg2start->y) * dxa) / denominator;
    if (ta < 0 || ta > 1 || tb < 0 || tb > 1) {
        return NULL;
    }

    intx=seg1start->x + ta * (seg1end->x - seg1start->x);
    inty=seg1start->y + ta * (seg1end->y - seg1start->y);

    return newp2((int) (intx+0.5) , (int) (inty+0.5));
}

int are_segments_intersecting(pp2 seg1start , pp2 seg1end ,
                pp2 seg2start , pp2 seg2end){

    double dxa, dya, dxb, dyb;
    double ta, tb;
    double denominator = 0;

    dxa = seg1end->x - seg1start->x;
    dya = seg1end->y - seg1start->y;
    dxb = seg2end->x - seg2start->x;
    dyb = seg2end->y - seg2start->y;

    denominator = dxa * dyb - dxb*dya;

    if (denominator == 0) {
        return 0;
    }

    ta = ((seg2start->x - seg1start->x) * dyb +
            (seg1start->y - seg2start->y) * dxb) / denominator;
    tb = ((seg2start->x - seg1start->x) * dya +
            (seg1start->y - seg2start->y) * dxa) / denominator;
    if (ta < 0 || ta > 1 || tb < 0 || tb > 1) {
        return 0;
    }

    return 1;
}

/* private */
ppoly poly_2d_vis_transf(ppoly the_poly , pm3 transf_matr){
    pv3 auxv3 , resultv3;
    ppoly_it pit;
    pp2 auxp2;
    ppoly ret_poly;

    auxv3=newv3(0.0 , 0.0 , 0.0);
    pit=newpoly_it(the_poly);
    ret_poly=NULL;

    while((auxp2=next_polyp(pit)) != NULL){
        auxv3->x=auxp2->x;
        auxv3->y=auxp2->y;
        auxv3->z=1;

        resultv3=mul_pm3_pv3(transf_matr , auxv3);
        if(!ret_poly)ret_poly=newpoly(
                newp2(resultv3->x , resultv3->y));
        else add_p2_to_poly(newp2(resultv3->x , resultv3->y) , ret_poly);
        freev3(&resultv3);
    }

    return ret_poly;
}

ppoly_l poly_l_2d_vis_transf(ppoly_l rad ,
                    int wl , int wr , int wb , int wt ,
                    int vl , int vr , int vb , int vt){

    ppoly_l_it rad_it;
    ppoly aux , aux1;
    pm3 transf_matr;
    ppoly_l ret_poly_l;

    transf_matr=transfviz_2d_matrice(wl,wr,wb,wt ,
                                        vl,vr,vb,vt);

    rad_it=newpoly_l_it(rad);
    aux=next_poly_l_poly(rad_it);
    aux1=poly_2d_vis_transf(aux , transf_matr);
    ret_poly_l=newpoly_l(aux1);
    while((aux=next_poly_l_poly(rad_it)) != NULL){
        aux1=poly_2d_vis_transf(aux , transf_matr);
        add_poly_to_poly_l(aux1 , &ret_poly_l);
    }

    return ret_poly_l;
}
