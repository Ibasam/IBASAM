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


#ifndef GENES_H_
#define GENES_H_
#include "Genemap.h"

class Genes {
public:
	Genes();
	Genes(double gPercF_mean, double gPercF_sd,unsigned gPercF_nloci,double gPercF_heritability,
			 double gG_mean,double gG_sd,unsigned gG_nloci,double gG_heritability,
			 double gG_sea_mean,double gG_sea_sd,unsigned gG_sea_nloci,double gG_sea_heritability,
			 double gMriver_intercept_mean, double gMriver_intercept_sd,unsigned gMriver_intercept_nloci,double gMriver_intercept_heritability,
			 double gMriver_f_intercept_mean, double gMriver_f_intercept_sd,unsigned gMriver_f_intercept_nloci,double gMriver_f_intercept_heritability,
			 double gMocean_intercept_mean, double gMocean_intercept_sd,unsigned gMocean_intercept_nloci,double gMocean_intercept_heritability,
			 double gMocean_f_intercept_mean, double gMocean_f_intercept_sd,unsigned gMocean_f_intercept_nloci,double gMocean_f_intercept_heritability,
			 double gSLmid_mean, double gSLmid_sd,unsigned gSLmid_nloci,double gSLmid_heritability,
			 double gSalphaS_mean, double gSalphaS_sd,unsigned gSalphaS_nloci,double gSalphaS_heritability);
	Genes(double gPercF_mean, double gPercF_sd,
			 double gG_mean,double gG_sd,
			 double gG_sea_mean,double gG_sea_sd,
			 double gMriver_intercept_mean, double gMriver_intercept_sd,
			 double gMriver_f_intercept_mean, double gMriver_f_intercept_sd,
			 double gMocean_intercept_mean, double gMocean_intercept_sd,
			 double gMocean_f_intercept_mean, double gMocean_f_intercept_sd,
			 double gSLmid_mean, double gSLmid_sd,
			 double gSalphaS_mean, double gSalphaS_sd);

	Genes(Genes *mother, Genes *father);
	void updateID(unsigned ID);
	unsigned ID()const{return ID_;};
	double gPercF(){return invlogit(gPercF_.expression());};
	double gG(){return gG_.expression();};
	double gG_sea(){return gG_sea_.expression();};
	double gSLmid(){return gSLmid_.expression();};
	double gSalphaS(){return gSalphaS_.expression();};
	double gMocean_intercept(){return gMocean_intercept_.expression();};
	double gMocean_f_intercept(){return gMocean_f_intercept_.expression();};
	double gMriver_intercept(){return gMriver_intercept_.expression();};
	double gMriver_f_intercept(){return gMriver_f_intercept_.expression();};

	double pPercF(){return invlogit(gPercF_.phenotype());};
	double pG(){return gG_.phenotype();};
	double pG_sea(){return gG_sea_.phenotype();};
	double pSLmid(){return gSLmid_.phenotype();};
	double pSalphaS(){return gSalphaS_.phenotype();};
	double pMocean_intercept(){return gMocean_intercept_.phenotype();};
	double pMocean_f_intercept(){return gMocean_f_intercept_.phenotype();};
	double pMriver_intercept(){return gMriver_intercept_.phenotype();};
	double pMriver_f_intercept(){return gMriver_f_intercept_.phenotype();};

	double gNeutral(){return neutral_.standardized_value();};
	virtual ~Genes();
protected:
	Genemap gPercF_;
	Genemap gG_;
	Genemap gG_sea_;
	Genemap gMocean_intercept_;
	Genemap gMocean_f_intercept_;
	Genemap gMriver_intercept_;
	Genemap gMriver_f_intercept_;
	Genemap gSLmid_;
	Genemap gSalphaS_;
	Genemap neutral_;
/*info from individuals to restitute at repro*/
	unsigned ID_,motherID_,fatherID_;
	double motherStrat_,fatherStrat_;
	double age_river_,age_sea_;
	unsigned nb_transmitted_;
public:
	double AgeRiver() const{return age_river_;}
	double AgeSea() const{return age_sea_;}
	double strategy();
	unsigned motherID() const{return motherID_;};
	unsigned fatherID() const{return fatherID_;};
	double motherStrat() const{return motherStrat_;};
	double fatherStrat() const{return fatherStrat_;};
	unsigned nb_transmitted() const{return nb_transmitted_;};
	void updateGene(double age_river, double age_sea,unsigned nb_transmitted);
};



#endif /* GENES_H_ */
