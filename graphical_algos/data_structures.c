#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"
#include "util.h"
#include "mathlib.h"
#include "graphics2d.h"

pp2 newp2(int x, int y) {
    pp2 p;
    p=malloc(sizeof(struct p2));

    p->x = x;
    p->y = y;

    return p;
}

void freep2(pp2 *p) {
    free(*p);
    *p = NULL;
}

pp3 newp3(int x, int y, int z) {
    pp3 p = malloc(sizeof (struct p3));

    p->x = (double) x;
    p->y = (double) y;
    p->z = (double) z;

    return p;
}

void freep3(pp3 *p) {
    free(*p);
    *p = NULL;
}

pv3 newv3(double x, double y, double z) {
    pv3 v = malloc(sizeof (struct v3));
    
    v->x = x;
    v->y = y;
    v->z = z;

    return v;
}

void freev3(pv3 *v) {
    free(*v);
    *v = NULL;
}

void setv3(pv3 v , double x , double y , double z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

pv3 v3_from_p3(pp3 a , pp3 b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    return newv3(a->x - b->x, a->y - b->y, a->z - b->z);
}

pm3 newm3(double e11, double e12, double e13,
        double e21, double e22, double e23,
        double e31, double e32, double e33) {
    pm3 m = malloc(sizeof (struct m3));

    m->e11 = e11 ; m->e12 = e12 ; m->e13 = e13;
    m->e21 = e21 ; m->e22 = e22 ; m->e23 = e23;
    m->e31 = e31 ; m->e32 = e32 ; m->e33 = e33;

    return m;
}

void freem3(pm3 *m) {
    free(*m);
    *m = NULL;
}

pm3 parse_translation_info(char *buffer_index) {
    double tx, ty; /* translation distance */
    pm3 m;

    tx = strtod(buffer_index, &buffer_index);
    ty = strtod(buffer_index, &buffer_index);
    m = intrans2d(tx, ty);

    return m;
}

pm3 parse_scaling_info(char *buffer_index) {
    double px, py; /* scale reference point coordinates */
    double sx, sy; /* scale */
    pm3 m;

    px = strtod(buffer_index, &buffer_index);
    py = strtod(buffer_index, &buffer_index);
    sx = strtod(buffer_index, &buffer_index);
    sy = strtod(buffer_index, &buffer_index);
    m = inscale2d(px, py, sx, sy);

    return m;
}

pm3 parse_rotation_info(char *buffer_index) {
    double px, py; /* rotation reference point */
    double angle; /* trigonometric rotation angle in degrees */
    pm3 m;

    px = strtod(buffer_index, &buffer_index);
    py = strtod(buffer_index, &buffer_index);
    angle = strtod(buffer_index, &buffer_index);
    m = inrotate2d(px, py, angle);

    return m;
}

pm3 parse_transformations_file(char *transf_fname) {
    char buff[100];
    char *buff_index;
    int index;
    pm3 aux , aux1;
    pm3 ret_matr;
    FILE *f;

    buff_index = NULL;
    aux = aux1 = NULL;
    ret_matr = NULL;

    ret_matr = trinit3();

    f = NULL;
    f=fopen(transf_fname, "r");
    if (f == NULL) {
        printf("error opening transformations file");
        return NULL;
    }

    while (fgets(buff, 100, f) != NULL) {
        buff_index = buff;
        index = strtriml(buff_index);
        buff_index = buff_index + index;
        if (!strcmp(buff_index, "")) {
            continue;
        }
        switch (buff_index[0]) {
            case TRANSLATION:
                buff_index = buff_index + 1;
                aux = parse_translation_info(buff_index);
                break;
            case SCALING:
                buff_index = buff_index + 1;
                aux = parse_scaling_info(buff_index);
                break;
            case ROTATION:
                buff_index = buff_index + 1;
                aux = parse_rotation_info(buff_index);
                break;
        }
        aux1 = mul_pm3(ret_matr, aux);
        freem3(&ret_matr);
        freem3(&aux);
        ret_matr = aux1;
    }
    fclose(f);

    return ret_matr;
}

pm4 newm4(double e11, double e12, double e13, double e14,
        double e21, double e22, double e23, double e24,
        double e31, double e32, double e33, double e34,
        double e41, double e42, double e43, double e44) {

    pm4 m;
    m = malloc(sizeof (struct m4));

    m->e11 = e11 ; m->e12 = e12 ; m->e13 = e13 ; m->e14 = e14;
    m->e21 = e21 ; m->e22 = e22 ; m->e23 = e23 ; m->e24 = e24;
    m->e31 = e31 ; m->e32 = e32 ; m->e33 = e33 ; m->e34 = e34;
    m->e41 = e41 ; m->e42 = e42 ; m->e43 = e43 ; m->e44 = e44;

    return m;
}

void freem4(pm4 *m) {
    free(*m);
    *m = NULL;
}

pv4 newv4(double x, double y, double z, double w) {
    pv4 v;
    v = malloc(sizeof (struct v4));
    
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;

    return v;
}

void freev4(pv4 *v) {
    free(*v);
    *v = NULL;
}

ppoly newpoly(pp2 p) {
    ppoly rad;
    rad=malloc(sizeof(struct p2l));

    rad->a = p;
    rad->prevpoint = rad;
    rad->nextp = rad;

    return rad;
}

void freepoly(ppoly *rad) {
    ppoly aux, aux1;

    aux = (*rad)->nextp, aux1 = NULL;

    while (aux != (*rad)) {
        aux1 = aux;
        aux->prevpoint->nextp = aux->nextp;
        aux->nextp->prevpoint = aux->prevpoint;
        aux = aux->nextp;
        freep2(&aux1->a);
        free(aux1);
    }

    freep2(&((*rad)->a));
    free(*rad);

    *rad = NULL;
}

void add_p2_to_poly(pp2 p, ppoly rad) {

    ppoly aux;

    if (rad == NULL) {
        return;
    }

    aux = malloc(sizeof(struct p2l));
    if (aux == NULL) {
        return;
    }

    aux->prevpoint = rad->prevpoint;
    rad->prevpoint->nextp = aux;
    aux->nextp = rad;
    rad->prevpoint = aux;

    aux->a = p;
}

void add_poly_to_poly(ppoly source , ppoly destination){

    ppoly aux;

    if(source == NULL){
        return;
    }

    destination->prevpoint->nextp=source;
    source->prevpoint->nextp=destination;

    aux=destination->prevpoint;
    destination->prevpoint=source->prevpoint;
    source->prevpoint=aux;
}

ppoly parsepolfile_to_polygon(char* polygon_file_name, int image_height) {
    ppoly rad = NULL;
    char buffer[200], *buffer_index;
    int auxx, auxy;
    FILE *f;

    buffer_index = NULL;
    f = fopen(polygon_file_name, "r");

    while (fgets(buffer, 195, f) != NULL) {
        buffer_index = buffer;
        auxx = (int) strtol(buffer_index, &buffer_index, 10);
        auxy = (int) strtol(buffer_index, &buffer_index, 10);
        auxy = image_height - auxy;
        if (rad == NULL) {
            rad = newpoly(newp2(auxx, auxy));
        } else {
            add_p2_to_poly(newp2(auxx, auxy), rad);
        }
    }

    fclose(f);

    return rad;
}

int isp2_in_poly(pp2 p , ppoly_it it){
    pp2 a;
    pp2 aux1 , aux2 , start_point;
    int intersection_count;

    /* point on edge outside the polygon */
    a=malloc(sizeof(struct p2));
    a->x=0;
    a->y=p->y;

    intersection_count=0;

    aux1=next_polyp(it); start_point=aux1;
    while((aux2=next_polyp(it)) != NULL){
        if(are_segments_intersecting(p , a , aux1 , aux2))intersection_count++;
        aux1=aux2;
    }
    reset_poly_it(it);
    if(are_segments_intersecting(p , a , start_point , aux1))
        intersection_count++;

    free(a);
    if(intersection_count % 2){/* odd number of intersections */
        return 1;
    }
    /* even */
    return 0;
}

ppoly_it newpoly_it(ppoly rad) {

    ppoly_it it;
    if (! rad)return NULL;
    it = malloc(sizeof (struct poly_it));

    it->rad = rad;
    it->current_poly_node = rad;
    it->done = 0;

    return it;
}

pp2 next_polyp(ppoly_it it) {

    pp2 p;

    if (it->done) {
        return NULL;
    }

    p = it->current_poly_node->a;

    it->current_poly_node = it->current_poly_node->nextp;
    if (it->current_poly_node == it->rad) {
        it->done = 1;
    }

    return p;
}

void reset_poly_it(ppoly_it it){
    it->current_poly_node=it->rad;
    it->done=0;
}

void freepoly_it(ppoly_it *it) {
    free(*it);
    *it = NULL;
}

ppoly move_origin_to(ppoly rad,
        int new_x, int new_y) {

    ppoly aux = NULL;
    ppoly_it it = newpoly_it(rad);
    pp2 a = NULL;

    a = next_polyp(it);
    if (a == NULL) {
        freepoly_it(&it);
        return NULL;
    }
    aux = newpoly(newp2(a->x - new_x, a->y - new_y));
    while (1) {
        a = next_polyp(it);
        if (! a)break;
        add_p2_to_poly(newp2(a->x - new_x, a->y - new_y), aux);
    }

    freepoly_it(&it);

    return aux;
}

ppoly_l newpoly_l(ppoly p){

    ppoly_l poly_l;

    if(! p)return NULL;
    
    poly_l=malloc(sizeof(struct poly_l));
    poly_l->p=p;
    poly_l->next_poly_l=NULL;
    
    return poly_l;
}

void freepoly_l(ppoly_l *rad){
    ppoly_l_it it;
    ppoly_l aux;
    if(! *rad)return;

    it=newpoly_l_it(*rad);
    while((aux=next_poly_l(it)) != NULL){
        freepoly(& aux->p);
        free(aux);
    }
    freepoly_l_it(&it);
}

void add_poly_to_poly_l(ppoly p , ppoly_l *plrad){

    ppoly_l aux;
    if(! p)return;

    aux=malloc(sizeof(struct poly_l));
    aux->p=p;
    aux->next_poly_l=*plrad;
    *plrad=aux;
}

ppoly_l_it newpoly_l_it(ppoly_l rad){
    ppoly_l_it aux;
    if(! rad)return NULL;

    aux=malloc(sizeof(struct poly_l_it));
    aux->rad=rad;
    aux->current_poly_l=aux->rad;

    return aux;
}

ppoly_l next_poly_l(ppoly_l_it it){
    ppoly_l aux;

    if(! it)return NULL;
    if(! it->current_poly_l)return NULL;

    aux=it->current_poly_l;
    it->current_poly_l=it->current_poly_l->next_poly_l;

    return aux;
}

ppoly next_poly_l_poly(ppoly_l_it it){
    ppoly aux;

    if(! it) return NULL;
    if(! it->current_poly_l)return NULL;

    aux=it->current_poly_l->p;
    it->current_poly_l=it->current_poly_l->next_poly_l;

    return aux;
}

void resetpoly_l_it(ppoly_l_it it){
    it->current_poly_l=it->rad;
}

void freepoly_l_it(ppoly_l_it *it){
    free(*it);
    *it=NULL;
}

face* newface(pp3 a , pp3 b , pp3 c) {
    face *f;

    f = malloc(sizeof (face));
    if (f == NULL) {
        return NULL;
    }

    f->a = a;
    f->b = b;
    f->c = c;

    return f;
}

void freeface(face **f) {
    freep3(&((*f)->a));
    freep3(&((*f)->b));
    freep3(&((*f)->c));
    free(*f);
    *f = NULL;
}

void add_face_to_list(face *f, plistface *radf) {
    plistface aux;
    aux = malloc(sizeof (struct listface));
    aux->faceitem = f;
    aux->next = *radf;
    *radf = aux;
}

void free_face_list(plistface *radf) {
    plistface aux;
    aux = *radf;
    while (*radf != NULL) {
        (*radf) = (*radf)->next;
        freeface(&(aux->faceitem));
        aux = *radf;
    }
    *radf = NULL;
}

void add_p3_to_list(pp3 vertex, plistpoint3 *radv) {
    plistpoint3 aux;

    if (*radv == NULL) {
        *radv = malloc(sizeof (struct listpoint3));
        (*radv)->next = NULL;
        (*radv)->vertex = vertex;
    }
    aux = malloc(sizeof (struct listpoint3));
    aux->next = *radv;
    aux->vertex = vertex;
    *radv = aux;
}

void free_p3_list(plistpoint3 *radv) {
    plistpoint3 aux;
    aux = *radv;
    while (*radv != NULL) {
        (*radv) = (*radv)->next;
        freep3(&(aux->vertex));
        aux = *radv;
    }
}

pline2 newline2(pp2 a , pp2 b) {
    pline2 pl;
    pl = malloc(sizeof (struct line2));
    
    pl->a = newp2(a->x , a->y);
    pl->b = newp2(b->x , b->y);

    return pl;
}

void freeline2(pline2 *pl) {
    freep2(& (*pl)->a);
    freep2(& (*pl)->b);
    free(*pl);
    *pl = NULL;
}

void setline2(pline2 pl , int xa , int ya , int xb , int yb) {
    pl->a->x = xa;
    pl->a->y = ya;

    pl->b->x = xb;
    pl->b->y = yb;
}

plistline2 add_line2_to_list(pline2 pl, plistline2 rad) {
    plistline2 aux;

    if (rad == NULL) {
        rad =malloc(sizeof (struct listline2));
        rad->line = pl;
        rad->next = NULL;
        return rad;
    }
    
    aux = malloc(sizeof (struct listline2));
    aux->line = pl;
    aux->next = rad;

    rad = aux;
    return rad;
}

void free_line2_list(plistline2 *rad) {
    plistline2 aux;
    aux = *rad;
    while (*rad != NULL) {
        *rad = (*rad)->next;
        freeline2(& aux->line);
        free(aux);
        aux = *rad;
    }
}

plistline2 parsepsfile_to_line2_list(char *filename) {

    FILE *f;
    char s[501] , *start , *end , stage , flag;
    unsigned int nr;
    pp2 p, q;
    int aux;
    pline2 auxline2;
    plistline2 rad;

    f = fopen(filename, "r");
    rad = NULL;
    stage = 'a';
    flag = 'i';
    p=newp2(0,0);
    q=newp2(0,0);

    if (f != NULL) {

        while (fgets(s, 500, f) != NULL && flag == 'i') {

            start=Trim(s);

            switch (stage) {

                case 'a':
                    if (strcmp(start, "%%%BEGIN") == 0) {
                        stage = 'b';
                    }
                    break;

                case 'b':

                    if (strcmp(start, "%%%END") != 0) {


                        nr = (unsigned int) strtol(start, &end, 10);
                        aux = nr;

                        if (strcmp(s, "") != 0) {
                            nr = (unsigned int) strtol(end, &end, 10);
                            p->x=aux; p->y=nr;

                            if (strcmp(s, "") != 0) {
                                nr = (unsigned int) strtol(end, &end, 10);
                                aux = nr;

                                if (strcmp(s, "") != 0) {
                                    nr = (unsigned int) strtol(end, &end, 10);
                                    q->x=aux; q->y=nr;

                                    end=Trim(end);

                                    if (strcmp(end, "Line") == 0) {/*s-a citit o linie */

                                        auxline2 = newline2(p, q);
                                        rad=add_line2_to_list(auxline2, rad);
                                    }
                                }
                            }
                        }


                    } else {
                        flag = 'o';
                    }

                    break;

            }
        }

    }

    fclose(f);
    freep2(&p);
    freep2(&q);
    return rad;
}

plistline2 lines_at_height_in_poly(ppoly rad , pline2 line_at_height){
    /* TODO */

    ppoly_it pit;
    pp2 aux , aux1;
    ppoly buffer_of_p2;
    plistline2 ret_lines;

    pit=newpoly_it(rad);

    while((aux1=next_polyp(pit)) != NULL){
        if(aux != NULL)
            ;/*get intersection point if it's there
              * and use add_p2_to_poly_xord on it*/
        aux=aux1;
    }

    return ret_lines;
}

pline3 newline3(pp3 a , pp3 b) {
    pline3 line;
    line = malloc(sizeof (struct line3));
    if (line == NULL) {
        return NULL;
    }
    line->a = a;
    line->b = b;
    return line;
}

void freeline3(pline3 *line) {
    freep3(&((*line)->a));
    freep3(&((*line)->b));
    free(*line);
    *line = NULL;
}

plistline3 add_line3_to_list(pline3 line, plistline3 rad) {
    plistline3 aux;
    if (rad == NULL) {
        rad = malloc(sizeof (struct listline3));
        rad->next_line = NULL;
        rad->line = line;
    }
    aux = malloc(sizeof (struct listline3));
    aux->line = line;
    aux->next_line = rad;
    rad = aux;

    return rad;
}

void free_line3_list(plistline3 *rad) {
    plistline3 aux;
    aux = *rad;
    while (*rad != NULL) {
        *rad = (*rad)->next_line;
        freeline3(&(aux->line));
        free(aux);
        aux = *rad;
    }
    *rad=NULL;
}
