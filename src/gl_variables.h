/*
 * C header file for global variables of tabipb
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
 * Last modified by Leighton Wilson, 06/20/2016
 * Last modified by Viktor Drobot, 08/25/2020
 */

#ifndef H_GLVARS_H
#define H_GLVARS_H

#include "TABIPBstruct.h"


/*consts */
#define TABIPB_PI            3.14159265358979324
#define TABIPB_ONE_OVER_4PI  0.079577471545948
#define TABIPB_KCAL2J        4.184
#define TABIPB_BULK_COEF     2529.12179861515279 /* constant w/o temp */
#define TABIPB_UNITS_COEF    1389.3875744 /* 332.0716 * kcal2j */
#define TABIPB_PARA_TEMP     17459.5591868959 /* units_coef * 4 * pi */
#define TABIPB_UNITS_PARA    8729.779593448 /* units_coef * 2 * pi */


/*runtime constant variables */
//extern double pi, one_over_4pi, kcal2j, bulk_coef, units_coef;
extern double epsw, epsp, eps;
extern double bulk_strength, kappa2, kappa;


/*global scalar variables*/
extern int nface, nspt, natm;


/*dynamic allocated variables*/
extern int **extr_v; //[3][nspt]
extern int **extr_f; //[2][nface]
extern int **face;//[3][nface]

extern double **vert, **snrm; //[3][nspt];
extern double *tr_xyz, *tr_q; //[3]*[nface]
extern double *tr_area, *bvct, *xvct; //[nface];
extern double *atmrad, *atmchr, *chrpos; //[natm],[3][nface];

/* GMRes variables */
extern double *work, *h;


#endif /* H_GLVARS_H */
