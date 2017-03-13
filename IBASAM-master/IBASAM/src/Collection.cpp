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
#include <iostream> //for the ID of unavailable males... to remove later
#include <fstream>
#include "Collection.h"
#include "rand.h"

static unsigned CollecID = 0;

using namespace std;

//Conditions: female;parr;mature;at sea;smolt
/*static int maleparr[5] = {0,1,0,0,0};
static int femaleparr[5] = {1,1,0,0,0};
static int malesalmon[5] = {0,0,0,1,0};
static int femalesalmon[5] = {1,0,0,1,0};*/
static int parrtosmoltify[5] = {2,1,2,0,0};
static int salmontoreturn[5] = {2,0,1,1,0};
static int smolttorun[5] = {2,0,2,0,1};
static int anadromous[5] = {2,0,2,0,0};
static int matureparr[5] = {2,1,1,0,2};
static int maturesmolt[5] = {2,0,1,0,1};
static int nonmaturesalmon[5] = {2,0,0,1,0};
static int nonmatureparr[5] = {2,1,0,0,0};
static int nonmaturesmolt[5] = {2,0,0,0,1};
static int inriver[5] = {2,2,2,0,2};


/************************
 * Constructors and setup
 ************************/

Collection::Collection()
{
	CollecID_=CollecID;
	++CollecID;
}

Collection::~Collection()
{
	clear();
	redds.clear();
}

void Collection::set_collecID(unsigned collecID)
{
	CollecID_=collecID;
	if(size()>0)
		for(unsigned i=0;i<size();++i)
			at(i).set_CollecID(collecID);
}
unsigned Collection::check_nloci(double nloci)
{
	//if(nloci>30.)nloci=30.;// this is the limit when using dbitset structure
	unsigned nloci_=static_cast<unsigned>(floor(nloci));
	return nloci_;
}


void Collection::setup_collection_parameters(double *colParam)
{
	unsigned j = 0;
	/****************************
	 * 		Constants			*
	 ****************************/
	/*Size Weight relationships*/
	lwa_ = colParam[j];
	lwb_ = colParam[j+1];
	lwa_sea_ = colParam[j+2];
	lwb_sea_ = colParam[j+3];

	/* Growth in River*/
	j=j+4;
	b_allom_ = colParam[j];
	effective_density_influence_growth_ = static_cast<unsigned>( floor(colParam[j+1]));
	exponent_effective_size_ = colParam[j+2];
	temperature_influence_growth_ = static_cast<unsigned>( floor(colParam[j+3])); //default and 1 = temperature function of Forseth, 0 = no effect
	mean_percent_growth_ = colParam[j+4];
	smolt1_activity_ = colParam[j+5];
	winterLMG_activity_ = colParam[j+6];
	smoltN_activity_ = colParam[j+7];

	/*Survival in River*/
	j=j+8;
	Sp0_  = colParam[j];
	Sp1_  = colParam[j+1];
	Sp1S_ = colParam[j+2];
	Sp1M_ = colParam[j+3];
	SpnM_ = colParam[j+4];
	Spn_ = colParam[j+5];
	maxRIV_ = colParam[j+6];
	sigRIV_ = colParam[j+7];
	kappaRIV_ = colParam[j+8];
	maxSEA_ = colParam[j+9];
	sigSEA_ = colParam[j+10];
	kappaSEA_ = colParam[j+11];

	/* Growth at Sea*/
	j=j+12;
	K_ = colParam[j];
	Wmax_ = colParam[j+1];
	grilse_add_nb_days_ = colParam[j+2];

	/* Survival at Sea*/
	j=j+3;
	RickA_ = colParam[j];
	RickB_ = colParam[j+1];

	/*Reproduction*/
	j=j+2;
	Loss_Fat_Repro_ = colParam[j];
	Loss_female_Fat_Repro_Coefficient_ = colParam[j+1]; //should always be the egg mass * 1.epsilon
	Loss_parr_Fat_Repro_ = colParam[j+2];//changed this way of reducing reserves! does not make sense because parrs reproduced only once!
	Exponent_W_fert_males_ = colParam[j+3];
	Mean_number_males_ = colParam[j+4];
	Mean_number_parrs_ = colParam[j+5];
	ReproMortality_[0] = colParam[j+6];//male
	ReproMortality_[1] = colParam[j+7];//female

	/*Emergence*/
	j=j+8;
	DDEmergeMin_ = colParam[j];
	DDEmergeMax_ = colParam[j+1];
	gBH_ = colParam[j+2];
	Nmax_ = colParam[j+3];
	Wcv_emergence_ = colParam[j+4];   //HYPO: Wsd for emergence function is not function of female...
	Mean_egg_W_pop_ = colParam[j+5];//0.1;
	Min_egg_W_pop_ = colParam[j+6];//0.06;//~Jonsson et al. 1996
	Max_egg_W_pop_ = colParam[j+7];//0.2;//~Jonsson et al. 1996
	WtoWegg_a_ = colParam[j+8];//0.21;
	WtoWegg_b_ = colParam[j+9];//0.013;
	WtoWegg_c_ = colParam[j+10];//6.6;
	WtoNegg_a_ = colParam[j+11];//0.86;
	WtoNegg_b_ = colParam[j+12];//1.63;
	specific_growth_river_m_ = colParam[j+13];//106;
	specific_growth_river_sd_ = colParam[j+14];//4.4;
	Wini_ = colParam[j+15];//0.2;

	/********************************************************************************
	 * 		Phenotypic traits varying eventually under genetic influence			*
	 ********************************************************************************/
	j=j+16;
	genetic_on_  = colParam[j]>0;

	/*Fat percentage during growth*/
	gPercFm_ = colParam[j+1]; /*invlogit at phenotype/genotype expression*/
	gPercFsd_ = colParam[j+2];	/* ~conservating variance on this scale of logit*/
	gPercF_heritability_ = colParam[j+3];
	gPercF_nloci_=check_nloci( colParam[j+4]);//10;
	MaturationPercF_[0]= colParam[j+5];
	MaturationPercF_[1] = colParam[j+6];

	/* Growth in river*/
	j=j+7;
	gGm_ = colParam[j];
	gGsd_ = colParam[j+1];
	gG_heritability_ = colParam[j+2];
	gG_nloci_= check_nloci(colParam[j+3]);//10

	/* Growth at sea*/
	j=j+4;
	gG_seam_ = colParam[j];
	gG_seasd_ = colParam[j+1];
	gG_sea_heritability_ = colParam[j+2];
	gG_sea_nloci_= check_nloci(colParam[j+3]);//10

	/* Smoltification*/
	j=j+4;
	LmidS_ = colParam[j];
	gLmidS_sd_= colParam[j+1];
	gLmidS_heritability_= colParam[j+2];
	gLmidS_nloci_= check_nloci(colParam[j+3]);
	alphaS_ = colParam[j+4];
	galphaS_sd_= colParam[j+5];
	galphaS_heritability_= colParam[j+6];
	galphaS_nloci_= check_nloci(colParam[j+7]);

	/*Maturation reaction norms*/
	j=j+8;
	for(unsigned i = 0; i<4;++i)
	{
		Fmid_[i] = colParam[j+i*3];
		Fmid_sd_[i] = colParam[j+1+i*3];
		//widthF_[i] = colParam[j+2+i*3];
	}
	j=j+3+9;
	//PRMN_CV_ = colParam[j];
	PRMN_H2_ = colParam[j+1];
	PRMN_nloci_ = check_nloci(colParam[j+2]);

	/*
	 * OBSERVATION
	 */
	j=j+3;
	Repro_Success_= static_cast<unsigned>(floor(colParam[j]));
	if(Repro_Success_>0)
		memory_success_.resize(0,0);

	myassert(colParam[j+1]==25071979.);
}


