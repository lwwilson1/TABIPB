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


/*constant variables */
extern double pi, one_over_4pi, kcal2j, bulk_coef, units_coef, epsw, epsp, eps;
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
