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

#include <math.h>
#include "Genes.h"

Genes::Genes() {
}

Genes::~Genes() {
}

Genes::Genes(double gPercF_mean, double gPercF_sd,unsigned gPercF_nloci,double gPercF_heritability,
			 double gG_mean,double gG_sd,unsigned gG_nloci,double gG_heritability,
			 double gG_sea_mean,double gG_sea_sd,unsigned gG_sea_nloci,double gG_sea_heritability,
			 double gMriver_intercept_mean, double gMriver_intercept_sd,unsigned gMriver_intercept_nloci,double gMriver_intercept_heritability,
			 //double gMriver_slope_mean, double gMriver_slope_sd,unsigned gMriver_slope_nloci,double gMriver_slope_heritability,
			 double gMriver_f_intercept_mean, double gMriver_f_intercept_sd,unsigned gMriver_f_intercept_nloci,double gMriver_f_intercept_heritability,
			 //double gMriver_f_slope_mean, double gMriver_f_slope_sd,unsigned gMriver_f_slope_nloci,double gMriver_f_slope_heritability,
			 double gMocean_intercept_mean, double gMocean_intercept_sd,unsigned gMocean_intercept_nloci,double gMocean_intercept_heritability,
			 //double gMocean_slope_mean, double gMocean_slope_sd,unsigned gMocean_slope_nloci,double gMocean_slope_heritability,
			 double gMocean_f_intercept_mean, double gMocean_f_intercept_sd,unsigned gMocean_f_intercept_nloci,double gMocean_f_intercept_heritability,
			 //double gMocean_f_slope_mean, double gMocean_f_slope_sd,unsigned gMocean_f_slope_nloci,double gMocean_f_slope_heritability,
			 double gSLmid_mean, double gSLmid_sd,unsigned gSLmid_nloci,double gSLmid_heritability,
			 double gSalphaS_mean, double gSalphaS_sd,unsigned gSalphaS_nloci,double gSalphaS_heritability)

	:gPercF_(gPercF_nloci,gPercF_heritability, logit(gPercF_mean),10.*gPercF_sd),
	gG_(gG_nloci,gG_heritability, gG_mean,gG_sd),
	gG_sea_(gG_sea_nloci,gG_sea_heritability, gG_sea_mean,gG_sea_sd),
	gMocean_intercept_(gMocean_intercept_nloci,gMocean_intercept_heritability, gMocean_intercept_mean,gMocean_intercept_sd),
	//gMocean_slope_(gMocean_slope_nloci,gMocean_slope_heritability, gMocean_slope_mean,gMocean_slope_sd),
	gMocean_f_intercept_(gMocean_f_intercept_nloci,gMocean_f_intercept_heritability, gMocean_f_intercept_mean,gMocean_f_intercept_sd),
	//gMocean_f_slope_(gMocean_f_slope_nloci,gMocean_f_slope_heritability, gMocean_f_slope_mean,gMocean_f_slope_sd),
	gMriver_intercept_(gMriver_intercept_nloci,gMriver_intercept_heritability, gMriver_intercept_mean,gMriver_intercept_sd),
	//gMriver_slope_(gMriver_slope_nloci,gMriver_slope_heritability, gMriver_slope_mean,gMriver_slope_sd),
	gMriver_f_intercept_(gMriver_f_intercept_nloci,gMriver_f_intercept_heritability, gMriver_f_intercept_mean,gMriver_f_intercept_sd),
	//gMriver_f_slope_(gMriver_f_slope_nloci,gMriver_f_slope_heritability, gMriver_f_slope_mean,gMriver_f_slope_sd),
	gSLmid_(gSLmid_nloci,gSLmid_heritability, gSLmid_mean,gSLmid_sd),
	gSalphaS_(gSalphaS_nloci,gSalphaS_heritability, gSalphaS_mean,gSalphaS_sd),
	neutral_(gMriver_intercept_nloci,1.0,0.,1.0)
{
	ID_=0;
	motherID_=0;
	fatherID_=0;
	motherStrat_=0;
	fatherStrat_=0;
}

