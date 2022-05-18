#ifndef _DATA_STRUCTURES_H
#define	_DATA_STRUCTURES_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*point2*/
    
    typedef struct p2{
        int x;
        int y;
    } *pp2;

    pp2 newp2(int x, int y);
    void freep2(pp2 *p);

    /*point3*/

    typedef struct p3{
        double x;
        double y;
        double z;
    } *pp3;

    pp3 newp3(int x, int y, int z);
    void freep3(pp3 *p);

    /*vector3*/

    typedef struct v3 {
        double x;
        double y;
        double z;

    } *pv3;

    pv3 newv3(double x, double y, double z);
    void freev3(pv3 *v);
    void setv3(pv3 v, double x , double y , double z);
    pv3 v3_from_p3(pp3 a , pp3 b);

    /*matrice3*/
    
    typedef struct m3 {
        double e11, e12, e13;
        double e21, e22, e23;
        double e31, e32, e33;

    } *pm3;

    pm3 newm3(double e11, double e12, double e13,
            double e21, double e22, double e23,
            double e31, double e32, double e33);
    void freem3(pm3 *m);
#define TRANSLATION 't'
#define SCALING 's'
#define ROTATION 'r'
    pm3 parse_transformations_file(char *transform_file_name);

    /*matrice4*/
    
    typedef struct m4 {
        double e11, e12, e13, e14;
        double e21, e22, e23, e24;
        double e31, e32, e33, e34;
        double e41, e42, e43, e44;
    } *pm4;

    pm4 newm4(double e11, double e12, double e13, double e14,
            double e21, double e22, double e23, double e24,
            double e31, double e32, double e33, double e34,
            double e41, double e42, double e43, double e44);
    void freem4(pm4 *m);

    /*vector4*/
    
    typedef struct v4 {
        double x;
        double y;
        double z;
        double w;
    } *pv4;

    pv4 newv4(double x, double y, double z, double w);
    void freev4(pv4 *v);

    /*polygon*/
    
    typedef struct p2l {
        pp2 a;
        struct p2l *prevpoint;
        struct p2l *nextp;
    }*ppoly;
    typedef ppoly pp2_list;

    /* list of 2D points that needs good input
     * used also as plain list */
    ppoly newpoly(pp2 p);

    /* free all including the points of the polygon*/
    void freepoly(ppoly *rad);
    /* this will not create a new polygon */
    void add_p2_to_poly(pp2 p, ppoly rad);

    /* add points from a polygon to an existing polygon
     * first source and last destination points get linked
     * also last source and first destination points get linked
     * NOT TESTED ONCE */
    void add_poly_to_poly(ppoly source , ppoly destination);
    ppoly parsepolfile_to_polygon(char *polygon_file_name, int image_height);

    /* shift values of all polygon points as if the axis origin moved */
    ppoly move_origin_to(ppoly rad,
            int new_x, int new_y);

    /* TODO add 2d points ordered by the x coordinate ascending */
    void add_p2_to_poly_xord(pp2 p , ppoly rad);

    typedef struct poly_it {
        ppoly rad;
        ppoly current_poly_node;
        int done;
    } *ppoly_it;
    typedef ppoly_it pp2l_it;

    ppoly_it newpoly_it(ppoly rad);
    
    /* return NULL after last point */
    pp2 next_polyp(ppoly_it it);

    /* return to first point in polygon */
    void reset_poly_it(ppoly_it it);
    void freepoly_it(ppoly_it *it);

    /* self describing
     * return
     * 0 point is not inside polygon
     * != 0 point is inside polygon
     *
     * the iterator must be at the first point in polygon
     * the iterator is at the first point in polygon on return from function */
    int isp2_in_poly(pp2 p , ppoly_it it);

    /* polygon_list */
    
    typedef struct poly_l{
        ppoly p;
        struct poly_l *next_poly_l;
    }*ppoly_l;

    ppoly_l newpoly_l(ppoly p);
    void freepoly_l(ppoly_l *rad);
    void add_poly_to_poly_l(ppoly p , ppoly_l *plrad);


    typedef struct poly_l_it{
        ppoly_l rad;
        ppoly_l current_poly_l;
    }*ppoly_l_it;

    ppoly_l_it newpoly_l_it(ppoly_l rad);
    ppoly_l next_poly_l(ppoly_l_it it);
    ppoly next_poly_l_poly(ppoly_l_it it);
    void resetpoly_l_it(ppoly_l_it it);
    void freepoly_l_it(ppoly_l_it *it);

    /* face */
    
    typedef struct f {
        pp3 a;
        pp3 b;
        pp3 c;
    } face;

    face* newface(pp3 a , pp3 b , pp3 c);
    void freeface(face **f);

    typedef struct listface {
        face *faceitem;
        struct listface *next;
    } *plistface;

    void add_face_to_list(face *f, plistface *radf);
    void free_face_list(plistface *radf);

    typedef struct listpoint3 {
        pp3 vertex;
        struct listpoint3 *next;
    } *plistpoint3;

    void add_p3_to_list(pp3 vertex, plistpoint3 *radv);
    void free_p3_list(plistpoint3 *radv);

    /* line2 */
    
    typedef struct line2{
        pp2 a;
        pp2 b;
    }*pl2;
    typedef pl2 pline2;

    pline2 newline2(pp2 a , pp2 b);
    void freeline2(pline2 *pl);
    void setline2(pline2 pl, int xa, int ya, int xb, int yb);

    typedef struct  listline2{
        pline2 line;
        struct listline2 *next;
    } *ll2;
    typedef ll2 plistline2;

    plistline2 add_line2_to_list(pline2 pl , plistline2 rad);
    void free_line2_list(plistline2 *rad);
    plistline2 parsepsfile_to_line2_list(char *filename);
    plistline2 lines_at_height_in_poly(ppoly rad , pline2 line_at_height);

    /* line3 */
    
    typedef struct line3{
        pp3 a;
        pp3 b;
    }*pl3;
    typedef pl3 pline3;

    pline3 newline3(pp3 a , pp3 b);
    void freeline3(pline3 *l);

    typedef struct listline3 {
        pline3 line;
        struct listline3 *next_line;
    } *plistline3;

    plistline3 add_line3_to_list(pline3 line, plistline3 rad);
    void free_line3_list(plistline3 *rad);

    /* TODO 3d stuff */
    
    typedef struct {
        pp2 uvmin;
        pp2 uvmax;
    } vrefcoord;

    typedef struct {
        pp3 view_reference_point; /*vrp*/
        pv3 view_plane_normal; /*vpn*/
        pv3 view_plane_up; /*vup*/
        pp3 projection_reference_point; /*prp*/
        vrefcoord view_reference_coordinates; /*vrc*/
        int projection_type; /*pt*/
    } view3d;

    /*void init_view3d(view3d *v , point3 *vrp , vector3 *vpn , vector3 *vup , point3 *prp ,
        vrefcoord *vrc , int *pt); */

    /*
    typedef struct{

    }object3d;

    typedef struct listobject3d{
        face f;
        object3d *next;
    }*plistobject3d;

    typedef struct objectvisibility{
        int object_count;
        char *data;
    }objectvisibility;
     */
    /*void visibility_set_object_count(objectvisibility *objvus , int count);
    void visibility_set_visible(objectvisibility *objvis , int index);
    void visibility_set_not_visible(objectvisibility *objvis , int index);
    int visibility_is_visible(objectvisibility *objvis , int index);
     *
    typedef struct{
        plistobject3d lobj3d;
        view3d v3d;
    }scene3d;

    void scene3d_set_view3d(scene3d *scene , view3d *v3d);
    void scene3d_add_object3d(scene3d *scene , object3d *o3d);
    void scene3d_zero(scene3d *s);
     */

#ifdef	__cplusplus
}
#endif

#endif