/************************
 * Add new individuals
 ************************/

void Collection::add_individuals(double * gParam, Environment *Env)
{
	unsigned N = (unsigned) floor(gParam[0]);
	double Wm = gParam[1];
	double Wsd = gParam[2];
	double FemaleProb = gParam[3];
	double ParrProb = gParam[4];
	double MatureProb = gParam[5];
	double AtSeaProb = gParam[6];
	double SmoltProb = gParam[7];
	double ageRiver  = gParam[8];
	double ageSea    = gParam[9];
	double Fat_m     = gParam[10];
	double Fat_sd    = gParam[11];
	double Fat_add_fem = gParam[12];
	add_individuals(N,Env,Wm,Wsd,FemaleProb,ParrProb,MatureProb,AtSeaProb,SmoltProb,
			//0,0,
			ageRiver,ageSea,Fat_m,Fat_sd,Fat_add_fem);
}

void Collection::add_individuals(unsigned N, Environment *Env, double Wm, double Wsd,
		double FemaleProb, double ParrProb, double MatureProb, double AtSeaProb, double SmoltProb,
		double ageRiver, double ageSea,
		double Fat_m, double Fat_sd, double Fat_add_fem)
{
	double W = 0.0;
	double MatpercF = 0.0;
	double Fat = 0.0;
	bool female,parr,mature,at_sea,smolt;
	double date=Env->actual_date();
	double year=Env->actual_year();
	double ageDays,specific_growth_river;
	Genes gene;
	for(unsigned a=0;a<N;++a)
	{
		W = rnorm(Wm,Wsd,0.,true);
		Fat = rnorm(Fat_m,Fat_sd,0.,true);

		if(genetic_on_)
			gene = Genes(gPercFm_,gPercFsd_,gPercF_nloci_,gPercF_heritability_,
					 gGm_, gGsd_,gG_nloci_,gG_heritability_,
					 gG_seam_, gG_seasd_,gG_sea_nloci_,gG_sea_heritability_,
					 Fmid_[0],Fmid_sd_[0],PRMN_nloci_,PRMN_H2_,
					 Fmid_[1],Fmid_sd_[1],PRMN_nloci_,PRMN_H2_,
					 Fmid_[2],Fmid_sd_[2],PRMN_nloci_,PRMN_H2_,
					 Fmid_[3],Fmid_sd_[3],PRMN_nloci_,PRMN_H2_,
					 LmidS_,gLmidS_sd_,gLmidS_nloci_,gLmidS_heritability_,
					 alphaS_,galphaS_sd_,galphaS_nloci_,galphaS_heritability_);
		else
			gene = Genes(gPercFm_,gPercFsd_,
					 gGm_, gGsd_,
					 gG_seam_, gG_seasd_,
					 Fmid_[0],Fmid_sd_[0],
					 Fmid_[1],Fmid_sd_[1],
					 Fmid_[2],Fmid_sd_[2],
					 Fmid_[3],Fmid_sd_[3],
					 LmidS_,gLmidS_sd_,
					 alphaS_,galphaS_sd_);

		female = ( runif(0.,1.) < FemaleProb );
		parr= ( runif(0.,1.) < ParrProb );
		mature= ( runif(0.,1.) < MatureProb );
		at_sea= ( runif(0.,1.) < AtSeaProb );
		smolt= ( runif(0.,1.) < SmoltProb );
		if(smolt && parr)smolt=false;
		if(at_sea && (parr || smolt))at_sea=false;
		if(mature && smolt)mature=false;

		specific_growth_river = rnorm(specific_growth_river_m_,specific_growth_river_sd_);

		if(female) Fat+=Fat_add_fem;

		ageDays = (ageRiver + ageSea) * 365.;

		MatpercF = (female) ? MaturationPercF_[1]  : MaturationPercF_[0] ;

		if(W <= Fat) Fat = W * gPercFm_;//to make sure no individuals get a NaN length

		Salmon o(W,Fat,lwa_,lwb_,lwa_sea_,lwb_sea_,female,parr,mature,at_sea,smolt,
				b_allom_, smolt1_activity_, winterLMG_activity_,smoltN_activity_,date,year,MatpercF,
				Sp0_, Sp1_, Sp1S_, Sp1M_, SpnM_, Spn_,  RickA_,  RickB_, K_, Wmax_, gPercFm_,
				CollecID_, ageRiver,ageSea,ageDays,//motherID,fatherID,
				specific_growth_river,Wini_,gene,   //,widthF_);		//create the animal
				maxRIV_,sigRIV_,kappaRIV_,maxSEA_,sigSEA_,kappaSEA_);   //edit Julien Papaix
		push_back(o);

		/*if(motherID>0)
		{
			ofstream logfile("logEmergence.txt",ios::app);
			logfile<<o;
		}*/
	}
}

