#include <math.h>
#include <stdlib.h>
#include <malloc.h>

#include "parseobj.h"

void parseobj(XPM *img , char *objname , char *vizname){

	FILE *f , *g;

	char s[500] , s1[500]  , *auxs , *tr;

	pp3 vrp , prp , uvmin , uvmax , auxp ;
	pv3 vpn , vup ;
	plistpoint3 radv=NULL , auxvert;
	char ptype=' '; /* 'o' - paralela ; 'p' - perspectiva */
	long v1 , v2 , v3;
	face *auxf;
	plistface radf=NULL;

        vrp=malloc(sizeof(struct p3));
        prp=malloc(sizeof(struct p3));
        uvmin=malloc(sizeof(struct p3));
        uvmax=malloc(sizeof(struct p3));

        vpn=malloc(sizeof(struct v3));
        vup=malloc(sizeof(struct v3));

	f=fopen(vizname , "r");


	if(f != NULL){

		while(fgets(s , 480 , f) != NULL){
			tr=Trim(s);
			auxs=strchr(tr , ' ');
			strncpy(s1 , tr , auxs - tr);
			s1[auxs-tr]='\0';

			if(strcmp(s1 , "VRP") == 0){
				vrp->x=strtod(auxs , &auxs);
				vrp->y=strtod(auxs , &auxs);
				vrp->z=strtod(auxs , NULL);
			}
			else if(strcmp(s1 , "VPN") == 0){
				vpn->x=strtod(auxs , &auxs);
				vpn->y=strtod(auxs , &auxs);
				vpn->z=strtod(auxs , NULL);
			}
			else if(strcmp(s1 , "VUP") == 0){
				vup->x=strtod(auxs , &auxs);
				vup->y=strtod(auxs , &auxs);
				vup->z=strtod(auxs , NULL);
			}
			else if(strcmp(s1 , "PRP") == 0){
				prp->x=strtod(auxs , &auxs);
				prp->y=strtod(auxs , &auxs);
				prp->z=strtod(auxs , NULL);
			}
			else if(strcmp(s1 , "UVMIN") == 0){
				uvmin->x=strtod(auxs , &auxs);
				uvmin->y=strtod(auxs , NULL);
			}
			else if(strcmp(s1 , "UVMAX") == 0){
				uvmax->x=strtod(auxs , &auxs);
				uvmax->y=strtod(auxs , NULL);
			}
			else if(strcmp(s1 , "PTYPE") == 0){
				if(strtol(auxs , NULL , 10) == 0){
					ptype='p';
				}
				else{
					ptype='o';
				}
			}
		}

		/*
		VRP    0   0   0
		VPN    0   0   1
		VUP    0   1   0
		PRP    50  0   400
		UVMIN -20 -10
		UVMAX  120 130
		PTYPE  0
		*/

		g=fopen(objname , "r");

		if(g != NULL){

			while(fgets(s , 480 , g)){
				tr=Trim(s);
				switch(tr[0]){
					case '#':
						break;
					case 'v':
						auxs=tr + 1;
                                                auxp=malloc(sizeof(struct p3));
						auxp->x=strtod(auxs , &auxs);
						auxp->y=strtod(auxs , &auxs);
						auxp->z=strtod(auxs , NULL);
						add_p3_to_list(auxp , &radv);
						break;
					case 'f':
                                                auxf=malloc(sizeof(face));
						auxs=tr + 1;
						v1=strtol(auxs , &auxs , 10);
						v2=strtol(auxs , &auxs , 10);
						v3=strtol(auxs , &auxs , 10);

						auxvert=radv;
						while(auxvert != NULL){
							if(v1 == 1){
								auxf->a=auxvert->vertex;
								auxvert=NULL;
							}
							v1=v1-1;
							if(auxvert != NULL){
								auxvert=auxvert->next;
							}
						}

						auxvert=radv;
						while(auxvert != NULL){
							if(v2 == 1){
								auxf->b=auxvert->vertex;
								auxvert=NULL;
							}
							v2=v2-1;
							if(auxvert != NULL){
								auxvert=auxvert->next;
							}
						}

						auxvert=radv;
						while(auxvert != NULL){
							if(v3 == 1){
								auxf->c=auxvert->vertex;
								auxvert=NULL;
							}
							v3=v3-1;
							if(auxvert != NULL){
								auxvert=auxvert->next;
							}
						}

						add_face_to_list(auxf , &radf);

						break;
				}
			}

			if(ptype == 'p'){
				/*afispersp(img , vrp , vpn , vup , prp , uvmin , uvmax , radf); */
			}
			else{
				/*afisparalel(img , vrp , vpn , vup , prp , uvmin , uvmax , radf);*/
			}

			if(radv != NULL){
				free_p3_list(&radv);
			}

			if(radf != NULL){
				free_face_list(&radf);
			}

			fclose(g);

		}

		fclose(f);
	}

        free(vrp);
        free(prp);
        free(uvmin);
        free(uvmax);

        free(vpn);
        free(vup);

}


