#include <math.h>
#include <malloc.h>

#include "mathlib.h"
#include "data_structures.h"

pm3 trinit3()
{
	return newm3(
		1 , 0 , 0 ,
		0 , 1 , 0 ,
		0 , 0 , 1);
}

pm4 trinit4()
{
	return newm4(
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1);
}

double deg2rad(double degrees)
{

	/* radians = degrees * (pi / 180) */

	return degrees * 0.0174532925;

}

double distpoints2(pp2 a , pp2 b)
{

	double ax = (double) a->x, ay = (double) a->y;
	double bx = (double) b->x, by = (double) b->y;

	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

double distpoints3(pp3 a , pp3 b)
{
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y) + (a->z - b->z)*(a->z - b->z));
}

pv3 cross_product3(pv3 a , pv3 b)
{
	return newv3(
		a->y * b->z - a->z * b->y ,
		a->z * b->x - a->x * b->z ,
		a->x * b->y - a->y * b->x);
}

double dot_product3(pv3 a , pv3 b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

pm3 intrans2d(double tx, double ty)
{
	return newm3(
		1 , 0 , tx ,
		0 , 1 , ty ,
		0 , 0 , 1);
}

pm3 inrotate2d(double px , double py , double angle)
{
	double a, b;

	a=deg2rad(angle);
	b=a;

	a = cos(a);
	b = sin(b);

	return newm3( /* trigonometric rotation (attention : y axis down
		   in the xpm library => on image coordinates clockwise rotation ) */
		a , -b , px*(1-a)+py*b ,
		b , a , py*(1-a)-px*b ,
		0 , 0 , 1);
}

pm3 inscale2d(double px , double py , double sx, double sy)
{
	return newm3(
	    sx,  0 , px*(1-sx) ,
	    0 , sy , py*(1-sy) ,
	    0 , 0 , 1);
}

pm3 mul_pm3(pm3 m1 , pm3 m2)
{
	return newm3(
	    m1->e11 * m2->e11 + m1->e12 * m2->e21 + m1->e13 * m2->e31,
	    m1->e11 * m2->e12 + m1->e12 * m2->e22 + m1->e13 * m2->e32,
	    m1->e11 * m2->e13 + m1->e12 * m2->e23 + m1->e13 * m2->e33,

	    m1->e21 * m2->e11 + m1->e22 * m2->e21 + m1->e23 * m2->e31,
	    m1->e21 * m2->e12 + m1->e22 * m2->e22 + m1->e23 * m2->e32,
	    m1->e21 * m2->e13 + m1->e22 * m2->e23 + m1->e23 * m2->e33,

	    m1->e31 * m2->e11 + m1->e32 * m2->e21 + m1->e33 * m2->e31,
	    m1->e31 * m2->e12 + m1->e32 * m2->e22 + m1->e33 * m2->e32,
	    m1->e31 * m2->e13 + m1->e32 * m2->e23 + m1->e33 * m2->e33);
}

pv3 mul_pm3_pv3(pm3 m , pv3 v)
{
	return newv3(
		m->e11 * v->x + m->e12 * v->y + m->e13 * v->z ,
		m->e21 * v->x + m->e22 * v->y + m->e23 * v->z ,
		m->e31 * v->x + m->e32 * v->y + m->e33 * v->z);
}

pm4 intrans3d(double tx, double ty, double tz)
{
	return newm4(
		1 , 0 , 0 , tx ,
		0 , 1 , 0 , ty ,
		0 , 0 , 1 , tz ,
		0 , 0 , 0 , 1);
}

pm4 inrotate3dx(double angle)
{
	double a, b;

	a=deg2rad(angle);
	b=deg2rad(angle);

	a = cos(a);
	b = sin(b);

	return newm4(
		1 , 0 , 0 , 0 ,
		0 , a , -b , 0 ,
		0 , b , a , 0 ,
		0 , 0 , 0 , 1);
}

pm4 inrotate3dy(double angle)
{
	double a, b;

	a=deg2rad(angle);
	b=deg2rad(angle);

	a = cos(a);
	b = sin(b);

	return newm4(
		a  , 0 , b , 0 ,
		0  , 1 , 0 , 0 ,
		-b , 0 , a , 0 ,
		0  , 0 , 0 , 1);
}

pm4 inrotate3dz(double angle)
{
	double a, b;

	a=deg2rad(angle);
	b=deg2rad(angle);

	a = cos(a);
	b = sin(b);

	return newm4(
		a , -b , 0 , 0 ,
		b , a  , 0 , 0 ,
		0 , 0  , 1 , 0 ,
		0 , 0  , 0 , 1);
}

pm4 inscale3d(double sx, double sy, double sz)
{
	return newm4(
		sx , 0  , 0  , 0 ,
		0  , sy , 0  , 0 ,
		0  , 0  , sz , 0 ,
		0  , 0  , 0  , 1);
}

pm4 inforfxy3d(double shx, double shy)
{
	return newm4(
		1 , 0 , shx , 0 ,
		0 , 1 , shy , 0 ,
		0 , 0 , 1   , 0 ,
		0 , 0 , 0   , 1);
}

void transform_point2(pp2 *returnpoint ,
        pm3 transformation_matrice , pp2 p){
    
	pv3 aux=NULL , aux1=NULL;

	aux1=newv3((double) p->x , (double) p->y , 1.0);
	aux=mul_pm3_pv3(transformation_matrice , aux1);
	(*returnpoint)->x=(int) (aux->x+0.5);
        (*returnpoint)->y=(int) (aux->y+0.5);

	freev3(&aux);
	freev3(&aux1);
}

pm3 transfviz_2d_matrice(int wl , int wr , int wb , int wt ,
        int vl , int vr , int vb , int vt){

    pm3 aux , aux1;
    pm3 ret_matr;

    double dwl=wl , dwr=wr , dwb=wb , dwt=wt;
    double dvl=vl , dvr=vr , dvb=vb , dvt=vt;

    aux=intrans2d(dvl , dvb);
    inscale2d(0.0 , 0.0 , /* scale around origin */
            (dvr-dvl) / (dwr-dwl), /* scale for viewport transform on x */
            (dvt-dvb) / (dwt-dwb)); /* on y */
    ret_matr=mul_pm3(aux , aux1);
    freem3(&aux);
    freem3(&aux1);

    aux=ret_matr;
    aux1=intrans2d(dwl , dwb);
    ret_matr=mul_pm3(aux , aux1);
    freem3(&aux);
    freem3(&aux1);

    return ret_matr;
}

pm4 multiply_matrice4(pm4 m1, pm4 m2)
{

	return newm4(
		m1->e11 * m2->e11 + m1->e12 * m2->e21 + m1->e13 * m2->e31 + m1->e14 * m2->e41 ,
		m1->e11 * m2->e12 + m1->e12 * m2->e22 + m1->e13 * m2->e32 + m1->e14 * m2->e42 ,
		m1->e11 * m2->e13 + m1->e12 * m2->e23 + m1->e13 * m2->e33 + m1->e14 * m2->e43 ,
		m1->e11 * m2->e14 + m1->e12 * m2->e24 + m1->e13 * m2->e34 + m1->e14 * m2->e44 ,

		m1->e21 * m2->e11 + m1->e22 * m2->e21 + m1->e23 * m2->e31 + m1->e24 * m2->e41 ,
		m1->e21 * m2->e12 + m1->e22 * m2->e22 + m1->e23 * m2->e32 + m1->e24 * m2->e42 ,
		m1->e21 * m2->e13 + m1->e22 * m2->e23 + m1->e23 * m2->e33 + m1->e24 * m2->e43 ,
		m1->e21 * m2->e14 + m1->e12 * m2->e24 + m1->e13 * m2->e34 + m1->e24 * m2->e44 ,

		m1->e31 * m2->e11 + m1->e32 * m2->e21 + m1->e33 * m2->e31 + m1->e34 * m2->e41 ,
		m1->e31 * m2->e12 + m1->e32 * m2->e22 + m1->e33 * m2->e32 + m1->e34 * m2->e42 ,
		m1->e31 * m2->e13 + m1->e32 * m2->e23 + m1->e33 * m2->e33 + m1->e34 * m2->e43 ,
		m1->e31 * m2->e14 + m1->e32 * m2->e24 + m1->e33 * m2->e34 + m1->e34 * m2->e44 ,

		m1->e41 * m2->e11 + m1->e42 * m2->e21 + m1->e43 * m2->e31 + m1->e44 * m2->e41 ,
		m1->e41 * m2->e12 + m1->e42 * m2->e22 + m1->e43 * m2->e32 + m1->e44 * m2->e42 ,
		m1->e41 * m2->e13 + m1->e42 * m2->e23 + m1->e43 * m2->e33 + m1->e44 * m2->e43 ,
		m1->e41 * m2->e14 + m1->e42 * m2->e24 + m1->e43 * m2->e34 + m1->e44 * m2->e44);
}

pv4 multiply_vector4(pm4 m , pv4 v)
{
	return newv4(
		m->e11 * v->x + m->e12 * v->y + m->e13 * v->z + m->e14 * v->w ,
		m->e21 * v->x + m->e22 * v->y + m->e23 * v->z + m->e24 * v->w ,
		m->e31 * v->x + m->e32 * v->y + m->e33 * v->z + m->e34 * v->w ,
		m->e41 * v->x + m->e42 * v->y + m->e43 * v->z + m->e44 * v->w);
}

double distpointplane3(pv3 normal , pp3 plpoint , pp3 distpoint)
{
	double a, b, c, d;

	a = normal->x;
	b = normal->y;
	c = normal->z;
	d = -(a * plpoint->x) - b * plpoint->y - c * plpoint->z;

	if (a != 0.0 && b != 0.0 && c != 0.0) {
		return fabs(a * distpoint->x + b * distpoint->y + c * distpoint->z + d) /
			sqrt((a * a) + (b * b) + (c * c));
	} else {
		return 0.0;
	}
}

pm4 init_matr_proj_persp3d(double dist)
{
	return newm4(
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 1 / dist , 0);
}

pm4 init_matr_proj_par3d()
{
	return newm4(
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 0 , 0 ,
		0 , 0 , 0 , 1);
}

void project3d_persp(plistface auxf, double d)
{
	auxf->faceitem->a->x = auxf->faceitem->a->x * d / auxf->faceitem->a->z;
	auxf->faceitem->a->y = auxf->faceitem->a->y * d / auxf->faceitem->a->z;
	auxf->faceitem->a->z = d;

	auxf->faceitem->b->x = auxf->faceitem->b->x * d / auxf->faceitem->b->z;
	auxf->faceitem->b->y = auxf->faceitem->b->y * d / auxf->faceitem->b->z;
	auxf->faceitem->b->z = d;

	auxf->faceitem->c->x = auxf->faceitem->c->x * d / auxf->faceitem->c->z;
	auxf->faceitem->c->y = auxf->faceitem->c->y * d / auxf->faceitem->c->z;
	auxf->faceitem->c->z = d;
}

void transf_viz_persp3d(plistface auxf,
        unsigned int width, unsigned int height, double zproj)
{
	pv3 auxv3 , aux1v3;
	pm3 auxmatr  , trmatr , auxmatr1;
	double umax, umin, vmax, vmin;

        auxv3=NULL;
        aux1v3=NULL;
        auxmatr=NULL;
        trmatr=NULL;
        auxmatr1=NULL;

	umin = 0;
	umax = (double) width;
	vmin = 0;
	vmax = (double) height;

	trinit3(&trmatr);

	auxmatr=intrans2d(zproj, zproj);
	auxmatr1=trinit3();
	trmatr = mul_pm3(auxmatr, auxmatr1);

	freem3(&auxmatr);
	auxmatr=inscale2d(0 ,
                0 ,
                (umax - umin) / (2 * zproj) ,
                (vmax - vmin) / (2 * zproj));
	freem3(&auxmatr1);
	auxmatr1=trmatr;
	trmatr = mul_pm3(auxmatr, auxmatr1);

	freem3(&auxmatr);
	auxmatr=intrans2d(umin, vmin);
	freem3(&auxmatr1);
	auxmatr1=trmatr;
	trmatr = mul_pm3(auxmatr, auxmatr1);
	
	freem3(&auxmatr);
	freem3(&auxmatr1);

	aux1v3=newv3(auxf->faceitem->a->x ,
                auxf->faceitem->a->y , 1);
	auxv3 = mul_pm3_pv3(trmatr, aux1v3);
	auxf->faceitem->a->x = auxv3->x;
	auxf->faceitem->a->y = auxv3->y;

	setv3(aux1v3 ,
                auxf->faceitem->b->x ,
		auxv3->y = auxf->faceitem->b->y ,
                1);
	freev3(&auxv3);
	auxv3 = mul_pm3_pv3(trmatr, aux1v3);
	auxf->faceitem->b->x = auxv3->x;
	auxf->faceitem->b->y = auxv3->y;

	setv3(aux1v3 , auxf->faceitem->c->x ,
		auxv3->y = auxf->faceitem->c->y ,
                1);
	freev3(&auxv3);
	auxv3 = mul_pm3_pv3(trmatr, aux1v3);
	auxf->faceitem->c->x = auxv3->x;
	auxf->faceitem->c->y = auxv3->y;

	freev3(&auxv3);
	freev3(&aux1v3);
	freem3(&trmatr);
}

void projectpar(plistface auxf, pm4 auxmatr)
{
	auxf->faceitem->a->z = 0;
	auxf->faceitem->b->z = 0;
	auxf->faceitem->c->z = 0;
}

void transf_viz_par3d(plistface auxf, unsigned int width, unsigned int height)
{
	pv3 auxv3 = NULL , aux1v3=NULL;
	pm3 auxmatr=NULL , auxmatr1=NULL , trmatr=NULL;
	double umax , umin , vmax , vmin;

	umin = 0;
	umax = (double) width;
	vmin = 0;
	vmax = (double) height;

	auxmatr1=trinit3();

	auxmatr=intrans2d(1, 1);
	trmatr = mul_pm3(auxmatr, auxmatr1);

	freem3(&auxmatr1);
	auxmatr1=trmatr;
	auxmatr=inscale2d(0 ,
                0 ,
                (umax - umin) / 2 ,
                (vmax - vmin) / 2);
	trmatr = mul_pm3(auxmatr, auxmatr1);

	freem3(&auxmatr1);
	auxmatr1=trmatr;
	auxmatr=intrans2d(umin, vmin);
	trmatr = mul_pm3(auxmatr, auxmatr1);

	freem3(&auxmatr);
	freem3(&auxmatr1);

	aux1v3=newv3(auxf->faceitem->a->x , auxf->faceitem->a->y , 1);
	auxv3 = mul_pm3_pv3(trmatr, aux1v3);
	auxf->faceitem->a->x = auxv3->x;
	auxf->faceitem->a->y = auxv3->y;

	setv3(aux1v3 ,
                auxf->faceitem->b->x ,
                auxf->faceitem->b->y , 1);
	freev3(&auxv3);
	auxv3 = mul_pm3_pv3(trmatr, aux1v3);
	auxf->faceitem->b->x = auxv3->x;
	auxf->faceitem->b->y = auxv3->y;

	setv3(aux1v3 ,
                auxf->faceitem->c->x ,
                auxf->faceitem->c->y , 1);
	freev3(&auxv3);
	auxv3 = mul_pm3_pv3(trmatr, aux1v3);
	auxf->faceitem->c->x = auxv3->x;
	auxf->faceitem->c->y = auxv3->y;

	free(auxv3);
	free(aux1v3);
	free(trmatr);
}

