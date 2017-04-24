/*
 * 	IBASAM : Individual Based Atlantic SAlmon Model
 *
 * 	Cyril Piou, 2009-2010, part of the Salmo salar individual based model IBASAM
 *  and Julien Papaix 2015
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
#include <math.h>
#include <iostream>
#include "Salmon.h"
#include "rand.h"

using namespace std;

static unsigned IDs = 0;

Salmon::Salmon(double W, double F, double lwa, double lwb,double lwa_sea, double lwb_sea,
		bool female, bool parr,  bool mature, bool at_sea,  bool smolt,
		double b_allom, double smolt1_activity, double winterLMG_activity, double smoltN_activity,
		double date, double year, double MaturationPercF,
		double Sp0,double Sp1,double Sp1S,double Sp1M,double SpnM,double Spn,
		double RickA, double RickB,double K, double Wmax, double popPercF,
		unsigned CollecID, double ageRiver, double ageSea, double ageDays,
		double specific_growth_river, double Wini,
		Genes genes, 
		double maxRIV, double sigRIV, double kappaRIV,//edit Julien Papaix 
		double maxSEA, double sigSEA, double kappaSEA)//edit Julien Papaix
{
	myGenes_=genes;
	gPercF_ = myGenes_.gPercF();//here already the invlogit value --> percentage
	gG_= myGenes_.gG();//here the raw value --> (-oo +oo) -->need exp for [0 +oo)
	gG_sea_=myGenes_.gG_sea();//undo the 'edit Julien Papaix to have only one genetic growth effect' because it is not called for pG_sea anyway if tradeoff is on
	gSLmid_=myGenes_.gSLmid();
	galphaS_=myGenes_.gSalphaS();
	gFmid_[0]=myGenes_.gMriver_intercept();
	gFmid_[1]=myGenes_.gMriver_f_intercept();
	gFmid_[2]=myGenes_.gMocean_intercept();
	gFmid_[3]=myGenes_.gMocean_f_intercept();
	pPercF_ = myGenes_.pPercF();//here already the invlogit value --> percentage
	pG_= myGenes_.pG();//here the raw value --> (-oo +oo) -->need exp for [0 +oo)
	pG_sea_=myGenes_.pG_sea();//undo the 'edit Julien Papaix to have only one genetic growth effect but a different pG_ to pG_sea_' because it is going to be changed below if tradeoff is on
	pSLmid_=myGenes_.pSLmid();
	palphaS_=myGenes_.pSalphaS();
	pFmid_[0]=myGenes_.pMriver_intercept();
	pFmid_[1]=myGenes_.pMriver_f_intercept();
	pFmid_[2]=myGenes_.pMocean_intercept();
	pFmid_[3]=myGenes_.pMocean_f_intercept();
	lwa_=lwa;
	lwb_=lwb;
	lwa_sea_=lwa_sea;
	lwb_sea_=lwb_sea;
	double a_,b_;
	if(ageSea>0. || smolt || at_sea)
	{
		a_=lwa_sea_;
		b_=lwb_sea_;
	}else{
		a_=lwa_;
		b_=lwb_;
	}
	W_ = W;
	W0_ = W;
	mPercF_ = pPercF_ + MaturationPercF;
	aPercF_ = (mature)? mPercF_ : pPercF_;
	popPercF_ = popPercF;
	myassert(popPercF_<1. && popPercF_>0.);
	F_ = F;
	F_maturing_memory_=F;
	DW_ = 0.0;
	myassert(W_>F_);
	L_ = exp(a_ + b_ * log(W_ - F_) );
	L0_=L_;
	Wini_=Wini;
	myassert(Wini_>0.);
	Lini_= exp(lwa_ + lwb_ * log(Wini_) );
	myassert(Lini_>0.);
	b_allom_=b_allom;
	myassert(b_allom_!=0.);
	//edit Julien Papaix, parameters and computation of individual penalty for 
	//survival depending on growth capacity pG_ and pG_sea_:
	
	//river tradeoff:
	if(maxRIV>0.)
	{
		maxRIV_=maxRIV; 
		sigRIV_=sigRIV; 
		kappaRIV_=kappaRIV; 
		pGres_=exp(pG_)/maxRIV_;
		if(pGres_>1.)
		{
			pGres_=1.;
		}
		coefSURV_=(exp(-kappaRIV_*pow(pGres_,sigRIV_))-exp(-kappaRIV_))/(1.-exp(-kappaRIV_));
	}else{
		maxRIV_=maxRIV; 
		sigRIV_=sigRIV; 
		kappaRIV_=kappaRIV; 
		pGres_=0;
		coefSURV_=1.;
	}
	myassert(coefSURV_>0. && coefSURV_<=1.);
	
	//Sea tradeoff:
	if(maxSEA>0.){
		pG_sea_=myGenes_.pG();//when the tradeoff is touching sea survival, the genetic growth capacity at sea is supposed to be entirely correlated to the river one.
		maxSEA_=maxSEA; 
		sigSEA_=sigSEA; 
		kappaSEA_=kappaSEA; 
		pG_seares_=(exp(pG_sea_))/maxSEA_;
		if(pG_seares_>1.) 
		{
			pG_seares_=1.;
		}
		coefSURVsea_=(exp(-kappaSEA_*pow(pG_seares_,sigSEA_))-exp(-kappaSEA_))/(1.-exp(-kappaSEA_));
	}else{
		maxSEA_=maxSEA; 
		sigSEA_=sigSEA; 
		kappaSEA_=kappaSEA; 
		pG_seares_=0.;
		coefSURVsea_=1.;
	}
	myassert(coefSURVsea_>0. && coefSURVsea_<=1.); 
	//end edit Julien Papaix
	
	IDs++;
	ID_ = IDs;
	myGenes_.updateID(ID_);//,motherID,fatherID);
	CollecID_=CollecID;
	age_river_=ageRiver;
	age_sea_=ageSea;
	age_days_=ageDays;
	date_=date;
	year_=year;
	female_ = female;
	parr_ = parr;
	mature_ = mature;
	at_sea_= at_sea;
	smolt_=smolt;
	P_survival_=1.;
	activity_=1.;
	smolt1_activity_=smolt1_activity;
	winterLMG_activity_= winterLMG_activity;
	smoltN_activity_=smoltN_activity;
	dead_=false;

	if(ageSea>0. && !at_sea)
		returns_=1.;
	else
		returns_=0.;

	Sp0_=Sp0;
	Sp1_=Sp1;
	Sp1S_=Sp1S;
	Sp1M_=Sp1M;
	SpnM_=SpnM;
	Spn_=Spn;
	RickA_=RickA;
	RickB_=RickB;
	K_=K;
	Wmax_=Wmax;
	specific_growth_river_=specific_growth_river;
	reproduced_=false;
	Nreprod_thisyear_=0;
	Nreprod_=0;
	Neggs_=0.;
	check_PRMN_param();
	myGenes_.updateGene(age_river_,age_sea_,Nreprod_thisyear_);

	myassert(exp(lwa_sea_)!=0.);
	myassert(exp(pG_sea_)*Wmax_>0.);
	myassert(exp(lwa_sea_)!=0.);
	myassert(lwb_sea_!=0.);

}

Salmon::~Salmon()
{
}

void Salmon::update_date(double nb_days)
{
	date_+=nb_days;
	if(date_>365.0)
	{
		date_ -=365.0;
		year_+=1.0;
	}
}

void Salmon::growS(double InfluenceSeaM,double InfluenceSeaSd, double OmegaS, double DensEffect, double nb_days) //using OmegaS (sum and not mean)
{
	age_days_+=nb_days;
	update_date(nb_days);
	if(!at_sea_)
	{
		double Wm ;
		W0_ = W_;
		W_ = pow( pow(W_,b_allom_) +  b_allom_ * OmegaS * exp(pG_) * activity_ * DensEffect/ 100 , 1/ b_allom_);
		DW_ = W_ - W0_;
		F_ = F_ + DW_ * aPercF_;
		Wm = (W_ - F_)/(1 - popPercF_);
		myassert(Wm>0.);
		if(smolt_)
			L_ = max(L_,exp(lwa_sea_ + lwb_sea_* log(Wm) ) );
		else
			L_ = max(L_,exp(lwa_ + lwb_* log(Wm) ) );

		age_river_ += nb_days/365.0;
	}else{
		W0_ = W_;
		double survm = min(1.,max(0.,1.-RickA_*pow((L_/exp(lwa_sea_)),RickB_/lwb_sea_)));
		if(survm>=0.)
		  P_survival_ = pow(survm,1./30.)*coefSURVsea_; //edit Julien Papaix
		else
			P_survival_ = 0.;
		marine_growth(InfluenceSeaM,InfluenceSeaSd,nb_days);
	}
	myGenes_.updateGene(age_river_,age_sea_,Nreprod_thisyear_);
}

void Salmon::marine_growth(double InfluenceSeaM,double InfluenceSeaSd,double nb_days)
{
	double Wm, survm=0.;
	for(double d=0.;d<nb_days;++d)
	{
		myassert(W_>0.);
		DW_ =  K_ * W_ * log(exp(pG_sea_)*Wmax_/W_) * rnorm(InfluenceSeaM,InfluenceSeaSd);//marine conditions effects
		W_ = W_ + DW_;
		F_ = F_ + DW_ * aPercF_;
		Wm = (W_ - F_)/(1 - popPercF_);
		myassert(Wm>0.);
		L_ = max(L_,exp(lwa_sea_ + lwb_sea_* log(Wm) ) );
		survm = min(1.,max(0.,1.-RickA_*pow((L_/exp(lwa_sea_)),RickB_/lwb_sea_))); //mortality L dependent!
		if(d>1.)
		{
			if(survm>=0.)
				P_survival_ *= pow(survm,1./30.)*coefSURVsea_; //edit Julien Papaix
			else
			{
				P_survival_ = 0.;
				break;
			}
		}
	}
	myassert(P_survival_<1.);
	age_sea_ += nb_days/365.0;
}

void Salmon::Initialize_P_survival()
{
	double survm = min(1.,max(0.,1.-RickA_*pow((L_/exp(lwa_sea_)),RickB_/lwb_sea_)));
	if(survm>=0.)
		P_survival_ = pow(survm,1./30.)*coefSURVsea_;//edit Julien Papaix
	else
		P_survival_ = 0.;
}

void Salmon::check_PRMN_param()
{
	if(at_sea_)
	{
		if(female_)
		{
			Fmid_=pFmid_[3];
		}else{
			Fmid_=pFmid_[2];
		}
	}else{
		if(female_)
		{
			Fmid_=pFmid_[1];
		}else{
			Fmid_=pFmid_[0];
		}
	}
}

/*******************************************
 * 			Maturation
 * ****************************************/