void Collection::add_juveniles(unsigned N, Environment *Env, double Wm, double Wsd,Genes *mother, Genes *father,double Wemergence)
{
	double W = 0.;
	double Wini = 0.;
	double MatpercF = 0.;
	bool female;
	double date=Env->actual_date();
	double year=Env->actual_year();
	double specific_growth_river;
	Genes gene;

	for(unsigned a=0;a<N;++a)
	{
		W = rnorm(Wm,Wsd,0.,true);
		Wini = Wemergence * W/Wm;
		gene = Genes(mother,father);
		female = ( runif(0.,1.) < 0.5 );
		specific_growth_river = rnorm(specific_growth_river_m_,specific_growth_river_sd_);
		MatpercF = (female) ? MaturationPercF_[1]  : MaturationPercF_[0] ;

		Salmon o(W,0.,lwa_,lwb_,lwa_sea_,lwb_sea_,female,true,false,false,false,
				b_allom_, smolt1_activity_, winterLMG_activity_,smoltN_activity_,date,year,MatpercF,
				Sp0_, Sp1_, Sp1S_, Sp1M_, SpnM_, Spn_,  RickA_,  RickB_, K_, Wmax_, gPercFm_,
				CollecID_, 0.,0.,0.,specific_growth_river,Wini,gene,     //create the animal
				maxRIV_,sigRIV_,kappaRIV_,maxSEA_,sigSEA_,kappaSEA_);	 //edit Julien Papaix	
		push_back(o);
	}
}


void Collection::empty()
{
	clear();
	redds.clear();
}


/********************************************
 * 			observer functions 				*
 ********************************************/

void Collection::update_memory_success_repro(Redd reddi,vector<unsigned> emergingN,double actual_year)
{
	unsigned nrowini = memory_success_.size1();
	unsigned nfather = reddi.size();
	memory_success_.resize(nrowini + nfather + 1 , 11);
	unsigned lastrow = nrowini;
	memory_success_(lastrow, 0)= (double)reddi.female.ID();
	memory_success_(lastrow, 1)= 1.;
	memory_success_(lastrow, 2)= reddi.female.AgeRiver();
	memory_success_(lastrow, 3)= reddi.female.AgeSea();
	memory_success_(lastrow, 4)= (double)reddi.dateRepro();
	memory_success_(lastrow, 5)= reddi.Neggs();
	memory_success_(lastrow, 6)= 0.;
	memory_success_(lastrow, 7)= (double)reddi.female.motherID();
	memory_success_(lastrow, 8)= (double)reddi.female.fatherID();
	memory_success_(lastrow, 9)= actual_year;
	memory_success_(lastrow, 10)= (double)reddi.female.nb_transmitted();
	unsigned totEm=0;
	for(unsigned j=0;j<nfather;++j)
	{
		lastrow++;
		memory_success_(lastrow, 0)= (double)reddi.at(j).ID();
		memory_success_(lastrow, 1)= 0.;
		memory_success_(lastrow, 2)= reddi.at(j).AgeRiver();
		memory_success_(lastrow, 3)= reddi.at(j).AgeSea();
		memory_success_(lastrow, 4)= (double)reddi.dateRepro();
		memory_success_(lastrow, 5)= reddi.Eggs_per_selected_males.at(j);
		memory_success_(lastrow, 6)= (double)emergingN.at(j);
		memory_success_(lastrow, 7)= (double)reddi.at(j).motherID();
		memory_success_(lastrow, 8)= (double)reddi.at(j).fatherID();
		memory_success_(lastrow, 9)= actual_year;
		memory_success_(lastrow, 10)= (double)reddi.at(j).nb_transmitted();
		totEm+=emergingN.at(j);
	}
	memory_success_(nrowini, 6)= totEm;
}

