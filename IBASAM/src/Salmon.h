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

#ifndef __SALMON_HEADER_H__
#define __SALMON_HEADER_H__

#include "Genes.h"
using namespace std;
static const unsigned _N_COL =44;

class Salmon
{
public:
	Salmon(double W, double F, double lwa, double lwb,double lwa_sea, double lwb_sea,
			bool female, bool parr,  bool mature, bool at_sea,  bool smolt,
			double b_allom, double smolt1_activity, double winterLMG_activity,double smoltN_activity,
			double date, double year, double MaturationPercF,
			double Sp0,double Sp1,double Sp1S,double Sp1M,double SpnM,double Spn,
			double RickA, double RickB,double K, double Wmax, double popPercF,
			unsigned CollecID, double ageRiver, double ageSea, double ageDays,
			double specific_growth_river, double Wini,
			Genes genes, 
			double maxRIV, double sigRIV, double kappaRIV, //edit Julien Papaix
			double maxSEA, double sigSEA, double kappaSEA);//edit Julien Papaix
	~Salmon();
	unsigned ID() const{return ID_;}
	double W() const{return W_;}
	double L() const{return L_;}
	double Wini() const{return Wini_;}
	double Lini() const{return Lini_;}
	double F() const{return F_;}
	double DW() const{return DW_;}
	double gPercF() const{return gPercF_;}
	double pPercF() const{return pPercF_;}
	double mPercF() const{return mPercF_;}
	double gG() const{return gG_;}
	double gG_sea() const{return gG_sea_;}
	double pG() const{return pG_;}
	double pG_sea() const{return pG_sea_;}
	double AgeRiver() const{return age_river_;}
	double AgeSea() const{return age_sea_;}
	bool female() const{return female_;}
	bool parr() const{return parr_;}
	bool at_sea() const{return at_sea_;}
	bool mature() const{return mature_;}
	bool smolt() const{return smolt_;}
	bool grilse()const{return mature_ && at_sea_ && (age_sea_<2.0);}
	double date() const{return date_;}
	double year() const{return year_;}
	double gSLmid()const{return gSLmid_;};
	double galphaS()const{return galphaS_;};
	double pSLmid()const{return pSLmid_;};
	double palphaS()const{return palphaS_;};
	double gFmid(unsigned w){return gFmid_[w];};
	double pFmid(unsigned w){return pFmid_[w];};

	double gNeutral(){return myGenes_.gNeutral();};

	double* all_info();

	unsigned CollecID() const{return CollecID_;}
	void set_CollecID(unsigned id){CollecID_=id;}

	void growS(double InfluenceSeaM,double InfluenceSeaSd, double OmegaS, double DensEffect, double nb_days);
	void marine_growth(double InfluenceSeaM,double InfluenceSeaSd, double nb_days);

	void check_spring_maturation_river();
	void check_autumn_maturation_ocean();
	double projectionF(double nbD, double nbDp);

	void check_PRMN_param();
	void check_smoltification();
	void migration();
	void prepare_winter_activity();
	void prepare_summer_activity();

	double P_survival() const{return P_survival_;}
	void Initialize_P_survival();
	void check_mortality(double rnd,double nb_days);
	void die() {dead_=true;}
	bool dead() const{return dead_;}

	bool condition(int *conditions);
	void reinitialize_maturation();
	void stop_maturation();
	double returns() const{return returns_;}

	void update_date(double nb_days);

	Genes genes()const {return myGenes_;};
	double Neggs(double Mean_egg_W_pop,double Min_egg_W_pop,double Max_egg_W_pop,
			double WtoWegg_a, double WtoWegg_b, double WtoWegg_c,
			double WtoNegg_a, double WtoNegg_b);
	double EggW() const{return Mean_egg_W_;};
	void participate_repro(double Loss_Fat);
	bool check_available();
	void not_yet_reproduced() {reproduced_=false;Nreprod_thisyear_=0;}
	double Nreprod_thisyear()const{return Nreprod_thisyear_;};
	double Nreprod()const{return Nreprod_;};
	bool reproduced() const{return reproduced_;}

	unsigned motherID() const{return myGenes_.motherID();};
	unsigned fatherID() const{return myGenes_.fatherID();};
	double motherStrat() const{return myGenes_.motherStrat();};
	double fatherStrat() const{return myGenes_.fatherStrat();};

