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

#include "myassert.h"
#include <time.h>
#include <math.h>
#include <boost/random.hpp>
#include <vector>
#include <float.h>
#include "rand.h"

boost::mt19937 rng(static_cast<unsigned int> (time(0)));
boost::uniform_int<> prob(0, 8);
boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(rng, prob);
boost::uniform_real<> probr(0, 1);
boost::variate_generator<boost::mt19937&, boost::uniform_real<> > rndv(rng,
		probr);
boost::normal_distribution<> norm;
boost::variate_generator<boost::mt19937&, boost::normal_distribution<> >
		rnormal(rng, norm);
boost::bernoulli_distribution<> bern;
boost::variate_generator<boost::mt19937&, boost::bernoulli_distribution<> > rbern(rng, bern);


void modify_seed(unsigned thread)
{
	rng.seed(thread);
}

double runif(double liminf, double limsup) {
	double rnd01 = rndv();
	double dif = limsup - liminf;
	return (rnd01 * dif + liminf);
}

unsigned long rloci(unsigned nloci)
{
	unsigned long rnd01 =  static_cast<unsigned long>(floor(rndv() * pow(2.,nloci)));//random(0,1)*nombre d'arrangements
	return rnd01;//random integer between 0 and nrec  (to be transformed in bitset)
}

bool rbool(){
	//return (rndv()>0.5 ) ? true : false;
	return rbern();
}

double rnorm(double mean, double sd) {
	double rn01 = rnormal();
	return (sd * rn01 + mean);
}

double rnorm(double mean, double sd,double lim, bool inferior) {
	double rn01 = sd * rnormal() + mean;
	if(inferior)
	{
		while(rn01<lim && lim<mean)
			rn01 = sd * rnormal() + mean;
	}else{
		while(rn01>lim && lim>mean)
			rn01 = sd * rnormal() + mean;
	}
	return rn01;
}

double rnorm(double mean, double sd,double liminf ,double limsup) {
	double rn01 = sd * rnormal() + mean;
	while((rn01<liminf || rn01>limsup ) && (liminf<limsup && liminf<mean && limsup>mean))
		rn01 = sd * rnormal() + mean;
	return rn01;
}


double rpoisson(double lambda)// random number (Knuth):
{
    double L = exp(- lambda);
    double k = 0.;
    double p = 1.;
    while(p>=L)
    {
    	++k;
    	p *= rndv();
    }
    return k - 1.;
}

double rweibull(double shape, double scale)
{
	myassert(shape!=0.);
	double rw = rndv();
	while(rw == 0.)
		rw = rndv();
	return scale * pow(- log(rw),1/shape);
}

