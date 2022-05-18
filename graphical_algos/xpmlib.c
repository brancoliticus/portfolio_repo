#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "data_structures.h"
#include <stdlib.h>
#include <math.h>

#include "xpmlib.h"
#include "mathlib.h"


/* initXPM initializeaza structura asociata unei imagini in
  formatul XPM; Aceasta va aloca memoria necesara pentru 
  tabela de culori (in functie de numarul de caractere/pixel
  si de numarul de culori utilizate) si zona de date
  (in functie de latime si inaltime); */

XPM* initXPM ( unsigned int width, unsigned int height, unsigned int cpp, unsigned int ncolors )
{

	int i;


	XPM *imagine = ( XPM* ) malloc ( sizeof ( XPM ) );

	imagine->width		= width;
	imagine->height		= height;
	imagine->cpp		= cpp;
	imagine->ncolors	= ncolors;

	imagine->colta	= ( Color* ) malloc ( sizeof ( Color ) * ncolors );

	for ( i = 0 ; i < ncolors ; i++ )
	{
		imagine->colta[i].pchars = ( unsigned char* ) malloc ( cpp + 1 );
	}

	imagine->data	= ( unsigned int** )	malloc ( height * sizeof ( unsigned int* ) );

	if ( imagine->data == NULL )
	{
		printf ( "\neroare de alocare" );
		getchar();
	}

	for ( i = 0 ; i < height ; i++ )
	{
		imagine->data[i] = ( unsigned int* ) malloc ( width * sizeof ( unsigned int ) );

		if ( imagine->data[i] == NULL )
		{
			printf ( "\neroare de alocare" );
			getchar();
		}
	}

	return imagine;

}

/* freeXPM va elibera memoria alocata prin folosirea initXPM */

void freeXPM ( XPM **imagine )
{

	int i;

	if ( *imagine != NULL )
	{
		if ( ( *imagine )->colta != NULL )
		{
			for ( i = 0 ; i < ( *imagine )->ncolors ; i++ )
			{
				if ( ( *imagine )->colta[i].pchars != NULL )
				{
					free ( ( *imagine )->colta[i].pchars );
					( *imagine )->colta[i].pchars = NULL;
				}
			}

			free ( ( *imagine )->colta );

			( *imagine )->colta = NULL;
		}

		if ( ( *imagine )->data != NULL )
		{
			for ( i = 0 ; i < ( *imagine )->height ; i++ )
			{
				if ( ( *imagine )->data[i] != NULL )
				{
					free ( ( *imagine )->data[i] );
					( *imagine )->data[i] = NULL;
				}
			}

			free ( ( *imagine )->data );

			( *imagine )->data = NULL;
		}

		free ( *imagine );

		*imagine = NULL;
	}

}

/* putXPMpixel scrie un pixel la coordonatele (x,y) intr-o
   imagine XPM aflata in memorie. Culoarea va fi data de
   numarul acesteia din tabela de culori a structurii XPM */

void putXPMpixel ( XPM *imagine, unsigned int x, unsigned int y, unsigned int colorindex )
{

	imagine->data[y][x] = colorindex;

}

/* setXPMcolor asociaza unui element din tabela de culori
   ("*colta" in structura XPM) elementele r,g,b precum si
   sirul de caractere asociat culorii */

void setXPMColor ( XPM *imagine, unsigned int index, unsigned char r, unsigned char g, unsigned char b, char *charpattern )
{

	imagine->colta[index].r = r;
	imagine->colta[index].g = g;
	imagine->colta[index].b = b;
	strcpy ( imagine->colta[index].pchars , charpattern );

}

/* writeXPMtofile scrie continutul unui element imagine -
   structura XPM in fisierul XPM identificat prin "filepath".
   Fisierul va respecta formatul XPM */

