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
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Environment.h"

const double pi =  3.141593;
using namespace std;

Environment::Environment() {
	actual_date_ = 1.;
	actual_year_ = 0.;
	index_environment_=0.;
	winter_=true;
}

Environment::~Environment() {

}
void Environment::Reset(){
	actual_date_ = 0.;
	actual_year_ = 0.;
	index_environment_=0.;
	winter_=true;
}

void Environment::clean_vectors()
{
	days.erase(days.begin(),days.end());
	temperatures.erase(temperatures.begin(),temperatures.end());
	logRelativeFlows.erase(logRelativeFlows.begin(),logRelativeFlows.end());
	myassert(days.empty());
	myassert(temperatures.empty());
	myassert(logRelativeFlows.empty());
}

void Environment::load(double *daysv, double *tempv, double *logrelflowv, double *n)
{
	nb_days_=*n;
	unsigned N=(unsigned)nb_days_;
	nb_years_=floor(nb_days_/365.);
	clean_vectors();
	for(unsigned i=0;i<N;++i)
	{
		days.push_back(daysv[i]);
		temperatures.push_back(tempv[i]);
		logRelativeFlows.push_back(logrelflowv[i]);
	}

}

void Environment::load(const char* filenameEnvironment)
{
	ifstream in(filenameEnvironment); // Open for reading
	string line;
	nb_days_=0.0;
	nb_years_=0.0;
	clean_vectors();
	char * cstr, *p;
	double temp[3];
	unsigned t;
	string emptystr (" ");
	cstr = new char [emptystr.size()+1]; //to avoid warning messages

	while(getline(in, line))
	{
		cstr = new char [line.size()+1];
		strcpy (cstr, line.c_str());
		p=strtok (cstr," \t");
		t=0;
		while (p!=NULL)
		{
			temp[t]= atof(p);
			p=strtok(NULL," \t");
			++t;
		}
		days.push_back(temp[0]);
		temperatures.push_back(temp[1]);
		logRelativeFlows.push_back(temp[2]);
		++nb_days_;
		nb_years_+= ((((unsigned)nb_days_) % 365)== 0) ? 1.0 : 0.0;
	}
	delete[] cstr;
	delete[] p;

	//close file!!
	in.close();

}


void Environment::Set_InfluenceDWsea(double *mean, double *sd)
{
	InfluenceDWseaMean_= *mean;
	InfluenceDWseaSd_= *sd;
}

void Environment::setup_parameters(double *Parameters)
{
	InfluenceDWseaMean_=Parameters[0];
	InfluenceDWseaSd_=Parameters[1];
	dr_=Parameters[2];
	gr_=Parameters[3];
	Tlr_=Parameters[4];
	Tur_=Parameters[5];
	Critical_RelativeFlow_=Parameters[6];
	beta_dens_effect_=Parameters[7];
	river_size_=Parameters[8];
	r1_=Parameters[9];//0.00019346;
	r2_=Parameters[10];//5161.93;
	r3_=Parameters[11];//0.608211;
	r4_=Parameters[12];//19.055;
	beta_noise_redd_survival_=Parameters[13];
	logCritInfFlow_=Parameters[14];
	logCritSupFlow_=Parameters[15];
	beta_redd_flow_survival_=Parameters[16];

	myassert(river_size_>0.);
	myassert(beta_dens_effect_>0.);

}

double Environment::Omega(double nb_days)
{
	unsigned index_now = (unsigned)index_environment_;
	unsigned index_end = (unsigned)(index_environment_ + nb_days);
	double mTemp=0.;
	for(unsigned j=index_now;j<index_end;++j)
		mTemp+=temperatures.at_torus(j);
	mTemp/=nb_days;
	double omega=dr_*(mTemp-Tlr_)*(1-exp(gr_*(mTemp-Tur_)));
	if(omega<0.) omega=0;
	return(omega);
}

double Environment::OmegaS(double nb_days)
{
	unsigned index_now = (unsigned)index_environment_;
	unsigned index_end = (unsigned)(index_environment_ + nb_days);
	double omegaS=0.;
	double omega;
	for(unsigned j=index_now;j<index_end;++j)
	{
		omega=dr_*(temperatures.at_torus(j)-Tlr_)*(1-exp(gr_*(temperatures.at_torus(j)-Tur_)));
		if(omega<0.) omega=0;
		omegaS+=omega;
	}
	return(omegaS);
}

double Environment::OmegaSinverse(double nb_days)
{
	unsigned index_end = (unsigned)index_environment_;
	unsigned index_now = (unsigned)(index_environment_ + nb_days);
	double omegaS=0.;
	double omega;
	for(unsigned j=index_now;j<index_end;++j)
	{
		omega=dr_*(temperatures.at_torus(j)-Tlr_)*(1-exp(gr_*(temperatures.at_torus(j)-Tur_)));
		if(omega<0.) omega=0;
		omegaS+=omega;
	}
	return(- omegaS);
}