double Salmon::projectionF(double nDaysWindows, double nDaysProjection)
{
	myassert(nDaysWindows>0.);
	double realizedFgrowthRate = (F_ - F_maturing_memory_)/nDaysWindows;
	return(F_ + nDaysProjection * realizedFgrowthRate);
}

void Salmon::check_autumn_maturation_ocean()
{
	double projectedFmaturing = projectionF(47.,135.);
	if(projectedFmaturing>=Fmid_)
	{
		mature_=true;
		aPercF_=mPercF_;
	}else{
		reinitialize_maturation();
	}
}

void Salmon::check_spring_maturation_river()
{
	double projectedFmaturing = projectionF(61.,122.);
	if(projectedFmaturing>=Fmid_)
	{
		mature_=true;
		aPercF_=mPercF_;
		W0_ = (W_ - F_)/(1 - popPercF_);
		myassert(W0_>0.);
		L_ = max(L0_,exp(lwa_ + lwb_* log(W0_) ) );
	}else{
		reinitialize_maturation();
	}
}

void Salmon::reinitialize_maturation()
{
		F_maturing_memory_ = F_;
		L0_=L_;
}

void Salmon::stop_maturation()
{
	if(F_<= 0.)
		dead_=true;
	else
	{
		mature_=false;
		aPercF_=pPercF_;
	}
}