void Collection::restitute_memory_success(double* allinorder)
{
	unsigned k=0;
	for(unsigned i=0;i< memory_success_.size1();++i) //lignes
	{
		for(unsigned j=0;j<memory_success_.size2();++j) //columns
		{
			allinorder[k]=memory_success_(i,j);
			++k;
		}
	}
}

void Collection::empty_memory_success()
{
	memory_success_.clear();
	memory_success_.resize(0,0);
}


double Collection::effective_density()
{
	double result= 0.;
	for (unsigned i=0; i<size();++i)
		if(at(i).condition(inriver) && (! at(i).condition(anadromous)))
			result += pow(at(i).L(),exponent_effective_size_);
	myassert(result>=0.);
	return(result);

}

double Collection::effective_density_more1()
{
	double result= 0.;
	for (unsigned i=0; i<size();++i)
		if(at(i).condition(inriver) && (! at(i).condition(anadromous)) && at(i).AgeRiver()>1.)
			result += pow(at(i).L(),exponent_effective_size_);
	myassert(result>=0.);
	return(result);

}
/********************************************
 * 			growth 				*
 ********************************************/

void Collection::grow(double nb_days, Environment *Env)
{
	double OmegaS;
	switch(temperature_influence_growth_){
	case 0:
		OmegaS = mean_percent_growth_;
		break;
	case 1:
		OmegaS = Env->OmegaS(nb_days);
		break;
	default:
		OmegaS = Env->OmegaS(nb_days);
		break;
	}
	grow(nb_days,OmegaS,Env);
}

void Collection::grow(Environment *Env)
{
	double OmegaS;
	switch(temperature_influence_growth_){
	case 0:
		OmegaS = mean_percent_growth_;
		break;
	case 1:
		OmegaS = Env->OmegaS();
		break;
	default:
		OmegaS =Env->OmegaS();
		break;
	}
	grow(1.0,OmegaS,Env);
}

void Collection::grow(double nb_days,double OmegaS,Environment *Env)
{
	double effectiveDensity;
	switch(effective_density_influence_growth_){
	case 0:
		effectiveDensity = 0.;
		break;
	case 1:
		effectiveDensity = effective_density_more1();
		break;
	default:
		effectiveDensity = effective_density();
		break;
	}

	double DensEffect=Env->DensEffect(nb_days,effectiveDensity);
	double SeaInfluenceM,SeaInfluenceSd;
	for(unsigned i=0; i<size();++i)
	{
		if((! at(i).condition(anadromous)) && (! at(i).dead()))
		{
			SeaInfluenceM=Env->InfluenceDWseaM();
			SeaInfluenceSd=Env->InfluenceDWseaSd();
			at(i).growS(SeaInfluenceM,SeaInfluenceSd,OmegaS,DensEffect,nb_days);
		}
		else
			at(i).update_date(nb_days);
	}
}

void Collection::compensatory_growth(Environment *Env)
{
	double SeaInfluenceM,SeaInfluenceSd;
	double prob=0.;
	for(unsigned i=0; i<size();++i)
		if(at(i).grilse())
		{
			SeaInfluenceM=Env->InfluenceDWseaM();
			SeaInfluenceSd=Env->InfluenceDWseaSd();
			at(i).Initialize_P_survival();
			at(i).marine_growth(SeaInfluenceM,SeaInfluenceSd,grilse_add_nb_days_);
			prob=runif(0.,1.);
			at(i).check_mortality(prob,grilse_add_nb_days_);
		}

	removedead();
}


/***********************************************
 *  maturation scheduling
 ***********************************************/

void Collection::check_autumn_maturation_ocean()
{

	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(nonmaturesalmon))
			at(i).check_autumn_maturation_ocean();
	}
}

void Collection::check_spring_maturation_river()
{

	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(nonmatureparr))
			at(i).check_spring_maturation_river();

	}

}

void Collection::reinitialize_parr_maturation()
{
	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(nonmatureparr)||at(i).condition(nonmaturesmolt))
			at(i).reinitialize_maturation();
	}
}

void Collection::reinitialize_salmon_maturation()
{
	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(nonmaturesalmon))
			at(i).reinitialize_maturation();
	}
}

void Collection::stop_river_maturation()
{
	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(matureparr) || at(i).condition(maturesmolt))
			at(i).stop_maturation();
	}
	removedead();
}

/************************
 * Smoltification & migration
 ************************/
void Collection::check_smoltification()
{
	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(parrtosmoltify) )
			at(i).check_smoltification();
		at(i).prepare_winter_activity();
	}

}