void writeXPMtofile ( XPM *imagine , char *filepath )
{

	int i, j;
	FILE *f = NULL;
	char s[4000] = "", s1[100] = "", s2[100];

	f = fopen ( filepath , "w" );

	if ( f != NULL )
	{

		strcpy ( s , "/* XPM */" );
		fprintf ( f , "%s\n" , s );

		strcpy ( s , "static char *egc[] = {" );
		fprintf ( f , "%s\n" , s );

		strcpy ( s , "" );
		strcat ( s , "/* width,height,nrcolors,charsperpixel */" );
		fprintf ( f , "%s\n" , s );

		strcpy ( s , "\"" );
		sprintf ( s1 , "%u" , imagine->width );
		strcat ( s , s1 );
		strcat ( s , " " );
		sprintf ( s1 , "%u" , imagine->height );
		strcat ( s , s1 );
		strcat ( s , " " );
		sprintf ( s1 , "%u" , imagine->ncolors );
		strcat ( s , s1 );
		strcat ( s , " " );
		sprintf ( s1 , "%u" , imagine->cpp );
		strcat ( s , s1 );
		strcat ( s , "\"," );
		fprintf ( f , "%s\n" , s );

		strcpy ( s , "/*colors #RRGGBB*/" );
		fprintf ( f , "%s\n" , s );

		for ( i = 0 ; i < imagine->ncolors ; i++ )
		{
			strcpy ( s , "\"" );
			strcat ( s , imagine->colta[i].pchars );
			strcat ( s , " c #" );
			sprintf ( s2 , "%x" , imagine->colta[i].r );

			if ( imagine->colta[i].r <= 0x0F )
			{
				strcpy ( s1 , "0" );
			}
			else
			{
				strcpy ( s1 , "" );
			}

			strcat ( s1 , s2 );

			strcat ( s , s1 );
			sprintf ( s2 , "%x" , imagine->colta[i].g );

			if ( imagine->colta[i].g <= 0x0F )
			{
				strcpy ( s1 , "0" );
			}
			else
			{
				strcpy ( s1 , "" );
			}

			strcat ( s1 , s2 );

			strcat ( s , s1 );
			sprintf ( s2 , "%x" , imagine->colta[i].b );

			if ( imagine->colta[i].b <= 0x0F )
			{
				strcpy ( s1 , "0" );
			}
			else
			{
				strcpy ( s1 , "" );
			}

			strcat ( s1 , s2 );

			strcat ( s , s1 );
			strcat ( s , "\"," );
			fprintf ( f , "%s\n" , s );
		}

		strcpy ( s , "/*pixels*/" );

		fprintf ( f , "%s\n" , s );

		for ( i = 0 ; i < imagine->height ; i++ )
		{
			strcpy ( s , "\"" );

			for ( j = 0 ; j < imagine->width ; j++ )
			{
				strcat ( s , imagine->colta[ imagine->data[i][j] ].pchars );
			}

			if ( i < imagine->height - 1 )
			{
				strcat ( s , "\"," );
			}
			else
			{
				strcat ( s , "\"" );
			}

			fprintf ( f , "%s\n" , s );
			
		}

		strcpy ( s , "};" );

		fprintf ( f , "%s" , s );

		fclose ( f );

	}
	else
	{
		printf ( "\nEroare la crearea fisierului." );
		getchar();
	}

}