/**********************************
 *		Smoltification
 * *********************************/


void Salmon::check_smoltification()
{
	if(norm_reaction(L_, pSLmid_, palphaS_) )
	{
		smolt_=true;
		parr_=false;
		aPercF_=(mature_)? (mPercF_ - pPercF_): 0.;
	}
}

void Salmon::prepare_winter_activity()
{
	if(!at_sea_)
	{
		if( smolt_)
		{
			if(age_river_<1.0)
				activity_= smolt1_activity_;
			else
				activity_=smoltN_activity_;
		}
		else
		{
				activity_=winterLMG_activity_;
		}
	}
}

void Salmon::prepare_summer_activity()
{
		activity_=1.;
}

void Salmon::migration() //suppose an upstream verification of decision to migrate...
{
	if(!at_sea_)
	{
		at_sea_=true;
		if(smolt_)
		{
			myassert(L_>0.);
			smolt_=false;
			aPercF_=pPercF_;
			specific_growth_river_ = ((log(L_) - log(Lini_))/age_river_) * 100.; //Jonsson et al. 1996
			check_PRMN_param();
		}
		if(mature_)
			mature_=false;
	}
	else
	{
		at_sea_=false;
		activity_=0.;
		returns_+=1.;
	}

}



void Salmon::check_mortality(double rnd, double nb_days)
{
	if(at_sea_)
	{
		//nothing to do, everything is calculated in the growth functions
	}else{
		if(returns_<1.)
		{
			if(age_days_<=365.)
			{
				if(age_days_<=183.) //first summer
				{
					P_survival_=pow(Sp0_*coefSURV_,nb_days); //edit Julien Papaix
				}else{				//first winter
					if(mature_ || reproduced_)
						P_survival_=pow(Sp1M_*coefSURV_,nb_days); //edit Julien Papaix
					else
					{
						if(smolt_)
							P_survival_=pow(Sp1S_*coefSURV_,nb_days); //edit Julien Papaix
						else
							P_survival_=pow(Sp1_*coefSURV_,nb_days); //edit Julien Papaix
					}
				}
			}else{
				if(date_<=273. && date_>90.)//summer
					P_survival_=Spn_;
				else						//winter
					P_survival_=(mature_ || reproduced_)? SpnM_ : Spn_;

				P_survival_=pow(P_survival_*coefSURV_,nb_days); //edit Julien Papaix
			}
		}else{
			P_survival_=1.;//->>anadromous fish do not die here
		}
	}
	if(rnd>P_survival_)
		dead_=true;
}