int rbinom(double nin, double pp) {
	/* Taken from the R source code */

	static double c, fm, npq, p1, p2, p3, p4, qn;
	static double xl, xll, xlr, xm, xr;

	static double psave = -1.0;
	static int nsave = -1;
	static int m;

	double f, f1, f2, u, v, w, w2, x, x1, x2, z, z2;
	double p, q, np, g, r, al, alv, amaxp, ffm, ynorm;
	int i, ix, k, n;
	ix = 0;
	bool finis = false;
	bool L_np_small = false;
	r = floor(nin + 0.5);

	if (r == 0 || pp == 0.)
		return 0;
	if (pp == 1.)
		return (int) r;

	n = int(r);

	p = fmin(pp, 1.0 - pp);
	q = 1.0 - p;
	np = n * p;
	r = p / q;
	g = r * (n + 1);

	if (pp != psave || n != nsave) {
		psave = pp;
		nsave = n;
		if (np < 30.0) {
			/* inverse cdf logic for mean less than 30 */
			qn = pow(q, (double) n);
			L_np_small = true;
		} else {
			ffm = np + p;
			m = (int) (ffm);
			fm = m;
			npq = np * q;
			p1 = (int) (2.195 * sqrt(npq) - 4.6 * q) + 0.5;
			xm = fm + 0.5;
			xl = xm - p1;
			xr = xm + p1;
			c = 0.134 + 20.5 / (15.3 + fm);
			al = (ffm - xl) / (ffm - xl * p);
			xll = al * (1.0 + 0.5 * al);
			al = (xr - ffm) / (xr * q);
			xlr = al * (1.0 + 0.5 * al);
			p2 = p1 * (1.0 + c + c);
			p3 = p2 + c / xll;
			p4 = p3 + c / xlr;
		}
	} else {
		if (n == nsave) {
			if (np < 30.0)
				L_np_small = true;
		}
	}

	/*-------------------------- np = n*p >= 30 : ------------------- */
	bool exit_ = false;
	while (!finis && !L_np_small && !exit_) {
		u = rndv() * p4;
		v = rndv();
		/* triangular region */
		if (u <= p1) {
			ix = (int) (xm - p1 * v + u);
			finis = true;
			break;
		}
		/* parallelogram region */
		if (u <= p2) {
			x = xl + (u - p1) / c;
			v = v * c + 1.0 - fabs(xm - x) / p1;
			if (v > 1.0 || v <= 0.) {
				continue;
			}
			ix = (int) x;
		} else {
			if (u > p3) { /* right tail */
				ix = (int) (xr - log(v) / xlr);
				if (ix > n) {
					continue;
				}
				v = v * (u - p3) * xlr;
			} else {/* left tail */
				ix = (int) (xl + log(v) / xll);
				if (ix < 0) {
					continue;
				}
				v = v * (u - p2) * xll;
			}
		}
		/* determine appropriate way to perform accept/reject test */
		k = abs(ix - m);
		if (k <= 20 || k >= npq / 2 - 1) {
			/* explicit evaluation */
			f = 1.0;
			if (m < ix) {
				for (i = m + 1; i <= ix; i++)
					f *= (g / i - r);
			} else {
				if (m != ix) {
					for (i = ix + 1; i <= m; i++)
						f /= (g / i - r);
				}
			}
			if (v <= f) {
				finis = true;
				break;
			}
		} else {
			/* squeezing using upper and lower bounds on log(f(x)) */
			amaxp = (k / npq) * ((k * (k / 3. + 0.625) + 0.1666666666666) / npq
					+ 0.5);
			ynorm = -k * k / (2.0 * npq);
			alv = log(v);
			if (alv < ynorm - amaxp) {
				finis = true;
				break;
			}
			if (alv <= ynorm + amaxp) {
				/* stirling's formula to machine accuracy */
				/* for the final acceptance/rejection test */
				x1 = ix + 1;
				f1 = fm + 1.0;
				z = n + 1 - fm;
				w = n - ix + 1.0;
				z2 = z * z;
				x2 = x1 * x1;
				f2 = f1 * f1;
				w2 = w * w;
				if (alv <= xm * log(f1 / x1) + (n - m + 0.5) * log(z / w) + (ix
						- m) * log(w * p / (x1 * q)) + (13860.0 - (462.0
						- (132.0 - (99.0 - 140.0 / f2) / f2) / f2) / f2) / f1
						/ 166320.0 + (13860.0 - (462.0 - (132.0 - (99.0 - 140.0
						/ z2) / z2) / z2) / z2) / z / 166320.0 + (13860.0
						- (462.0 - (132.0 - (99.0 - 140.0 / x2) / x2) / x2)
								/ x2) / x1 / 166320.0 + (13860.0 - (462.0
						- (132.0 - (99.0 - 140.0 / w2) / w2) / w2) / w2) / w
						/ 166320.) {
					finis = true;
					break;
				}
			}
		}
	}

	while (L_np_small && !finis && !exit_) {
		/*---------------------- np = n*p < 30 : ------------------------- */
		ix = 0;
		f = qn;
		u = rndv();
		while (!finis) {
			if (u < f) {
				finis = true;
				break;
			}
			if (ix > 110) {
				exit_ = true;
				break;
			}
			u -= f;
			ix++;
			f *= (g / ix - r);
		}

	}

	if (finis)
		if (psave > 0.5)
			ix = n - ix;

	return ix;
}

static int rcmp(double x, double y) {
	if (x < y)
		return -1;
	if (x > y)
		return 1;
	return 0;
}

void rsort_with_index(double *x, unsigned *indx, int n) {
	double v;
	int i, j, h, iv;

	for (h = 1; h <= n / 9; h = 3 * h + 1)
		;
	for (; h > 0; h /= 3)
		for (i = h; i < n; i++) {
			v = x[i];
			iv = indx[i];
			j = i;
			while (j >= h && rcmp(x[j - h], v) > 0) {
				x[j] = x[j - h];
				indx[j] = indx[j - h];
				j -= h;
			}
			x[j] = v;
			indx[j] = iv;
		}
}
double invlogit(double x) {
	return (1. / (1. + exp(-x)));
}

double logit(double x) {
	myassert(x<1. && x>0.);
	return log(x / (1. -x));
}


bool norm_reaction(double X, double Xmid, double alpha) {
	double proba = invlogit(alpha * (X - Xmid));
	return (proba > runif(0.0, 1.0));
}

bool prob_norm_reaction(double X, double Xmid, double width)
{
	double proba = invlogit((X-Xmid)/width);
	return (proba > runif(0.0, 1.0));
}

double mean(std::vector<double> *X) {
	double result = 0.;
	for (unsigned i = 0; i < X->size(); ++i)
		result += X->at(i);
	if (X->size() > 0)
		return (result / X->size());
	else
		return (result);
}
double amplitude(std::vector<double> *X) {
	double lowest = X->at(0);
	double highest = X->at(0);
	for (unsigned i = 0; i < X->size(); ++i) {
		lowest = (X->at(i) < lowest) ? X->at(i) : lowest;
		highest = (X->at(i) > highest) ? X->at(i) : highest;
	}
	return (highest - lowest);
}

