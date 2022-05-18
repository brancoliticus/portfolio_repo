#ifndef _MATHLIB_H
#define	_MATHLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "data_structures.h"

pm3 trinit3();

pm4 trinit4();

double deg2rad(double degrees);

double distpoints2(pp2 a , pp2 b);

double distpoints3(pp3 a , pp3 b);

pv3 cross_product3(pv3 a, pv3 b);

double dot_product3(pv3 a, pv3 b);

pm3 intrans2d(double tx , double ty);

/*(px,py):rotation reference point
angle:rotation angle in degrees*/
pm3 inrotate2d(double px , double py , double angle);

/*(px,py):scale reference point
(sx,sy):scale factors*/
pm3 inscale2d(double px , double py , double sx, double sy);

pm3 mul_pm3(pm3 m1, pm3 m2);

pv3 mul_pm3_pv3(pm3 m, pv3 v);

pm4 intrans3d(double tx, double ty, double tz);

pm4 inrotate3dx(double angle);

pm4 inrotate3dy(double angle);

pm4 inrotate3dz(double angle);

pm4 inscale3d(double sx, double sy, double sz);

pm4 inforfxy3d(double shx, double shy);

void transform_point2(pp2 *return_point ,
        pm3 transformation_matrice , pp2 p);

pm3 transfviz_2d_matrice(int wl , int wr , int wb , int wt ,
        int vl , int vr , int vb , int vt);

pm4 multiply_matrice4(pm4 m1 , pm4 m2);

pv4 multiply_vector4(pm4 m, pv4 v);

double distpointplane3(pv3 normal , pp3 plpoint , pp3 distpoint);

pm4 init_matr_proj_persp3d(double dist);

pm4 init_matr_proj_par3d();

void project3d_persp(plistface auxf, double d);

void transf_viz_persp3d(plistface auxf, unsigned int width, unsigned int height, double zproj);

void projectpar(plistface auxf , pm4 auxmatr);

void transf_viz_par3d(plistface auxf, unsigned int width, unsigned int height);

pp2 line2_axis_intersection(pline2 l1 , pline2 l2);

#ifdef	__cplusplus
}
#endif

#endif
