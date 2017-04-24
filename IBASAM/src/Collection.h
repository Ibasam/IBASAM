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

#ifndef __COLLECTION_HEADER_H__
#define __COLLECTION_HEADER_H__


#include <vector>
#include "Salmon.h"
#include "Environment.h"
#include "Redd.h"
#include "Genes.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>

static const unsigned _N_COL_REDDS_ = 13;
static const unsigned _N_COL_DETAILS_REDDS_ = 3;

using namespace std;
class vectorSalmon : public vector<Salmon>
{
public:
	vectorSalmon(){};
	~vectorSalmon(){};
	void observe(double * allind);
	unsigned N();
};

class Collection : public  vectorSalmon
{
public:
	Collection();
	~Collection();
	/*void setup_collection_parameters(double lwa, double lwb, double lwa_sea, double lwb_sea, double b_allom,
			double LmidS, double alphaS, double betaS,double LmidR, double alphaR, double betaR,
			double *Fmid, double *alphaF, double *betaF, double *MaturationPercF,
			double smolt1_activity, double winterLMG_activity, double PercLossFatAfterRepro );*/
	void setup_collection_parameters(double *colParam);
	void set_collecID(unsigned collecID);

	void add_individuals(double *gParam, Environment *Env);
	void add_individuals(unsigned N, Environment *Env, double Wm, double Wsd,
			double FemaleProb, double ParrProb, double MatureProb, double AtSeaProb, double SmoltProb,
			double ageRiver, double ageSea,
			double Fat_m, double Fat_sd, double Fat_add_fem);
	void add_juveniles(unsigned N, Environment *Env, double Wm, double Wsd,
			Genes *mother, Genes *father, double Wemergence);

	void add_eggs(unsigned N, unsigned Nredds, Environment * Env);

	void empty();
	double effective_density();
	double effective_density_more1();

	void grow(double nb_days,double OmegaS,Environment *Env);
	void grow(double nb_days, Environment *Env);
	void grow(Environment *Env);
	void compensatory_growth(Environment *Env);
	void check_return();
	void check_smoltification();
	void force_smolt_run();
	void stop_river_maturation();
	void reproduce(Environment * Env);
	void post_repro_mortality();
	void removedead();
	void mortality(double nb_days);//handle which of the following should be called...
	void mortality_classical(double nb_days);
	void mortality_density(double nb_days);
	void mortality_size(double nb_days);
	void mortality_density_size(double nb_days);
	void emergence(Environment * Env);
	unsigned Nredds() {return redds.size();}
	void observe_redds(double *allredds);
	vectorSalmon fishing(double *fishParam);
	unsigned n_details_one_redd(long motherID);
	void details_one_redd(double *inforedd,long motherID);

	//new scheduling of maturation:
	void reinitialize_parr_maturation();
	void check_autumn_maturation_ocean();
	void check_spring_maturation_river();
	void reinitialize_salmon_maturation();


private:
	/****************************
	 * 		Constants			*
	 ****************************/
	/*Size Weight relationships*/
	double lwa_,lwb_,lwa_sea_,lwb_sea_;

	/* Growth in River*/
	double b_allom_,exponent_effective_size_,mean_percent_growth_;
	unsigned temperature_influence_growth_; //default and 1 = temperature function of Forseth, 0 = no effect
	unsigned effective_density_influence_growth_; //default=effective density on all parrs, 1 = effective density on 1+ and more parrs, 0 = no effect
	double smolt1_activity_,smoltN_activity_,winterLMG_activity_;

	/*Survival in River*/
	double Sp0_, Sp1_, Sp1S_, Sp1M_, SpnM_, Spn_;
	double maxRIV_, sigRIV_, kappaRIV_; //edit Julien Papaix

	/* Growth at Sea*/
	double K_, Wmax_,grilse_add_nb_days_;

	/* Survival at Sea*/
	double RickA_,  RickB_;
	double	maxSEA_, sigSEA_, kappaSEA_;//edit Julien Papaix