double Environment::DensEffect(double nb_days,double effective_density)
{
	double river_effective_density = effective_density / (river_size_ * 1000000); //Note: effD is in mm�, river_size is in m�
	double denseffect =1 + beta_dens_effect_ * river_effective_density * IWUH(nb_days);
	myassert(denseffect!=0.);
	denseffect = 1 /denseffect ;
	bool winter;
	if(actual_date_ + nb_days < 91.0 || actual_date_ + nb_days>273.0 )
			winter=true;
		else
			winter=false;
	denseffect = winter ? 1. : denseffect;
	myassert(denseffect>=0.);
	myassert(denseffect<=1.);
	return(denseffect);
}

double Environment::IWUH(double nb_days)
{
	myassert(nb_days>0.);
	double iwuh=0.;
	unsigned index_now = (unsigned)index_environment_;
	unsigned index_end = (unsigned)(index_environment_ + nb_days);
	for(unsigned j=index_now;j<index_end;++j)
	{
		myassert(exp(logRelativeFlows.at_torus(j))!=0);
		iwuh+=max(1.0,Critical_RelativeFlow_/exp(logRelativeFlows.at_torus(j)));
	}
	iwuh/=nb_days;
	return(iwuh);

}

double Environment::OmegaS()
{
	unsigned index_now = (unsigned)index_environment_;
	double omegaS=dr_*(temperatures.at_torus(index_now)-Tlr_)*(1-exp(gr_*(temperatures.at_torus(index_now)-Tur_)));
	return(omegaS);
}

double Environment::DensEffect(double effective_density)
{
	double river_effective_density = effective_density / (river_size_ * 1000000); //Note: effD is in mm�, river_size is in m�
	double denseffect =1 + beta_dens_effect_ * river_effective_density * IWUH();
	myassert(denseffect!=0.);
	denseffect = 1 /denseffect ;
	bool winter;
	if(actual_date_ < 91.0 || actual_date_ >273.0 )
			winter=true;
		else
			winter=false;
	denseffect = winter ? 1.0 : denseffect;
	return(denseffect);
}

double Environment::IWUH()
{
	unsigned index_now = (unsigned)index_environment_;
	myassert(exp(logRelativeFlows.at_torus(index_now))!=0.);
	double iwuh=max(1.0,Critical_RelativeFlow_/exp(logRelativeFlows.at_torus(index_now)));
	return(iwuh);
}


unsigned Environment::daterepro(double L, double ageSea)
{
	unsigned index_now = (unsigned)index_environment_;

	return index_now + static_cast<unsigned>(floor(rweibull(3.598,38.24)));// parameters of date of reproduction
}

double Environment::survival_redd(unsigned DateRepro, unsigned DateEmergence)
{
	double surv = 1.;
	if(beta_noise_redd_survival_>0.)// flow impact on survival
	{
		double nprob=0.;
		for(unsigned j=DateRepro;j<DateEmergence;++j)
		{
			surv*=r1_*(temperatures.at_torus(j)+r2_)*(1-exp(r3_*(temperatures.at_torus(j) - r4_)));
			nprob +=  ( logRelativeFlows.at_torus(j) <  logCritInfFlow_ || logRelativeFlows.at_torus(j) >  logCritSupFlow_ ) ? 1. : 0.;
		}
		nprob = fmax(1.,nprob);
		double ndays = static_cast<double>(DateEmergence-DateRepro);
		myassert(ndays>0.);
		surv*=rbeta(beta_noise_redd_survival_,beta_noise_redd_survival_*beta_redd_flow_survival_*nprob/ndays);
	}else{							//only temperature impact on survival
		for(unsigned j=DateRepro;j<DateEmergence;++j)
			surv*=r1_*(temperatures.at_torus(j)+r2_)*(1-exp(r3_*(temperatures.at_torus(j) - r4_)));
	}
	if(surv>1.) surv = 1.;
	if(surv<0.) surv = 0.;
	return surv;
}

double Environment::emergence_W(double Wegg, unsigned DateEmergence, double b_allom)
{
	double nb_days = index_environment_ - static_cast<double>(DateEmergence);
	if(nb_days>0.)
		Wegg = growW(Wegg,OmegaS(nb_days),b_allom);
	else
		Wegg = growW(Wegg,OmegaSinverse(nb_days),b_allom);

	return Wegg;
}

void Environment::increment_date(double nb_days)
{
	index_environment_+=nb_days;
	actual_date_+=nb_days;
	if(actual_date_>365.0)
	{
		actual_date_ -=365.0;
		actual_year_+=1.0;
	}
	if(actual_date_ < 91.0 || actual_date_>273.0)
		winter_=true;
	else
		winter_=false;
}

unsigned Environment::ComputeDateEvent(unsigned Date,double todoDD)
{
	while(todoDD>0)
	{
		todoDD-=temperatures.at_torus(Date);
		++Date;
	}
	return Date;
}


std::ostream& operator<<(std::ostream& os, const Environment& e)
{
	//os<<"Environment"<<endl;
	for(unsigned i=0;i<(unsigned)e.nb_days();++i)
		os<<e.days.at(i)<<"\t"<<e.logRelativeFlows.at(i)<<"\t"<<e.temperatures.at(i)<<endl;
	return os;
}