/*accept point coordinates between 0 to imagewidth and 0 to imageheight*/
void XPMline(XPM *img , pp2 p , pp2 q , unsigned int color)
{

	unsigned int i, j,
	xm, xM,
	ym, yM,
	dy, dx;
	int D;


	/*
	   \6|7/
	  5 \|/ 8
	------------
	  4 /|\ 1
	   /3|2\


	yM
	/ \
	|
	|    	  /
	|    	 /
	|    	/
	\ /       ________________
	ym    xm <--------------> xM
	*/

	if (	p->x < img->width	&&
	        p->y < img->height	&&
	        q->x < img->width	&&
	        q->y < img->height      &&
	        p->x >= 0                &&
	        p->y >= 0                &&
	        q->x >= 0                &&
	        q->y >= 0 )
	{

		if ( q->x > p->x && q->y >= p->y && ( q->x - p->x ) >= ( q->y - p->y ) )  /*cazul 1*/
		{

			xm = p->x;
			xM = q->x;
			ym = p->y;
			yM = q->y;

			j = ym;
			dx = xM - xm;
			dy = yM - ym;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i < xM ; i++ )
			{
				putXPMpixel ( img , i , j , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j++;/*j->yM*/
				}
			}

			putXPMpixel ( img , xm , ym , color );

			putXPMpixel ( img , xM , yM , color );

		}

		else if ( q->x >= p->x && q->y > p->y && ( q->x - p->x ) < ( q->y - p->y ) )  /*cazul 2*/
		{

			xm = p->y;
			xM = q->y;
			ym = p->x;
			yM = q->x;

			j = ym;
			dx = xM - xm;
			dy = yM - ym;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i < xM ; i++ )
			{
				putXPMpixel ( img , j , i , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j++;/*j->yM*/
				}
			}

			putXPMpixel ( img , ym , xm , color );

			putXPMpixel ( img , yM , xM , color );

		}

		else if ( q->x < p->x && q->y > p->y && ( p->x - q->x ) < ( q->y - p->y ) )  /*cazul 3*/
		{

			xm = p->y;
			xM = q->y;
			ym = p->x;
			yM = q->x;

			j = ym;
			dx = xM - xm;
			dy = ym - yM;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i < xM ; i++ )
			{
				putXPMpixel ( img , j , i , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j--;/*j->yM ym > yM*/
				}
			}

			putXPMpixel ( img , ym , xm , color );

			putXPMpixel ( img , yM , xM , color );

		}

		else if ( q->x < p->x && q->y >= p->y && ( p->x - q->x ) >= ( q->y - p->y ) )  /*cazul 4*/
		{

			xm = p->x;
			xM = q->x;
			ym = p->y;
			yM = q->y;

			j = ym;
			dx = xm - xM;
			dy = yM - ym;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i > xM ; i-- )  /*xm > xM*/
			{
				putXPMpixel ( img , i , j , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j++;/*j->yM*/
				}
			}

			putXPMpixel ( img , xm , ym , color );

			putXPMpixel ( img , xM , yM , color );

		}

		else if ( q->x < p->x && q->y < p->y && ( p->x - q->x ) >= ( p->y - q->y ) )  /*cazul 5*/
		{

			xm = p->x;
			xM = q->x;
			ym = p->y;
			yM = q->y;

			j = ym;
			dx = xm - xM;
			dy = ym - yM;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i > xM ; i-- )  /*xm > xM*/
			{
				putXPMpixel ( img , i , j , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j--;/*j->yM , ym > yM*/
				}
			}

			putXPMpixel ( img , xm , ym , color );

			putXPMpixel ( img , xM , yM , color );

		}

		else if ( q->x <= p->x && q->y < p->y && ( p->x - q->x ) < ( p->y - q->y ) )  /*cazul 6*/
		{

			xm = p->y;
			xM = q->y;
			ym = p->x;
			yM = q->x;

			j = ym;
			dx = xm - xM;
			dy = ym - yM;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i > xM ; i-- )
			{
				putXPMpixel ( img , j , i , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j--;/*j->xM*/
				}
			}

			putXPMpixel ( img , ym , xm , color );

			putXPMpixel ( img , yM , xM , color );

		}

		else if ( q->x > p->x && q->y < p->y && ( q->x - p->x ) <= ( p->y - q->y ) )  /*cazul 7*/
		{

			xm = p->y;
			xM = q->y;
			ym = p->x;
			yM = q->x;

			j = ym;
			dx = xm - xM;
			dy = yM - ym;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i > xM ; i-- )
			{
				putXPMpixel ( img , j , i , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j++;/*j->yM*/
				}
			}

			putXPMpixel ( img , ym , xm , color );

			putXPMpixel ( img , yM , xM , color );

		}

		else if ( q->x > p->x && q->y < p->y && ( q->x - p->x ) > ( p->y - q->y ) )  /*cazul 8*/
		{

			xm = p->x;
			xM = q->x;
			ym = p->y;
			yM = q->y;

			j = ym;
			dx = xM - xm;
			dy = ym - yM;
			D = ( int ) 2 * dy - dx;

			for ( i = xm ; i < xM ; i = i + 1 )
			{
				putXPMpixel ( img , i , j , color );

				if ( D <= 0 )
				{
					D += ( int ) 2 * dy;
				}
				else
				{
					D += ( int ) 2 * ( dy - dx );
					j--;/*j->yM    ym > yM*/
				}
			}

			putXPMpixel ( img , xm , ym , color );

			putXPMpixel ( img , xM , yM , color );

		}


	}/*control daca pct-ele sunt in imagine*/

}

/* transition from y axis positive up (postscript) to
  y axis positive down (xpm) */
void XPMlines ( XPM *img , plistline2 rad , unsigned int color )
{
	plistline2 aux=rad;
	pp2 a=NULL , b=NULL;

	while ( aux != NULL )
	{
		a = newp2 ( aux->line->a->x ,
                        img->height - aux->line->a->y );
		b = newp2 ( aux->line->b->x ,
                        img->height - aux->line->b->y );
		XPMline ( img , a , b , color );
		aux = aux->next;
		freep2 ( &a );
		freep2 ( &b );
	}
}