	void erase_males() {selected_males_ID_.clear();selected_parrs_ID_.clear();}
	void push_parr(unsigned ID) {selected_parrs_ID_.push_back(ID);}
	void push_male(unsigned ID) {selected_males_ID_.push_back(ID);}
	unsigned selected_male_size() const{return selected_males_ID_.size();}
	unsigned selected_parr_size() const{return selected_parrs_ID_.size();}
	unsigned get_parr(unsigned pos) const{return selected_parrs_ID_.at(pos);}
	unsigned get_male(unsigned pos) const{return selected_males_ID_.at(pos);}
	void set_daterepro(unsigned daterepro) {daterepro_=daterepro;}
	unsigned get_daterepro() const{return daterepro_;}
	bool not_already_selected_male(unsigned ID) const{return (find(selected_males_ID_.begin(),selected_males_ID_.end(),ID)==selected_males_ID_.end());}
	bool not_already_selected_parr(unsigned ID) const{return (find(selected_parrs_ID_.begin(),selected_parrs_ID_.end(),ID)==selected_parrs_ID_.end());}

	double mass_repro()const{return Neggs_*Mean_egg_W_;}
	double SpecificGR()const{return specific_growth_river_;}

private:

	/* State variables */
	unsigned ID_;
	bool female_;
	bool parr_;
	bool mature_;
	bool at_sea_;
	bool smolt_;
	bool dead_;
	double L_,L0_,Lini_;		//length, temporal and initial
	double W_,W0_,Wini_;		//mass or weight, temporal and initial
	double F_;		// fat or storage
	double F_maturing_memory_; // fat at the beginning of the evaluation window.
	double age_river_,age_sea_,age_days_,date_,year_; //age variables
	double DW_;			//last increase in weight
	double activity_; // to regulate winter growth and smolt compensations...
	double aPercF_; // actual capacity to produce fat from gain of W depending on maturation metabolism
	double returns_;	//nb of returns from ocean
	double P_survival_; //probability to survive at the present time step

	/*Populational stuffs*/
	double K_, Wmax_;// parameters from population for ocean growth
	double mPercF_; // theoretical capacity to produce fat from gain of W when maturing (all same for population)
	double popPercF_; //parameter representing the population capacity to produce fat to correct L in function of Fat produced
	double winterLMG_activity_, smolt1_activity_,smoltN_activity_; // level parameters from population
	double lwa_sea_,lwb_sea_,lwa_,lwb_,b_allom_;  // L~W parameters from population
	double Sp0_, Sp1_, Sp1S_, Sp1M_, SpnM_, Spn_,  RickA_,  RickB_; // survival parameters from population
	double maxRIV_, sigRIV_, kappaRIV_, coefSURV_, pGres_;	//edit Julien Papaix: tradeoff growth-survival for river
	double maxSEA_, sigSEA_, kappaSEA_, coefSURVsea_, pG_seares_; //edit Julien Papaix: tradeoff growth-survival for sea



	/*repro and affiliation*/
	double proba_fert_;//male probability to take part in repro of one female
	double specific_growth_river_; //according to Jonsson et al. 1996 influence egg size...
	double Neggs_,Mean_egg_W_;//female fertility and mean egg size
	unsigned CollecID_;//affiliation to a collection (for replicates use)
	vector<unsigned> selected_males_ID_;//males selected by the female for repro
	vector<unsigned> selected_parrs_ID_;//parrs selected by the female for repro
	unsigned daterepro_;//female date of reproduction (not yet dependent on size or status)
	bool reproduced_;// did the individual already reproduced?
	unsigned Nreprod_;// number of reproduction events (over entire life)
	unsigned Nreprod_thisyear_;// number of reproduction events (over this year reproduction)

	/*State variables under myGenes_ influence */
	double gPercF_; // genetic capacity to produce fat from gain of W
	double pPercF_; // phenotypic expression to produce fat from gain of W
	double gG_,gG_sea_; // genetic growth capacity
	double pG_,pG_sea_; // phenotypic growth capacity
	double gFmid_[4],pFmid_[4];//,galphaF_[4],palphaF_[4],pwidthF_[4];
	double Fmid_ ;//, alphaF_,widthF_; //actual PRMN parameters --> phenotype that takes values depending on sex and river/ocean
	double gSLmid_,galphaS_;//genotype values of trait related to smoltification norm
	double pSLmid_, palphaS_; //phenotype values of trait related to smoltification norm
	Genes myGenes_;

	double all_info_[_N_COL];

};

std::ostream& operator<<(std::ostream& os, Salmon& a);



#endif
