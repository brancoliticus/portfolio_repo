#include "graphics3d.h"
/*
void updatezbuf(unsigned int i , unsigned int j , point2 p , point2 q
				, double depth , double deptha , double depthb  , double **zbuf){
	point2 auxp;
	double auxd;

	auxp.x=i;
	auxp.y=j;

	if(depth != deptha && depth != depthb){
            if(distpoints2(p , q) != 0.0){
                depth=distpoints2(p , q) * (deptha - depthb) / distpoints2(p , q) + depthb;
            }
            else{
                depth=deptha;
            }
	}

	auxd=distpoints2(p , q);
	if(auxd != 0.0){
		depth=auxd * (deptha - depthb) / auxd;
	}
	else{
		depth=deptha;
	}

	if(depth > zbuf[i][j]){
		zbuf[i][j]=depth;
	}
}

int faceinvolumepersp(plistface auxf , double zmin){
	if(	auxf->face.a.x >= auxf->face.a.z &&
		auxf->face.a.x <= (- auxf->face.a.z) &&
		auxf->face.a.y >= auxf->face.a.z &&
		auxf->face.a.y <= (- auxf->face.a.z) &&
		auxf->face.a.z <= zmin &&
		auxf->face.a.z >= -1 &&
		auxf->face.b.x >= auxf->face.b.z &&
		auxf->face.b.x <= (- auxf->face.b.z) &&
		auxf->face.b.y >= auxf->face.b.z &&
		auxf->face.b.y <= (- auxf->face.b.z) &&
		auxf->face.b.z <= zmin &&
		auxf->face.b.z >= -1 &&
		auxf->face.c.x >= auxf->face.c.z &&
		auxf->face.c.x <= (- auxf->face.c.z) &&
		auxf->face.c.y >= auxf->face.c.z &&
		auxf->face.c.y <= (- auxf->face.c.z) &&
		auxf->face.c.z <= zmin &&
		auxf->face.c.z >= -1){

		return 1;
	}

	return 0;
}

int faceinvolumepar(plistface auxf){
	if(	auxf->face.a.x >= -1 &&
		auxf->face.a.x <= 1 &&
		auxf->face.a.y >= -1 &&
		auxf->face.a.y <= 1 &&
		auxf->face.a.z <= 0 &&
		auxf->face.a.z >= -1 &&

		auxf->face.b.x >= -1 &&
		auxf->face.b.x <= 1 &&
		auxf->face.b.y >= -1 &&
		auxf->face.b.y <= 1 &&
		auxf->face.b.z <= 0 &&
		auxf->face.b.z >= -1 &&

		auxf->face.c.x >= -1 &&
		auxf->face.c.x <= 1 &&
		auxf->face.c.y >= -1 &&
		auxf->face.c.y <= 1 &&
		auxf->face.c.z <= 0 &&
		auxf->face.c.z >= -1){

		return 1;
	}

	return 0;
}

void computeuvn(vector3 *u , vector3 *v , vector3 *n , vector3 vpn , vector3 vup){

	double auxd1 ;
	vector3 auxv;

	auxd1=sqrt( vpn.x*vpn.x + vpn.y*vpn.y + vpn.z*vpn.z );// | vpn | //determinare u , v , n
	n->x=vpn.x / auxd1 ; n->y=vpn.y / auxd1 ; n->z=vpn.z / auxd1 ;

	auxv=cross_product3(vup , vpn);
	auxd1=sqrt( auxv.x*auxv.x + auxv.y*auxv.y + auxv.z*auxv.z ); // |VUP x VPN|
	u->x=auxv.x / auxd1 ; u->y=auxv.y / auxd1 ; u->z=auxv.z / auxd1;

	(*v)=cross_product3((*n) , (*u));// u , v , n
}

point3 computeprpuvn(vector3 u , vector3 v , vector3 n , point3 prp){

	point3 prpuvn;
	matrice4 auxmatr;
	vector4 auxv;

	auxmatr.e11=u.x ; auxmatr.e12=u.y ; auxmatr.e13=u.z ; auxmatr.e14=0 ; //prp (x,y,z)->(u,v,n)
	auxmatr.e21=v.x ; auxmatr.e22=v.y ; auxmatr.e23=v.z ; auxmatr.e24=0 ;
	auxmatr.e31=n.x ; auxmatr.e32=n.y ; auxmatr.e33=n.z ; auxmatr.e34=0 ;
	auxmatr.e41=0   ; auxmatr.e42=0   ; auxmatr.e43=0   ; auxmatr.e44=1 ;

	auxv.x=prp.x;
	auxv.y=prp.y;
	auxv.z=prp.z;
	auxv.w=1;
	auxv=multiply_vector4(auxmatr , auxv);
	prpuvn.x=auxv.x;
	prpuvn.y=auxv.y;
	prpuvn.z=auxv.z;//prp (x,y,z)->(u,v,n)

	return prpuvn;
}

char cross(point2 *x , point2 p1d1u , point2 p2d1u , point2 p1d2u , point2 p2d2u){

	point3 p1d1 , p2d1 , p1d2 , p2d2 , ret ;

	double r , s , num ;

	p1d1.x=(double) p1d1u.x ; p1d1.y=(double) p1d1u.y;
	p2d1.x=(double) p2d1u.x ; p2d1.y=(double) p2d1u.y;
	p1d2.x=(double) p1d2u.x ; p1d2.y=(double) p1d2u.y;
	p2d2.x=(double) p2d2u.x ; p2d2.y=(double) p2d2u.y;

	num=(p2d1.x - p1d1.x) * (p2d2.y - p1d2.y) -
		(p2d1.y - p1d1.y) * (p2d2.x - p1d2.x) ;



	r=(	(p1d1.y - p1d2.y) * (p2d2.x - p1d2.x) -
		(p1d1.x - p1d2.x) * (p2d2.y - p1d2.y)  );

	if(fabs(r) < 0.00000001 && fabs(num) < 0.00000001){
		return 'c';//coincidenta
	}

	if( fabs(num) < 0.00000001 ){
		return 'p' ;//paralelism
	}

	s=(	(p1d1.y - p1d2.y) * (p2d1.x - p1d1.x) -
		(p1d1.x - p1d2.x) * (p2d1.y - p1d1.y)  );

	if( r / num < 0.0 || r / num > 1.0 ||
		s / num < 0.0
		|| s / num > 1.0 ){

			return 'e';//intersectie in afara segmentelor (exterior)
	}

	ret.x=p1d1.x + (r / num) * (p2d1.x - p1d1.x);
	ret.y=p1d1.y + (r / num) * (p2d1.y - p1d1.y);

	if(ret.x > 0){
		x->x=(unsigned int) ret.x;
	}
	else{
		x->x=0;
	}

	if(ret.y > 0){
		x->y=(unsigned int) ret.y;
	}
	else{
		x->y=0;
	}

	return 'i';//intersectie si punct de intersectie calculat

}
void afispersp(XPM* img , point3 vrp , vector3 vpn , vector3 vup ,
			   point3 prp , point3 uvmin , point3 uvmax , plistface radf){

	matrice4 trmatr , auxmatr , rot;
	vector3 u , v , n;
	vector4 auxv4;
	double auxd1 , auxd2 , auxd3 , auxd4 , auxd5 , f , b , d , zmin ;
	point3 prpuvn;
	plistface auxf;
	point3 pa , pb , pc , p1 , p2 , p3 , p4 , p5 ;
	char auxc1 , auxc2 , auxc3 ;

	int i,j;
	double **zbuf=malloc(img->height * sizeof(double*));
	for(i=0 ; i < img->height ; i=i+1){
		zbuf[i]=malloc(img->width * sizeof(double));
		for(j=0 ; j < img->width ; j=j+1){
			zbuf[i][j]=-2;
		}
	}

	trinit4(&trmatr);//I(4) initial

	intrans3d(&auxmatr , -vrp.x , -vrp.y , -vrp.z);//T(-VRP)
	trmatr=multiply_matrice4(auxmatr , trmatr);

	computeuvn(&u , &v , &n , vpn , vup);

	rot.e11=u.x ; rot.e12=u.y ; rot.e13=u.z ; rot.e14=0;//R uvn peste xyz
	rot.e21=v.x ; rot.e22=v.y ; rot.e23=v.z ; rot.e24=0;
	rot.e31=n.x ; rot.e32=n.y ; rot.e33=n.z ; rot.e34=0;
	rot.e41=0   ; rot.e42=0   ; rot.e43=0;  ; rot.e44=1;
	trmatr=muliply_matrice4(rot , trmatr);

	prpuvn=computeprpuvn(u , v , n , prp);

	intrans3d(&auxmatr , -prpuvn.x , -prpuvn.y , -prpuvn.z);//T(-PRP) in coordonate (u,v,n)
	trmatr=multiply_matrice4(auxmatr , trmatr);

	auxd1=(0.5 * (uvmax.x + uvmin.x) - prpuvn.x) / prpuvn.z ;//forfecare pe axa z
	auxd2=(0.5 * (uvmax.y + uvmin.y) - prpuvn.y) / prpuvn.z ;
	inforfxy3d(&auxmatr , auxd1 , auxd2);
	trmatr=multiply_matrice4(auxmatr , trmatr);

	f=distpoints3(vrp , prp) * 0.9;//f=dist intre
	b=-(9 * f);//determinare f si b

	auxd1=(-2) * prpuvn.z / ((uvmax.x - uvmin.x) * (b - prpuvn.z)) ;
	auxd2=(-2) * prpuvn.z / ((uvmax.y - uvmin.y) * (b - prpuvn.z)) ;
	auxd3=(-1) / (-prpuvn.z + b);
	inscale3d(&auxmatr , auxd1 , auxd2 , auxd3);
	trmatr=multiply_matrice4(auxmatr , trmatr);               //scalare perspectiva

	d=prpuvn.z / (b-prpuvn.z);
	zmin=-((f-prpuvn.z) / (b-prpuvn.z));

	initmatrprojpersp(&auxmatr , d);

	auxf=radf;
	while(auxf != NULL){

		auxv4.x=auxf->face.a.x ; auxv4.y=auxf->face.a.y ; auxv4.z=auxf->face.a.z ; auxv4.w=1;
		auxv4=multiply_vector4(trmatr , auxv4);
		auxf->face.a.x=auxv4.x ; auxf->face.a.y=auxv4.y ; auxf->face.a.z=auxv4.z ;

		auxv4.x=auxf->face.b.x ; auxv4.y=auxf->face.b.y ; auxv4.z=auxf->face.b.z ; auxv4.w=1;
		auxv4=multiply_vector4(trmatr , auxv4);
		auxf->face.b.x=auxv4.x ; auxf->face.b.y=auxv4.y ; auxf->face.b.z=auxv4.z ;

		auxv4.x=auxf->face.c.x ; auxv4.y=auxf->face.c.y ; auxv4.z=auxf->face.c.z ; auxv4.w=1;
		auxv4=multiply_vector4(trmatr , auxv4);
		auxf->face.c.x=auxv4.x ; auxf->face.c.y=auxv4.y ; auxf->face.c.z=auxv4.z ;
		//transformare perspectiva pt punctele dintr-un triunghi

		//if(	faceinvolumepersp(auxf , zmin) == 1){

			auxd1=auxf->face.a.z;
			auxd2=auxf->face.b.z;
			auxd3=auxf->face.c.z;//cele 3 coordonate de adancime pt zbuffer
			projectpersp(auxf  , fabs(d));
			transfvizpersp(auxf , img->width , img->height , fabs(d));

			pa.x=(unsigned int) auxf->face.a.x; pa.y=img->height - (unsigned int) auxf->face.a.y;
			pb.x=(unsigned int) auxf->face.b.x; pb.y=img->height - (unsigned int) auxf->face.b.y;
			pc.x=(unsigned int) auxf->face.c.x; pc.y=img->height - (unsigned int) auxf->face.c.y;

			for(i=0 ; i < img->height ; i++){

				p1.x=0			; p1.y=i ;
				p2.x=img->width ; p2.y=i ;

				auxc1=cross(&p3 , p1 , p2 , pa , pb);
				auxc2=cross(&p4 , p1 , p2 , pb , pc);
				auxc3=cross(&p5 , p1 , p2 , pc , pa);

				if(auxc1 == 'i' && auxc2 == 'i' && auxc3 == 'i'){
					if((p4.x < p1.x && p3.x < p5.x)||
						(p5.x < p3.x && p3.x < p4.x)){
						auxc1='a';
					}
					else if((p3.x < p4.x && p4.x < p5.x)||
						(p5.x < p4.x && p4.x < p3.x)){
							auxc2='a';
					}
					else{
						auxc3='a';
					}
				}

				if((auxc1 == 'i' && auxc2 == 'i') ||
					(auxc2 == 'i' && auxc3 == 'i') ||
					(auxc3 == 'i' && auxc1 == 'i')){

					if(auxc1 != 'i'){
						if(distPoints(pb , pc) != 0.0){
							auxd4=distPoints(pb , pc) * (auxd2 - auxd3) /
								  distPoints(pb , pc) + auxd3;
						}
						else{
							auxd4=auxd2;
						}

						if(distPoints(pc , pa) != 0.0){
							auxd5=distPoints(pc , pa) * (auxd3 - auxd1) /
								  distPoints(pc , pa) + auxd1;
						}
						else{
							auxd5=auxd3;
						}

						zXPMline(img , p4 , p5 , auxd4 , auxd5 , d , zbuf);
					}
					else if(auxc2 != 'i'){
						if(distPoints(pc , pa) != 0.0){
							auxd4=distPoints(pc , pa) * (auxd3 - auxd1) /
								  distPoints(pc , pa) + auxd1;
						}
						else{
							auxd4=auxd3;
						}

						if(distPoints(pa , pb) != 0.0){
							auxd5=distPoints(pa , pb) * (auxd1 - auxd2) /
								  distPoints(pa , pb) + auxd2;
						}
						else{
							auxd5=auxd1;
						}

						zXPMline(img , p3 , p5 , auxd4 , auxd5 , d , zbuf);
					}
					else{
						if(distPoints(pb , pc) != 0.0){
							auxd4=distPoints(pa , pb) * (auxd1 - auxd2) /
								  distPoints(pa , pb) + auxd2;
						}
						else{
							auxd4=auxd1;
						}

						if(distPoints(pc , pa) != 0.0){
							auxd5=distPoints(pb , pc) * (auxd2 - auxd3) /
								  distPoints(pb , pc) + auxd3;
						}
						else{
							auxd5=auxd1;
						}

						zXPMline(img , p3 , p4 , auxd4 , auxd5 , d , zbuf);
					}
				}
			}
		//}

		auxf=auxf->next;
	}

	for(i=0 ; i < img->height ; i=i+1){
		for(j=0 ; j < img->width ; j=j+1){
			if(zbuf[i][j] != -2){
				putXPMpixel(img , i , j , 1);
			}
			else{
				putXPMpixel(img , i , j , 0);
			}
		}
	}

	for(i=0 ; i < img->height ; i=i+1){
		free(zbuf[i]);
	}
	free(zbuf);

}
 */