void Collection::check_return()
{
	for(unsigned i=0; i<size();++i)
		if(at(i).condition(salmontoreturn))
			at(i).migration();


}

void Collection::force_smolt_run()
{
	for(unsigned i=0; i<size();++i)
	{
		if(at(i).condition(smolttorun))
			at(i).migration();
		at(i).prepare_summer_activity();//Carefull, this force smolt run should be for all
	}
}

/************************
 * Mortality
 ************************/


void Collection::mortality(double nb_days)
{
	double prob=0.;
	for(unsigned i=0; i<size();++i)
	{
		prob=runif(0.,1.);
		at(i).check_mortality(prob,nb_days);
	}
}


void Collection::removedead()
{
	erase(remove_if(begin(),end(),IsDead()),end());
}

/************************
 * New individuals
 ************************/

void Collection::add_eggs(unsigned N, unsigned Nredds, Environment * Env)
{
	if(Nredds<1 || N<1)
	{
		//do nothing
	}else{
		Genes gene;
		double Neggs = floor(N / Nredds);
		unsigned date;
		for(unsigned n = 0;n<Nredds;++n)
		{
			date = Env->daterepro(600,1);//Carefull, here so because no effect of size and age implemented so far...

			if(genetic_on_)
				gene = Genes(gPercFm_,gPercFsd_,gPercF_nloci_,gPercF_heritability_,
						 gGm_, gGsd_,gG_nloci_,gG_heritability_,
						 gG_seam_, gG_seasd_,gG_sea_nloci_,gG_sea_heritability_,
						 Fmid_[0],Fmid_sd_[0],PRMN_nloci_,PRMN_H2_,
						 Fmid_[1],Fmid_sd_[1],PRMN_nloci_,PRMN_H2_,
						 Fmid_[2],Fmid_sd_[2],PRMN_nloci_,PRMN_H2_,
						 Fmid_[3],Fmid_sd_[3],PRMN_nloci_,PRMN_H2_,
						 LmidS_,gLmidS_sd_,gLmidS_nloci_,gLmidS_heritability_,
						 alphaS_,galphaS_sd_,galphaS_nloci_,galphaS_heritability_);
			else
				gene = Genes(gPercFm_,gPercFsd_,
						 gGm_, gGsd_,
						 gG_seam_, gG_seasd_,
						 Fmid_[0],Fmid_sd_[0],
						 Fmid_[1],Fmid_sd_[1],
						 Fmid_[2],Fmid_sd_[2],
						 Fmid_[3],Fmid_sd_[3],
						 LmidS_,gLmidS_sd_,
						 alphaS_,galphaS_sd_);
			Redd reddi(gene);
			reddi.Eggs_per_selected_males.push_back(Neggs) ;
			reddi.push_back(gene);
			reddi.setup(date,Neggs,Mean_egg_W_pop_);
			redds.push_back(reddi);
		}
	}
}

void Collection::emergence(Environment * Env)//assume to be at day 90 (31st march)
{
	double Survival,Wm,gSurv,Ntot,Wsd;
	unsigned DateEmergence,i,j;
	Ntot=0.;
	vector<double> Wms;
	vector<double> Wsds;
	vector<double> Ns;
	double N;
	for(i = 0; i<redds.size(); ++i)
	{
		DateEmergence=Env->ComputeDateEvent(redds.at(i).dateRepro(),runif(DDEmergeMin_,DDEmergeMax_));
		Survival=Env->survival_redd(redds.at(i).dateRepro(),DateEmergence);
		Wm = Env->emergence_W(redds.at(i).Mean_egg_W(), DateEmergence,b_allom_);
		Wsd = Wcv_emergence_ * Wm; //see Einum, Fleming 2004 and references herein...
		for(j = 0; j<redds.at(i).size(); ++j)
		{
			N = floor((redds.at(i).Eggs_per_selected_males.at(j)) * Survival);
			Ntot += N;
			Ns.push_back(N);
		}
		Wms.push_back(Wm);
		Wsds.push_back(Wsd);
	}

	gSurv=Nmax_ / (Ntot + gBH_ * Nmax_);//relation of Beverton and Holt (1957) type for survival here.
	if(gSurv>1.)gSurv=1.;
	unsigned indm = 0;
	if(Repro_Success_>0)//record individuals that reproduced for observation
	{
		vector<unsigned> emergingN;

		for(i = 0; i<redds.size(); ++i)
		{
			emergingN.clear();
			Wm = Wms.at(i);
			myassert(Wm>0.);
			Wsd = Wsds.at(i);
			for(j = 0; j<redds.at(i).size(); ++j)
			{
				N =  floor( Ns.at(indm) * gSurv);
				add_juveniles(static_cast<unsigned>(N),Env,Wm,Wsd,&redds.at(i).female,&redds.at(i).at(j),redds.at(i).Mean_egg_W());
				emergingN.push_back(static_cast<unsigned>(N));
				indm++;
			}
			myassert(emergingN.size()==redds.at(i).size());
			update_memory_success_repro((redds.at(i)),emergingN,Env->actual_year());
		}

	}else{
		for(i = 0; i<redds.size(); ++i)
		{
			Wm = Wms.at(i);
			myassert(Wm>0.);
			Wsd = Wsds.at(i);
			for(j = 0; j<redds.at(i).size(); ++j)
			{
				N = floor( Ns.at(indm) * gSurv);
				add_juveniles(static_cast<unsigned>(N),Env,Wm,Wsd,&redds.at(i).female,&redds.at(i).at(j),redds.at(i).Mean_egg_W());
				indm++;
			}
		}
	}

	redds.clear();
}