double amplitude_p(std::vector<double> *X, double p) {
	double n = (double) X->size();
	double probs[2], index[2], lo[2], hi[2], h[2], qs[2];
	if (p == 0.0)
		p = 0.5;
	probs[0] = 0.5 - p / 2.0;
	probs[1] = 0.5 + p / 2.0;
	std::vector<double> x = *X;
	sort(x.begin(), x.end());
	for (unsigned j = 0; j < 2; ++j) {
		index[j] = 1 + (n - 1) * probs[j];
		lo[j] = std::floor(index[j]);
		hi[j] = std::ceil(index[j]);
		qs[j] = x[(unsigned) lo[j]];
		h[j] = index[j] - lo[j];
		qs[j] = (1 - h[j]) * qs[j] + h[j] * x[(unsigned) hi[j]];
	}
	return (qs[1] - qs[0]);
}

double min(double a, double b)
{
  if (a < b)
	return(a);
  else
	return(b);
}

double max(double a, double b)
{
  if (a > b)
	return(a);
  else
	return(b);
}

#define expmax	(DBL_MAX_EXP * M_LN2)/* = log(DBL_MAX) */

double rbeta(double aa, double bb)
{

	/* From R sources
	 *
	 * Reference:
	 * R. C. H. Cheng (1978).
	 * Generating beta variates with nonintegral shape parameters.
	 * Communications of the ACM 21, 317-322.
	 * (Algorithms BB and BC)
	 */

	double a, b, alpha;
    double r, s, t, u1, u2, v, w, y, z;

    int qsame;
    /* FIXME:  Keep Globals (properly) for threading */
    /* Uses these GLOBALS to save time when many rv's are generated : */
    static double beta, gamma, delta, k1, k2;
    static double olda = -1.0;
    static double oldb = -1.0;

    /*if (aa <= 0. || bb <= 0. || (!R_FINITE(aa) && !R_FINITE(bb)))
	ML_ERR_return_NAN;

    if (!R_FINITE(aa))
    	return 1.0;

    if (!R_FINITE(bb))
    	return 0.0;*/
    myassert(aa>0. && bb>0.);

    /* Test if we need new "initializing" */
    qsame = (olda == aa) && (oldb == bb);
    if (!qsame) { olda = aa; oldb = bb; }

    a = fmin(aa, bb);
    b = fmax(aa, bb); /* a <= b */
    alpha = a + b;

#define v_w_from__u1_bet(AA)			\
	    v = beta * log(u1 / (1.0 - u1));	\
	    if (v <= expmax)			\
		w = AA * exp(v);		\
	    else				\
		w = DBL_MAX


    if (a <= 1.0) {	/* --- Algorithm BC --- */

	/* changed notation, now also a <= b (was reversed) */

	if (!qsame) { /* initialize */
	    beta = 1.0 / a;
	    delta = 1.0 + b - a;
	    k1 = delta * (0.0138889 + 0.0416667 * a) / (b * beta - 0.777778);
	    k2 = 0.25 + (0.5 + 0.25 / delta) * a;
	}
	/* FIXME: "do { } while()", but not trivially because of "continue"s:*/
	for(;;) {
	    u1 = rndv();
	    u2 = rndv();
	    if (u1 < 0.5) {
		y = u1 * u2;
		z = u1 * y;
		if (0.25 * u2 + z - y >= k1)
		    continue;
	    } else {
		z = u1 * u1 * u2;
		if (z <= 0.25) {
		    v_w_from__u1_bet(b);
		    break;
		}
		if (z >= k2)
		    continue;
	    }

	    v_w_from__u1_bet(b);

	    if (alpha * (log(alpha / (a + w)) + v) - 1.3862944 >= log(z))
		break;
	}
	return (aa == a) ? a / (a + w) : w / (a + w);

    }
    else {		/* Algorithm BB */

	if (!qsame) { /* initialize */
	    beta = sqrt((alpha - 2.0) / (2.0 * a * b - alpha));
	    gamma = a + 1.0 / beta;
	}
	do {
	    u1 = rndv();
	    u2 = rndv();

	    v_w_from__u1_bet(a);

	    z = u1 * u1 * u2;
	    r = gamma * v - 1.3862944;
	    s = a + r - w;
	    if (s + 2.609438 >= 5.0 * z)
		break;
	    t = log(z);
	    if (s > t)
		break;
	}
	while (r + alpha * log(alpha / (b + w)) < t);

	return (aa != a) ? b / (b + w) : w / (b + w);
    }
}

double growW(double W, double omega, double b_allom)
{
	myassert(b_allom!=0.);
	return pow( pow(W,b_allom) +  b_allom * omega / 100 , 1/ b_allom);
}

//////////////////////////////////////////////
//			Vector_torus sources            //
//////////////////////////////////////////////

Vector_torus::Vector_torus() {
}

Vector_torus::~Vector_torus() {
}

double Vector_torus::at_torus(unsigned i){
	if(i>=size())
		i-=size()*static_cast<unsigned>(floor(double(i) / double(size())));

	return(at(i));
}