double Salmon::Neggs(double Mean_egg_W_pop,double Min_egg_W_pop,double Max_egg_W_pop,
						double WtoWegg_a, double WtoWegg_b, double WtoWegg_c,
						double WtoNegg_a, double WtoNegg_b)
{
	//Mean_egg_W_ = max( Min_egg_W_pop, min( Max_egg_W_pop, exp( WtoWegg_a*log(W_) - WtoWegg_b * specific_growth_river_ + WtoWegg_c)/10000. ) );   //Jonsson et al 1996
	Mean_egg_W_ = max( Min_egg_W_pop, min( Max_egg_W_pop, exp( WtoWegg_a*log(W_)  + WtoWegg_c)/10000. ) );   //Jonsson et al 1996
	myassert(W_>0.);
	double potential_Neggs = exp(WtoNegg_a * log(W_) + WtoNegg_b); //Jonsson et al 1996
	//double WeggsTot= potential_Neggs * Mean_egg_W_pop;  //Jonsson et al. 1996
	Neggs_ = floor(potential_Neggs);//floor(WeggsTot / Mean_egg_W_);
	return Neggs_;
}

void Salmon::participate_repro(double Loss_Fat)
{
// reduce fats so that afterward not available for following reproduction event for males and reduce weight of females
	double oldF_=F_;
	if(female_)
		Loss_Fat = mass_repro()*Loss_Fat;
	F_=F_- Loss_Fat;
	if(F_<0.)
		F_=0.;
	W_ = W_ - (oldF_ - F_);
	reproduced_=true;
	Nreprod_thisyear_ += 1;
	Nreprod_ += 1;
	myGenes_.updateGene(age_river_,age_sea_,Nreprod_thisyear_);
}