Genes::Genes(Genes *mother, Genes *father)
{
	gPercF_ = reproduction(&(mother->gPercF_),&(father->gPercF_));
	gG_ = reproduction(&(mother->gG_),&(father->gG_));
	gG_sea_ = reproduction(&(mother->gG_sea_),&(father->gG_sea_));
	gMocean_intercept_ = reproduction(&(mother->gMocean_intercept_),&(father->gMocean_intercept_));
	//gMocean_slope_ = reproduction(&(mother->gMocean_slope_),&(father->gMocean_slope_));
	gMocean_f_intercept_ = reproduction(&(mother->gMocean_f_intercept_),&(father->gMocean_f_intercept_));
	//gMocean_f_slope_ = reproduction(&(mother->gMocean_f_slope_),&(father->gMocean_f_slope_));
	gMriver_intercept_ = reproduction(&(mother->gMriver_intercept_),&(father->gMriver_intercept_));
	//gMriver_slope_ = reproduction(&(mother->gMriver_slope_),&(father->gMriver_slope_));
	gMriver_f_intercept_ = reproduction(&(mother->gMriver_f_intercept_),&(father->gMriver_f_intercept_));
	//gMriver_f_slope_ = reproduction(&(mother->gMriver_f_slope_),&(father->gMriver_f_slope_));
	gSLmid_ = reproduction(&(mother->gSLmid_),&(father->gSLmid_));
	gSalphaS_ = reproduction(&(mother->gSalphaS_),&(father->gSalphaS_));
	neutral_=reproduction(&(mother->neutral_),&(father->neutral_));
	ID_=0;
	motherID_=mother->ID();
	fatherID_=father->ID();
	motherStrat_=mother->strategy();//floor(mother->AgeSea()) + floor(mother->AgeRiver())*0.1;
	fatherStrat_=father->strategy();//floor(father->AgeSea()) + floor(father->AgeRiver())*0.1;
}

double Genes::strategy()
{
	return (floor(age_sea_) + floor(age_river_)*0.1);
}

void Genes::updateID(unsigned ID)//, unsigned motherID, unsigned fatherID)
{
	ID_=ID;
}

void Genes::updateGene(double age_river, double age_sea,unsigned nb_transmitted)
{
	age_river_=age_river;
	age_sea_=age_sea;
	nb_transmitted_= nb_transmitted;
}

Genes::Genes(double gPercF_mean, double gPercF_sd,
			 double gG_mean,double gG_sd,
			 double gG_sea_mean,double gG_sea_sd,
			 double gMriver_intercept_mean, double gMriver_intercept_sd,
			 double gMriver_f_intercept_mean, double gMriver_f_intercept_sd,
			 double gMocean_intercept_mean, double gMocean_intercept_sd,
			 double gMocean_f_intercept_mean, double gMocean_f_intercept_sd,
			 double gSLmid_mean, double gSLmid_sd,
			 double gSalphaS_mean, double gSalphaS_sd)
	:gPercF_(logit(gPercF_mean),10.*gPercF_sd),
	gG_(gG_mean,gG_sd),
	gG_sea_(gG_sea_mean,gG_sea_sd),
	gMocean_intercept_(gMocean_intercept_mean,gMocean_intercept_sd),
	gMocean_f_intercept_(gMocean_f_intercept_mean,gMocean_f_intercept_sd),
	gMriver_intercept_(gMriver_intercept_mean,gMriver_intercept_sd),
	gMriver_f_intercept_(gMriver_f_intercept_mean,gMriver_f_intercept_sd),
	gSLmid_(gSLmid_mean,gSLmid_sd),
	gSalphaS_(gSalphaS_mean,gSalphaS_sd),
	neutral_(0.,1.0)
{
	ID_=0;
	motherID_=0;
	fatherID_=0;
	motherStrat_=0;
	fatherStrat_=0;
}