	/*Reproduction*/
	double Loss_parr_Fat_Repro_,Loss_Fat_Repro_,Loss_female_Fat_Repro_Coefficient_;
	double Exponent_W_fert_males_;
	double Mean_number_males_,Mean_number_parrs_;
	double ReproMortality_[2];

	/*Emergence*/
	double DDEmergeMin_,DDEmergeMax_,gBH_ ,Nmax_, Wcv_emergence_;
	double Mean_egg_W_pop_,Min_egg_W_pop_,Max_egg_W_pop_,WtoWegg_a_,WtoWegg_b_,WtoWegg_c_,WtoNegg_a_,WtoNegg_b_;
	double specific_growth_river_m_,specific_growth_river_sd_,Wini_; //parameters to get the size of eggs right for female initialized as something different than a 0 parr


	/********************************************************************************
	 * 		Phenotypic traits varying eventually under genetic influence			*
	 ********************************************************************************/
	bool genetic_on_;

	/*Fat percentage during growth*/
	double gPercFm_ ,gPercFsd_ , gPercF_heritability_;
	unsigned gPercF_nloci_;
	double MaturationPercF_[2];

	/* Growth in river*/
	double gGm_ ,gGsd_, gG_heritability_;
	unsigned gG_nloci_;

	/* Growth at sea*/
	double gG_seam_,gG_seasd_,gG_sea_heritability_;
	unsigned gG_sea_nloci_;

	/* Smoltification*/
	double LmidS_,gLmidS_sd_,gLmidS_heritability_,alphaS_,galphaS_sd_,galphaS_heritability_;
	unsigned gLmidS_nloci_,galphaS_nloci_;

	/*Maturation reaction norms*/
	double Fmid_[4],Fmid_sd_[4];//,widthF_[4];PRMN_CV_,
	double PRMN_H2_;
	unsigned PRMN_nloci_;

	/*observation*/
	unsigned Repro_Success_;
	boost::numeric::ublas::matrix<double> memory_success_;
	void update_memory_success_repro(Redd reddi,vector<unsigned> emergingN,double actual_year);
public:
	void restitute_memory_success(double *allinorder);
	unsigned memory_success_size1(){return memory_success_.size1();};
	unsigned memory_success_size2(){return memory_success_.size2();};
	void empty_memory_success();


private:
	vector<Redd> redds;
	void select_anadromous_males(Salmon *female, vector<unsigned> *males_ID,
			double n_max, double Loss_fat);
	void select_parr_males(Salmon *female, vector<unsigned> *males_ID,
					double n_max, double Loss_fat);
	unsigned CollecID_;


	unsigned check_nloci(double nloci);
};

std::ostream& operator<<(std::ostream& os, Collection& c);
std::ostream& operator<<(std::ostream& os, vectorSalmon& c);

struct IsDead
{
	IsDead( ){}
	template <typename SP>
	bool operator()(const SP& a) const
	{
		return (a.dead());
	}
};

struct IsReproductiveFemale
{
	IsReproductiveFemale( ){}
	template <typename SP>
	bool operator()(const SP& a) const
	{
		return (a.female() && a.mature() && !a.at_sea());
	}
};

struct IsReproductive
{
	IsReproductive( ){}
	template <typename SP>
	bool operator()(const SP& a) const
	{
		return (a.mature() && !a.at_sea());
	}
};

struct IsReproductiveMaleParr
{
	IsReproductiveMaleParr( ){}
	template <typename SP>
	bool operator()(const SP& a) const
	{
		return (a.parr() &&  !a.female() && a.mature() && !a.at_sea());
	}
};


struct IDequal
{
	unsigned IDs_ ;
	IDequal(unsigned IDs)
		: IDs_(IDs)
	{}
	template <typename SP>
	bool operator()(const SP& a) const
	{
		return (a.ID()==IDs_);
	}
};

struct compareW
{
	template <typename SP>
	bool operator()(const SP& a, const SP& b) const
	{
		return (a.W()>b.W());
	}
};

struct compareDateRepro
{
	template <typename SP>
	bool operator()(const SP& a, const SP& b) const
	{
		return (a.get_daterepro()<b.get_daterepro());
	}
};


#endif
