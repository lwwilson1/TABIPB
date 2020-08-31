/*
 * C source file for global variables definition of tabipb
 *
 * C version authored by:
 * Jiahui Chen, Southern Methodist University, Dallas, TX
 *
 * Additional modifications and updates by:
 * Leighton Wilson, University of Michigan, Ann Arbor, MI
 *
 * Based on package originally written in FORTRAN by:
 * Weihua Geng, Southern Methodist University, Dallas, TX
 * Robery Krasny, University of Michigan, Ann Arbor, MI
 *
 * Last modified by Viktor Drobot, 08/25/2020
 */

#include "gl_variables.h"

/*runtime constant variables */
//double pi, one_over_4pi, kcal2j, bulk_coef, units_coef;
double epsw=0., epsp=0., eps=0.;
double bulk_strength=0., kappa2=0., kappa=0.;


/*global scalar variables*/
int nface=0, nspt=0, natm=0;


/*dynamic allocated variables*/
int **extr_v=NULL; //[3][nspt]
int **extr_f=NULL; //[2][nface]
int **face=NULL;//[3][nface]

double **vert=NULL, **snrm=NULL; //[3][nspt];
double *tr_xyz=NULL, *tr_q=NULL; //[3]*[nface]
double *tr_area=NULL, *bvct=NULL, *xvct=NULL; //[nface];
double *atmrad=NULL, *atmchr=NULL, *chrpos=NULL; //[natm],[3][nface];

/* GMRes variables */
double *work=NULL, *h=NULL;