/*
void afisparalel(XPM* img , point3 vrp , vector3 vpn , vector3 vup ,
				 point3 prp , point3 uvmin , point3 uvmax , plistface radf){


	matrice4 trmatr , auxmatr , rot;
	vector3 u , v , n;
	vector4 auxv4;
	double auxd1 , auxd2 , auxd3 , auxd4 , auxd5 , f , b ;
	point3 prpuvn ;
	plistface auxf;
	Point pa , pb , pc , p1 , p2 , p3 , p4 , p5 ;
	char auxc1 , auxc2 , auxc3 ;

	int i,j;
	double **zbuf=malloc(img->height * sizeof(double*));
	for(i=0 ; i < img->height ; i=i+1){
		zbuf[i]=malloc(img->width * sizeof(double));
		for(j=0 ; j < img->width ; j=j+1){
			zbuf[i][j]=-2;
		}
	}


	trinit4(&trmatr);//I(4) initial

	intrans3d(&auxmatr , -vrp.x , -vrp.y , -vrp.z);//T(-VRP)
	trmatr=mulm4(auxmatr , trmatr);

	computeuvn(&u , &v , &n , vpn , vup);

	rot.e11=u.x ; rot.e12=u.y ; rot.e13=u.z ; rot.e14=0;//R uvn peste xyz
	rot.e21=v.x ; rot.e22=v.y ; rot.e23=v.z ; rot.e24=0;
	rot.e31=n.x ; rot.e32=n.y ; rot.e33=n.z ; rot.e34=0;
	rot.e41=0   ; rot.e42=0   ; rot.e43=0;  ; rot.e44=1;
	trmatr=mulm4(rot , trmatr);

	prpuvn=computeprpuvn(u , v , n , prp);

	auxd1=(0.5 * (uvmax.x + uvmin.x) - prpuvn.x) / prpuvn.z ;//forfecare pe axa z
	auxd2=(0.5 * (uvmax.y + uvmin.y) - prpuvn.y) / prpuvn.z ;
	inforfxy3d(&auxmatr , auxd1 , auxd2);
	trmatr=mulm4(auxmatr , trmatr);

	auxv4.x=vrp.x ; auxv4.y=vrp.y ; auxv4.z=vrp.z ; auxv4.w=1 ;
	auxv4=mulv4(trmatr , auxv4);
	vrp.x=auxv4.x ; vrp.y=auxv4.y ; vrp.z=auxv4.z ;
	auxv4.x=prp.x ; auxv4.y=prp.y ; auxv4.z=prp.z ; auxv4.w=1 ;
	auxv4=mulv4(trmatr , auxv4);
	vrp.x=auxv4.x ; vrp.y=auxv4.y ; vrp.z=auxv4.z ;
	f=distpoints3(vrp , prp);//f=dist intre
	b=-(9 * f);//determinare f si b

	auxd1=- ((uvmax.x + uvmin.x) / 2) ;
	auxd2=- ((uvmax.y + uvmin.y) / 2) ;
	auxd3= -f;
	intrans3d(&auxmatr , auxd1 , auxd2 , auxd3);
	trmatr=mulm4(auxmatr , trmatr);//translatie pt proiectie paralela

	auxd1=2 / (uvmax.x - uvmin.x);
	auxd2=2 / (uvmax.y - uvmin.y);
	auxd3=1 / (f - b);
	inscale3d(&auxmatr , auxd1 , auxd2 , auxd3);
	trmatr=mulm4(auxmatr , trmatr);//scalare pt proiectie paralela

	initmatrprojpar(&auxmatr);

	auxf=radf;
	while(auxf != NULL){
		auxv4.x=auxf->face.a.x ; auxv4.y=auxf->face.a.y ; auxv4.z=auxf->face.a.z ; auxv4.w=1;
		auxv4=mulv4(trmatr , auxv4);
		auxf->face.a.x=auxv4.x ; auxf->face.a.y=auxv4.y ; auxf->face.a.z=auxv4.z;

		auxv4.x=auxf->face.b.x ; auxv4.y=auxf->face.b.y ; auxv4.z=auxf->face.b.z ; auxv4.w=1;
		auxv4=mulv4(trmatr , auxv4);
		auxf->face.b.x=auxv4.x ; auxf->face.b.y=auxv4.y ; auxf->face.b.z=auxv4.z;

		auxv4.x=auxf->face.c.x ; auxv4.y=auxf->face.c.y ; auxv4.z=auxf->face.c.z ; auxv4.w=1;
		auxv4=mulv4(trmatr , auxv4);
		auxf->face.c.x=auxv4.x ; auxf->face.c.y=auxv4.y; auxf->face.c.z=auxv4.z;
		//transformare paralela pt punctele dintr-un triunghi

		//if(faceinvolumepar(auxf) == 1){

			projectpar(auxf , auxmatr);
			transfvizpar(auxf , img->width , img->height);

			pa.x=(unsigned int) auxf->face.a.x; pa.y=img->height - (unsigned int) auxf->face.a.y;
			pb.x=(unsigned int) auxf->face.b.x; pb.y=img->height - (unsigned int) auxf->face.b.y;
			pc.x=(unsigned int) auxf->face.c.x; pc.y=img->height - (unsigned int) auxf->face.c.y;

			auxd1=auxf->face.a.z;
			auxd2=auxf->face.b.z;
			auxd3=auxf->face.c.z;

			for(i=0 ; i < img->height ; i++){

				p1.x=0			; p1.y=i ;
				p2.x=img->width ; p2.y=i ;

				auxc1=cross(&p3 , p1 , p2 , pa , pb);
				auxc2=cross(&p4 , p1 , p2 , pb , pc);
				auxc3=cross(&p5 , p1 , p2 , pc , pa);

				if(auxc1 == 'i' && auxc2 == 'i' && auxc3 == 'i'){
					if((p2.x < p1.x && p1.x < p3.x)||
						(p3.x < p1.x && p1.x < p2.x)){
						auxc1='a';
					}
					else if((p1.x < p2.x && p2.x < p3.x)||
						(p3.x < p2.x && p2.x < p1.x)){
							auxc2='a';
					}
					else{
						auxc3='a';
					}
				}
				if((auxc1 == 'i' && auxc2 == 'i') ||
					(auxc2 == 'i' && auxc3 == 'i') ||
					(auxc3 == 'i' && auxc1 == 'i')){

					if(auxc1 != 'i'){
						if(distPoints(pb , pc) != 0.0){
							auxd4=distPoints(pb , pc) * (auxd2 - auxd3) /
								  distPoints(pb , pc) + auxd3;
						}
						else{
							auxd4=auxd2;
						}

						if(distPoints(pc , pa) != 0.0){
							auxd5=distPoints(pc , pa) * (auxd3 - auxd1) /
								  distPoints(pc , pa) + auxd1;
						}
						else{
							auxd5=auxd3;
						}

						zXPMline(img , p4 , p5 , auxd4 , auxd5 , -0.1 , zbuf);
					}
					else if(auxc2 != 'i'){
						if(distPoints(pc , pa) != 0.0){
							auxd4=distPoints(pc , pa) * (auxd3 - auxd1) /
								  distPoints(pc , pa) + auxd1;
						}
						else{
							auxd4=auxd3;
						}

						if(distPoints(pa , pb) != 0.0){
							auxd5=distPoints(pa , pb) * (auxd1 - auxd2) /
								  distPoints(pa , pb) + auxd2;
						}
						else{
							auxd5=auxd1;
						}

						zXPMline(img , p3 , p5 , auxd4 , auxd5 , -0.1 , zbuf);
					}
					else{
						if(distPoints(pb , pc) != 0.0){
							auxd4=distPoints(pa , pb) * (auxd1 - auxd2) /
								  distPoints(pa , pb) + auxd2;
						}
						else{
							auxd4=auxd1;
						}

						if(distPoints(pc , pa) != 0.0){
							auxd5=distPoints(pb , pc) * (auxd2 - auxd3) /
								  distPoints(pb , pc) + auxd3;
						}
						else{
							auxd5=auxd1;
						}

						zXPMline(img , p3 , p4 , auxd4 , auxd5 , -0.1 , zbuf);
					}
				}
			}
		//}

		auxf=auxf->next;
	}

	for(i=0 ; i < img->height ; i=i+1){
		for(j=0 ; j < img->width ; j=j+1){
			if(zbuf[i][j] != -2){
				putXPMpixel(img , i , j , 1);
			}
			else{
				putXPMpixel(img , i , j , 0);
			}
		}
	}

	for(i=0 ; i < img->height ; i=i+1){
		free(zbuf[i]);
	}
	free(zbuf);

}


void clip3d(plistobject3d *obj , view3d *v){
    
}

plistline2* display_scene3d_to_screen(scene3d *s , int projection_type){
    plistline2 root=NULL;
    objectvisibility *objvis;

    // input 3d object list => output objects that fit in the 3d view
    objvis=clip3d(s->lobj3d , NULL);

    //input objects that fit in the 3d view
    //=> output list of 2d lines to display in the view reference plane
    if(projection_type == PERSPECTIVE_PROJECTION){
        root=project_perspective_selective(s , objvis);
    }
    else if(projection_type == PARALEL_PROJECTION){
        root=project_paralel_selective(s , objvis);
    }

    //input list of 2d lines to display
    //=> output 2d coordinates list for lines on screen
    visualisation_transformation(root);

}
*/