/************************
 * Reproduction
 ************************/

void Collection::reproduce(Environment * Env)//assume to be at day 320 (16th november)
{
	vector<unsigned> males_ID;
	vector<unsigned> parrs_ID;
	double Neggs,sumWparrs,sumWmales,Male_Neggs;
	unsigned date;
	//ofstream logfile("logRepro.txt",ios::app);
	//logfile<<"Year: "<<Env->actual_year()<<endl;
// Preparation
	for (unsigned i=0; i<size();++i)	//prepare the vectors of info from individuals
	{
		if(at(i).mature() && !at(i).at_sea())
		{
			if(at(i).female())			//get reproduction dates of females, number of eggs and IDs
			{
				at(i).set_daterepro(Env->daterepro(at(i).L(),at(i).AgeSea()));
				at(i).erase_males();
				at(i).not_yet_reproduced();
			}else{
				if(! at(i).parr() && !at(i).smolt())		//get IDs males
				{
					males_ID.push_back(at(i).ID());
					at(i).not_yet_reproduced();
				}else{
					parrs_ID.push_back(at(i).ID());	//get IDs of parr/smolts males
					at(i).not_yet_reproduced();
				}
			}
		}
	}

	Collection::iterator it, femalebound;
	femalebound = partition(begin(),end(),IsReproductiveFemale());

	sort(begin(),femalebound,compareW());
	//logfile<<"Weight & ID of females in order of selection of big males"<<endl;
	for (it=begin(); it!=femalebound; ++it)
	{
	    //select males
		select_anadromous_males(&(*it),&males_ID,Mean_number_males_,Loss_Fat_Repro_);
		//logfile<<(*it).W()<<"\t"<<(*it).ID()<<endl;
	}

	sort(begin(),femalebound,compareDateRepro());
	//logfile<<"Daterepro & ID of females in order of selection of parr"<<endl;
	for (it=begin(); it!=femalebound; ++it)
	{
		Salmon *female = &(*it);
		date = female->get_daterepro();
		Neggs = female->Neggs(Mean_egg_W_pop_,Min_egg_W_pop_,Max_egg_W_pop_,WtoWegg_a_,WtoWegg_b_,WtoWegg_c_,WtoNegg_a_,WtoNegg_b_);
		female->participate_repro(Loss_female_Fat_Repro_Coefficient_);
		//logfile<<date<<"\t"<<female->ID()<<endl;
		//select parrs
		select_parr_males(female,&parrs_ID,Mean_number_parrs_,Loss_parr_Fat_Repro_);
		//create redd
		if(female->selected_parr_size() > 0 || female->selected_male_size() > 0) //is there some males for reproduction?
		{
			Redd reddi(female->genes());// create a redd with female genetic material
			sumWmales=0.;
			sumWparrs=0.;
			for(unsigned i=0; i<female->selected_male_size();++i)
			{
				Salmon* male = &(*find_if(begin(),end(),IDequal(female->get_male(i))));
				sumWmales += pow(male->W(),Exponent_W_fert_males_);
			}
			for(unsigned i=0; i<female->selected_parr_size();++i)
			{
				Salmon* male = &(*find_if(begin(),end(),IDequal(female->get_parr(i))));
				sumWmales += pow(male->W(),Exponent_W_fert_males_);
				sumWparrs += pow(male->W(),Exponent_W_fert_males_);
			}
			myassert(sumWmales>0.);
			// attribute a number of egg to each male
			for(unsigned i=0; i<female->selected_male_size();++i)
			{
				Salmon* male = &(*find_if(begin(),end(),IDequal(female->get_male(i))));
				Male_Neggs = floor( (pow(male->W(),Exponent_W_fert_males_) / sumWmales )*Neggs );
				reddi.Eggs_per_selected_males.push_back(Male_Neggs) ;
				reddi.push_back(male->genes());
			}
			// attribute a number of egg to each parr
			if(female->selected_parr_size() > 0)
				for(unsigned i=0; i<female->selected_parr_size();++i)
				{
					Salmon* parr = &(*find_if(begin(),end(),IDequal(female->get_parr(i))));
					Male_Neggs =  floor(((sumWparrs / sumWmales )*Neggs)/(female->selected_parr_size()));
					reddi.Eggs_per_selected_males.push_back(Male_Neggs) ;
					reddi.push_back(parr->genes());
				}
			reddi.setup(date,Neggs,female->EggW());
			redds.push_back(reddi);
		}//end if males for repro
	}//end of female loop
}

void Collection::post_repro_mortality()
{
	for (unsigned i=0; i<size();++i)
	{
		if(at(i).reproduced() && !at(i).parr() && !at(i).smolt())
		{
			if(runif(0.,1.)<ReproMortality_[(unsigned)at(i).female()])//sex dependent
			{
				at(i).die();
			}else{
				at(i).migration();
			}
		}
	}
	removedead();
}