void XPMpoly ( XPM *img , ppoly rad , unsigned int color )
{
	ppoly_it it;
	
	pp2 a=NULL , b=NULL , aux=NULL , firstpoint=NULL;
	if(rad == NULL){
		return;
	}
	it = newpoly_it(rad);
	if (it == NULL)
	{
		return;
	}

	aux=next_polyp(it);
	if(aux != NULL){
		a=newp2(aux->x , img->height - aux->y - 1);
		firstpoint=a;
		aux=next_polyp(it);
	}
	while ( 1 )
	{
		if(aux == NULL)
		{
			if(firstpoint != NULL && firstpoint != a){
				b=newp2(firstpoint->x , firstpoint->y);
				XPMline(img , a , b , color);
			}
			break;
		}
		
		b=newp2(aux->x , img->height - aux->y - 1);
		XPMline(img , a , b , color);
		if(a != firstpoint){
			freep2(&a);
		}
		a=b;
		aux=next_polyp(it);
	}
	
	freep2(&b);
	freep2(&a);
        if(firstpoint)freep2(&firstpoint);
	freepoly_it(&it);
}

void XPMpoly_fill ( XPM *img , ppoly rad , unsigned int color ){

    int the_height;
    pp2 auxp2;
    plistline2 int_linel;
    pline2 line_at_height;
    line_at_height=newline2(newp2(0,0) , newp2(0,0));

    for(the_height=0 ; the_height < img->height ; the_height++){
        setline2(line_at_height ,
                0 ,             the_height ,
                img->width ,    the_height);
        int_linel=lines_at_height_in_poly(rad , line_at_height);
        XPMlines(img , int_linel , color);
        free_line2_list(&int_linel);
    }

    freeline2(&line_at_height);
}

void XPMlines_transform ( XPM *img , plistline2 rad , pm3 tr , unsigned int color )
{
	plistline2 aux = rad;
	pline2 aux1 ;
	pp2 a = NULL , b = NULL;

        a=newp2(0,0);
        b=newp2(0,0);
        aux1 = newline2 (a , b);

        while ( aux != NULL )
	{
		transform_point2 (&a , tr , aux->line->a );
		transform_point2 (&b , tr , aux->line->b );
		setline2 (aux1 ,
                        a->x , img->height - a->y ,
                        b->x , img->height - b->y);
		XPMline ( img , aux1->a , aux1->b , color );

		aux = aux->next;
	}

        freep2(& a);
        freep2(& b);
	freeline2(& aux1);
}

void XPMpoly_l_fill(XPM *img , ppoly_l rad , unsigned int color){
    ppoly_l_it polyl_it;
    ppoly aux;

    polyl_it=newpoly_l_it(rad);
    while((aux=next_poly_l_poly(polyl_it)) != NULL){
        XPMpoly_fill(img , aux , color);
    }
}