bool Salmon::check_available()
{
	return (F_>0.) && !dead_;
}

bool Salmon::condition(int *conditions)
{
	bool result = (conditions[0]==(female_? 1 : 0) || conditions[0]==2);
	result = result && (conditions[1]==(parr_? 1 : 0) || conditions[1]==2);
	result = result && (conditions[2]==(mature_? 1 : 0) || conditions[2]==2);
	result = result && (conditions[3]==(at_sea_? 1 : 0) || conditions[3]==2);
	result = result && (conditions[4]==(smolt_? 1 : 0) || conditions[4]==2);
	result = result && (! dead_);
	return result ;
}

double* Salmon::all_info()
{

	all_info_[0]=L();
	all_info_[1]=W();
	all_info_[2]=F();
	all_info_[3]=AgeRiver();
	all_info_[4]=AgeSea();
	all_info_[5]=(female() ? 1. : 0.);
	all_info_[6]=(parr() ? 1. : 0.);
	all_info_[7]=(mature() ? 1. : 0.);
	all_info_[8]=(at_sea() ? 1. : 0.);
	all_info_[9]=(smolt() ? 1. : 0.);
	all_info_[10]=ID();
	all_info_[11]=DW();
	all_info_[12]=returns();
	all_info_[13]=P_survival();
	all_info_[14]=date();
	all_info_[15]=year();
	all_info_[16]=CollecID();
	all_info_[17]=Wini();
	all_info_[18]=SpecificGR();
	all_info_[19]=motherID();
	all_info_[20]=fatherID();
	all_info_[21]=gG();
	all_info_[22]=gG_sea();
	all_info_[23]=gPercF();
	all_info_[24]=pG();
	all_info_[25]=pG_sea();
	all_info_[26]=pPercF();
	all_info_[27]=gSLmid();
	all_info_[28]=galphaS();
	all_info_[29]=pSLmid();
	all_info_[30]=palphaS();

	for(unsigned w=0;w<4;++w)
	{
		all_info_[31+w*2]=gFmid(w);
		all_info_[32+w*2]=pFmid(w);
	}//last is +38
	all_info_[39]=gNeutral();
	all_info_[40]=motherStrat();
	all_info_[41]=fatherStrat();
	all_info_[42]=Nreprod_thisyear();
	all_info_[43]=Nreprod();
	return all_info_;
}

std::ostream& operator<<(std::ostream& os, Salmon& a)
{
	os << a.L() << '\t';
	os << a.W() << '\t';
	os << a.F() << '\t';
	os << a.AgeRiver() << '\t';
	os << a.AgeSea() << '\t';
	os << a.female() << '\t';
	os << a.parr() << '\t';
	os << a.mature() << '\t';
	os << a.at_sea() << '\t';
	os << a.smolt() << '\t';
	os << a.ID() << '\t';
	os << a.DW() << '\t';
	os << a.returns() << '\t';
	os << a.P_survival() << '\t';
	os << a.date() << '\t';
	os << a.year() << '\t';
	os << a.CollecID() << '\t';
	os << a.Wini()<< '\t';
	os << a.SpecificGR()<< '\t';
	os << a.motherID()<< '\t';
	os << a.fatherID()<< '\t';
	os << a.gG()<< '\t';
	os << a.gG_sea()<< '\t';
	os << a.gPercF()<< '\t';
	os << a.pG()<< '\t';
	os << a.pG_sea()<< '\t';
	os << a.pPercF()<< '\t';
	os << a.gSLmid()<< '\t';
	os << a.galphaS()<< '\t';
	os << a.pSLmid()<< '\t';
	os << a.palphaS()<< '\t';
	for(unsigned w=0;w<4;++w)
	{
		os << a.gFmid(w)<<'\t';
		os << a.pFmid(w)<<'\t';
	}//last is +38
	os << a.gNeutral()<<'\t';
	os << a.motherStrat()<<'\t';
	os << a.fatherStrat()<<'\t';
	os << a.Nreprod_thisyear()<<'\t';
	os << a.Nreprod()<<'\t';
	os << endl;
	return os;
}