void Collection::select_anadromous_males(Salmon *female, vector<unsigned> *males_ID, double mean_nb, double Loss_fat)
{
	// some storage for the proba of reproduction
	vector<unsigned> IDs_mult;
	double tot=0.;
	vector<double> weight_males;
	unsigned prob_select,i,ii,j;
	unsigned NBselect;
	double temp, minpss;

	//=========================================================
	//Get the sizes of the ones that are available at the given date to obtain the smallest one
	for(i=0; i<males_ID->size();++i)
	{
		Salmon* male = &(*find_if(begin(),end(),IDequal(males_ID->at(i))));
		if((male->check_available()))
			weight_males.push_back(male->W());
	}

	if(weight_males.size()>0)
	{
		// a random number of selected males (according to a poisson distribution)
		NBselect = static_cast<unsigned>(rpoisson(mean_nb));

		if(NBselect>0) //could there be any
		{
			if(NBselect>=weight_males.size())// is there more wish of selection than actual present males
			{
				NBselect = weight_males.size(); //then select all the available males
				for(i=0; i<males_ID->size();++i)
				{
					Salmon* male = &(*find_if(begin(),end(),IDequal(males_ID->at(i))));
					if((male->check_available()))
					{
						female->push_male(male->ID());
						// put these selected males eventually not available for later
						male->participate_repro(Loss_fat);
					}
				}
			}else{ // there is more available than selected
				// check the smallest one
				minpss = *min_element(weight_males.begin(),weight_males.end());
				myassert(minpss>0.);
				//=========================================================
				// create the vector of unsigned corresponding to the ID of males
				// with repetition corresponding to their probability of being selected
				for(i=0; i<males_ID->size();++i)
				{
					Salmon* male = &(*find_if(begin(),end(),IDequal(males_ID->at(i))));
					if((male->check_available()))
					{
						//Here use a linear ratio of Weight for proba of selection
						temp = ceil(male->W() / minpss);
						for(j=0;j<temp;++j)
							IDs_mult.push_back(male->ID());
						tot+=temp;
					}
				}
				//select these NBselect males
				ii=0;
				while(ii<NBselect)
				{
					prob_select = static_cast<unsigned>( runif(1,tot) );
					if(female->not_already_selected_male(IDs_mult[prob_select]))
					{
						female->push_male(IDs_mult[prob_select]);
						Salmon* male = &(*find_if(begin(),end(),IDequal(IDs_mult[prob_select])));
						male->participate_repro(Loss_fat);// put these selected males eventually not available for later
						++ii;
					}
				}
			}
			myassert(female->selected_male_size() == NBselect);
		}
	}else{
		//"The female could not get any big male"
	}
}


void Collection::select_parr_males(Salmon *female, vector<unsigned> *males_ID, double mean_nb, double Loss_fat)
{
	// some storage for the probability of selection
	vector<unsigned> IDs_mult;
	double tot=0.;
	vector<double> weight_males;
	unsigned prob_select,i;
	double NBselect,ii;

	// a random number of selected males
	NBselect = rpoisson(mean_nb);
	//=========================================================
	// create the vector of unsigned corresponding to the ID of males
	// with repetition corresponding to their probability of being selected
	for(i=0; i<males_ID->size();++i)
	{
		Salmon* male = &(*find_if(begin(),end(),IDequal(males_ID->at(i))));
		if((male->check_available()))
		{
			//Here, use a null hypothesis of selection for fertilization of parrs (no relation to sizes)
			IDs_mult.push_back(male->ID());
			++tot;
		}
	}

	if(NBselect>0.)
	{
		if(NBselect>=tot)
		{
			NBselect = tot;
			for(i=0; i<males_ID->size();++i)
			{
				Salmon* male = &(*find_if(begin(),end(),IDequal(males_ID->at(i))));
				if((male->check_available()))
				{
					female->push_parr(male->ID());
					male->participate_repro(Loss_fat);// put these selected males eventually not available for later
				}
			}
		}else{
			//select these NBselect males
			ii=0.;
			while(ii<NBselect)
			{
				prob_select = static_cast<unsigned>( runif(1,tot) );
				if(female->not_already_selected_parr(IDs_mult[prob_select]))//find(selected_IDs->begin(),selected_IDs->end(),IDs_mult[prob_select])==selected_IDs->end())
				{
					female->push_parr(IDs_mult[prob_select]);
					Salmon* male = &(*find_if(begin(),end(),IDequal(IDs_mult[prob_select])));
					male->participate_repro(Loss_fat);// put these selected males eventually not available for later
					++ii;
				}
			}
		}
		myassert(female->selected_parr_size() == static_cast<unsigned>(  NBselect));
	}else{
		//"The female could not get any parr male"
	}
}


/************************
 * Fishing
 ************************/

vectorSalmon Collection::fishing(double *fishParam)
{
	vectorSalmon fishedColl;
	double rate1SW = fishParam[0];
	double rateMSW = fishParam[1];
	double surv;
	for (unsigned i=0; i<size();++i)
	{
		if(at(i).condition(anadromous))
		{
			if(at(i).AgeSea()<1.5)
			{
				surv=runif(0.,1.);
				if(surv<rate1SW)
				{
					at(i).die();
					fishedColl.push_back(at(i));
				}
			}else{
				surv=runif(0.,1.);
				if(surv<rateMSW)
				{
					at(i).die();
					fishedColl.push_back(at(i));
				}
			}
		}
	}
	removedead();
	return fishedColl;
}