/*
void zXPMline(XPM *img , point2 p , point2 q ,
			  double deptha , double depthb , double depthproj , double **zbuf){

	unsigned int i,j,
		xm,xM,
		ym,yM,
		dy,dx;
	int D;
	double depth;


	//
	   \6|7/
	  5 \|/ 8
	------------
	  4 /|\ 1
	   /3|2\


 yM
/ \
 |
 |		  /
 |		 /
 |		/
\ /	   ________________
 ym	xm <--------------> xM
	//

	if(	p.x < img->width	&&
		p.y < img->height	&&
		q.x < img->width	&&
		q.y < img->height ){

	if( q.x > p.x && q.y >= p.y && (q.x - p.x) >= (q.y - p.y) ){//cazul 1

		xm=p.x;
		xM=q.x;
		ym=p.y;
		yM=q.y;

		j=ym;
		dx=xM-xm;
		dy=yM-ym;
		D=(int)2*dy-dx;

		for(i=xm ; i < xM ; i++){

			depth=-2;
			updatezbuf(i , j , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , i , j , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j++;//j->yM
			}
		}

		updatezbuf(xm , ym , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , xm , ym , color);

		updatezbuf(xM , yM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , xM , yM , color);

	}

	else if( q.x >= p.x && q.y > p.y && (q.x - p.x) < (q.y - p.y) ){//cazul 2

		xm=p.y;
		xM=q.y;
		ym=p.x;
		yM=q.x;

		j=ym;
		dx=xM-xm;
		dy=yM-ym;
		D=(int)2*dy-dx;

		for(i=xm ; i < xM ; i++){

			depth=-2;
			updatezbuf(j , i , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , j , i , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j++;//j->yM
			}
		}

		updatezbuf(ym , xm , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , ym , xm , color);

		updatezbuf(yM , xM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , yM , xM , color);

	}

	else if( q.x < p.x && q.y > p.y && (p.x - q.x) < (q.y - p.y) ){//cazul 3

		xm=p.y;
		xM=q.y;
		ym=p.x;
		yM=q.x;

		j=ym;
		dx=xM-xm;
		dy=ym-yM;
		D=(int)2*dy-dx;

		for(i=xm ; i < xM ; i++){

			depth=-2;
			updatezbuf(j , i , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , j , i , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j--;//j->yM ym > yM
			}
		}

		updatezbuf(ym , xm , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , ym , xm , color);

		updatezbuf(yM , xM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , yM , xM , color);

	}

	else if( q.x < p.x && q.y >= p.y && (p.x - q.x) >= (q.y - p.y) ){//cazul 4

		xm=p.x;
		xM=q.x;
		ym=p.y;
		yM=q.y;

		j=ym;
		dx=xm-xM;
		dy=yM-ym;
		D=(int)2*dy-dx;

		for(i=xm ; i > xM ; i--){//xm > xM

			depth=-2;
			updatezbuf(i , j , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , i , j , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j++;//j->yM
			}
		}

		updatezbuf(xm , ym , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , xm , ym , color);

		updatezbuf(xM , yM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , xM , yM , color);

	}

	else if( q.x < p.x && q.y < p.y && (p.x - q.x) >= (p.y - q.y) ){//cazul 5

		xm=p.x;
		xM=q.x;
		ym=p.y;
		yM=q.y;

		j=ym;
		dx=xm-xM;
		dy=ym-yM;
		D=(int)2*dy-dx;

		for(i=xm ; i > xM ; i--){//xm > xM

			depth=-2;
			updatezbuf(i , j , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , i , j , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j--;//j->yM , ym > yM
			}
		}

		updatezbuf(xm , ym , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , xm , ym , color);

		updatezbuf(xM , yM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , xM , yM , color);

	}

	else if( q.x <= p.x && q.y < p.y && (p.x - q.x) < (p.y - q.y) ){//cazul 6

		xm=p.y;
		xM=q.y;
		ym=p.x;
		yM=q.x;

		j=ym;
		dx=xm-xM;
		dy=ym-yM;
		D=(int)2*dy-dx;

		for(i=xm ; i > xM ; i--){

			depth=-2;
			updatezbuf(j , i , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , j , i , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j--;//j->xM
			}
		}

		updatezbuf(ym , xm , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , ym , xm , color);

		updatezbuf(yM , xM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , yM , xM , color);

	}

	else if( q.x > p.x && q.y < p.y && (q.x - p.x) <= (p.y - q.y) ){//cazul 7

		xm=p.y;
		xM=q.y;
		ym=p.x;
		yM=q.x;

		j=ym;
		dx=xm-xM;
		dy=yM-ym;
		D=(int)2*dy-dx;

		for(i=xm ; i > xM ; i--){

			depth=-2;
			updatezbuf(j , i , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , j , i , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j++;//j->yM
			}
		}

		updatezbuf(ym , xm , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , ym , xm , color);

		updatezbuf(yM , xM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , yM , xM , color);

	}

	else if( q.x > p.x && q.y < p.y && (q.x - p.x) > (p.y - q.y) ){//cazul 8

		xm=p.x;
		xM=q.x;
		ym=p.y;
		yM=q.y;

		j=ym;
		dx=xM-xm;
		dy=ym-yM;
		D=(int)2*dy-dx;

		for(i=xm ; i < xM ; i=i+1){

			depth=-2;
			updatezbuf(i , j , p , q , depth , deptha , depthb , zbuf);
			//putXPMpixel(img , i , j , color);

			if(D <= 0){
				D+=(int)2*dy;
			}
			else{
				D+=(int)2*(dy-dx);
				j--;//j->yM    ym > yM
 			}
		}

		updatezbuf(xm , ym , p , q , deptha , deptha , depthb , zbuf);
		//putXPMpixel(img , xm , ym , color);

		updatezbuf(xM , yM , p , q , depthb , deptha , depthb , zbuf);
		//putXPMpixel(img , xM , yM , color);

	}


	}//control daca pct-ele sunt in imagine

}
*/

