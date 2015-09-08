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


#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "rand.h"

class Environment {
public:
	Environment();
	~Environment();
	void Reset();

	void load(const char* filenameEnvironment);
	void load(double *daysv, double *tempv, double *logrelflowv, double *n);

	double actual_date() const {return actual_date_;}
	double actual_year() const {return actual_year_;}
	void increment_date(double nb_days);

	void setup_parameters(double *Parameters);//for environment influence

	void Set_InfluenceDWsea(double *mean, double *sd);
	double Omega(double nb_days);
	double OmegaS(double nb_days);
	double OmegaSinverse(double nb_days);
	double DensEffect(double nb_days, double effectiveDensity);
	double IWUH(double nb_days);
	double OmegaS();
	double DensEffect(double effectiveDensity);
	double IWUH();
	unsigned ComputeDateEvent(unsigned DateStart,double todoDD);

	unsigned daterepro(double L, double ageSea);
	double survival_redd(unsigned DateRepro, unsigned DateEmergence);
	double emergence_W(double Wegg, unsigned DateEmergence,double b_allom);

	double nb_days()const{return nb_days_;}

	void clean_vectors();
	double InfluenceDWseaM()const{return InfluenceDWseaMean_;}
	double InfluenceDWseaSd()const{return InfluenceDWseaSd_;}
private:

//Time parameters:
	double actual_date_;
	double actual_year_;
	double index_environment_;

	double nb_years_;
	double nb_days_;


//Parameters for environment influence:
	double InfluenceDWseaMean_; // Mean influence on delta W at sea (typically 1.)
	double InfluenceDWseaSd_; //per day potential delta W at sea
	double dr_,gr_,Tlr_,Tur_; //parameters for omega in river
	double Critical_RelativeFlow_,beta_dens_effect_,river_size_;//parameters for density effect in river
	double beta_noise_redd_survival_; //switch and value of beta random noise on redd survival
	double r1_,r2_,r3_,r4_; // temperature effect on redd survival
	double logCritInfFlow_,logCritSupFlow_; //Critical flows (in log of relative) that increase mortality risk in redds
	double beta_redd_flow_survival_;  //importance of flow impact on beta noise
public:
	Vector_torus days;
	Vector_torus temperatures;
	Vector_torus logRelativeFlows;
	bool winter_;

};

std::ostream& operator<<(std::ostream& os, const Environment& e);

#endif /* ENVIRONMENT_H_ */