/************************
 * Observation
 ************************/

unsigned vectorSalmon::N()
{
	return size();
}

void vectorSalmon::observe(double * allind)
{
	unsigned ind,i,w;
	if(size()>0)
		for(i=0; i<size();++i)
		{
			ind= _N_COL * i;
			allind[ind]=at(i).L();
			allind[ind+1]=at(i).W();
			allind[ind+2]=at(i).F();
			allind[ind+3]=at(i).AgeRiver();
			allind[ind+4]=at(i).AgeSea();
			allind[ind+5]=(at(i).female() ? 1. : 0.);
			allind[ind+6]=(at(i).parr() ? 1. : 0.);
			allind[ind+7]=(at(i).mature() ? 1. : 0.);
			allind[ind+8]=(at(i).at_sea() ? 1. : 0.);
			allind[ind+9]=(at(i).smolt() ? 1. : 0.);
			allind[ind+10]=at(i).ID();
			allind[ind+11]=at(i).DW();
			allind[ind+12]=at(i).returns();
			allind[ind+13]=at(i).P_survival();
			allind[ind+14]=at(i).date();
			allind[ind+15]=at(i).year();
			allind[ind+16]=at(i).CollecID();
			allind[ind+17]=at(i).Wini();
			allind[ind+18]=at(i).SpecificGR();
			allind[ind+19]=at(i).motherID();
			allind[ind+20]=at(i).fatherID();
			allind[ind+21]=at(i).gG();
			allind[ind+22]=at(i).gG_sea();
			allind[ind+23]=at(i).gPercF();
			allind[ind+24]=at(i).pG();
			allind[ind+25]=at(i).pG_sea();
			allind[ind+26]=at(i).pPercF();
			allind[ind+27]=at(i).gSLmid();
			allind[ind+28]=at(i).galphaS();
			allind[ind+29]=at(i).pSLmid();
			allind[ind+30]=at(i).palphaS();

			for(w=0;w<4;++w)
			{
				allind[ind+31+w*2]=at(i).gFmid(w);
				allind[ind+32+w*2]=at(i).pFmid(w);
			}//last is +38
			allind[ind+39]=at(i).gNeutral();
			allind[ind+40]=at(i).motherStrat();
			allind[ind+41]=at(i).fatherStrat();
			allind[ind+42]=at(i).Nreprod_thisyear();
			allind[ind+43]=at(i).Nreprod();
		}
}

void Collection::observe_redds(double *allredds)
{
	unsigned ind;
	if(redds.size()>0)
		for(unsigned i=0; i<redds.size();++i)
		{
			ind= _N_COL_REDDS_ * i;
			allredds[ind]=redds.at(i).Neggs();
			allredds[ind+1]=redds.at(i).Mean_egg_W();
			allredds[ind+2]=static_cast<double>(redds.at(i).dateRepro());
			allredds[ind+3]=static_cast<double>(redds.at(i).female.ID());
			allredds[ind+4]=redds.at(i).female.strategy();
			allredds[ind+5]=static_cast<double>(redds.at(i).size());
			allredds[ind+6]=redds.at(i).percentStrategy(0);//stands for 0.0
			allredds[ind+7]=redds.at(i).percentStrategy(1);
			allredds[ind+8]=redds.at(i).percentStrategy(2);
			allredds[ind+9]=redds.at(i).percentStrategy(11);
			allredds[ind+10]=redds.at(i).percentStrategy(12);
			allredds[ind+11]=redds.at(i).percentStrategy(21);
			allredds[ind+12]=redds.at(i).percentStrategy(22);//stands for 2.2

		}
}

unsigned Collection::n_details_one_redd(long motherID)
{
	unsigned n=0;
	for(unsigned i=0; i<redds.size();++i)
	{
		if(redds.at(i).female.ID()==(unsigned)motherID || i==(unsigned)motherID)
		{
			n=redds.at(i).size();
			break;
		}
	}
	return n;
}

void Collection::details_one_redd(double *inforedd, long motherID)
{
	unsigned n=0;
	unsigned ind;
	for(unsigned i=0; i<redds.size();++i)
	{
		if(redds.at(i).female.ID()==(unsigned)motherID || i==(unsigned)motherID)
		{
			n=redds.at(i).size();
			for(unsigned j=0;j<n;++j)
			{
				ind= _N_COL_DETAILS_REDDS_ * j;
				inforedd[ind]=static_cast<double>(redds.at(i).at(j).ID());
				inforedd[ind+1]=redds.at(i).Eggs_per_selected_males.at(j);
				inforedd[ind+2]=redds.at(i).at(j).strategy();
			}
			break;
		}
	}
}

std::ostream& operator<<(std::ostream& os,  vector<Salmon>& c)
{
	for(unsigned i=0;i<c.size();++i)
		os<<c.at(i);
	return os;
}

std::ostream& operator<<(std::ostream& os,  Collection& c)
{
	//os<<"Collection"<<endl;
	for(unsigned i=0;i<c.size();++i)
		os<<c.at(i);
	return os;
}

