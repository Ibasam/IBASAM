/*
 * 	IBASAM : Individual Based Atlantic SAlmon Model
 *
 * 	Cyril Piou, 2009-2010, part of the Salmo salar individual based model IBASAM
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  Any questions or remarks, please contact Cyril Piou at:
 *
 *  piou.cyril<at>yahoo.fr
 *
 */



#ifndef __RAND_HEADER_H__
#define __RAND_HEADER_H__

#include <vector>
void modify_seed(unsigned thread);
bool rbool();
int rbinom(double nin, double pp);
double runif(double liminf, double limsup);
unsigned long rloci(unsigned nloci);
double rnorm(double mean, double sd);
double rnorm(double mean, double sd,double lim, bool inferior);
double rnorm(double mean, double sd,double liminf, double limsup);
double rpoisson(double lambda);
double rweibull(double shape, double scale);//use Weibull for date of reproduction.
double rbeta(double aa, double bb);//for noise on redd survival
void rsort_with_index(double *x, unsigned *indx, int n);
bool norm_reaction(double X, double Xmid, double alpha);
double mean(std::vector<double> *X);
double amplitude(std::vector<double> *X);
double amplitude_p(std::vector<double> *X, double p);
double min(double a, double b);
double max(double a, double b);
double invlogit(double x);
double logit(double x);
double growW(double W, double omega, double b_allom);

class Vector_torus :public std::vector<double>
{
public:
	Vector_torus();
	~Vector_torus();
	double at_torus(unsigned i);
};

#endif
