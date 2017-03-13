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
#include "Collection.h"
#include "Environment.h"
#include "defaultParameters.h"
#include "R.h"
#include <cstdlib>
#include <new>

using namespace std;

static Collection MyCollec;
static Environment MyEnv;


static Collection RefCollec;
static Environment RefEnv;
static vectorSalmon FishedCollec;

void myassert(bool b)
{
	if(!b) Rf_error("Unexpected error in IBASAM... closing.");
}


extern "C" {

	void out_of_memory() {
		MyCollec.empty();
		MyEnv.Reset();
		Rf_error("Too many individuals in IBASAM for the system");
	}

	void my_terminate(){
		Rf_error("Unexpected error in IBASAM... closing.");
		//abort();
	}

	void defaultParameters(double *envParam,double *gParam,double *parrParam,double *smoltsParam,double *grilseParam,double *mswParam,double *colParam)
	{
		unsigned i = 0;
		for( ; i<13;++i)
		{
			envParam[i]=envParamDef[i];
			gParam[i]=gParamDef[i];
			parrParam[i]=parrParamDef[i];
			smoltsParam[i]=smoltsParamDef[i];
			grilseParam[i]=grilseParamDef[i];
			mswParam[i]=mswParamDef[i];
			colParam[i]=colParamDef[i];
		}
		for( ; i<17;++i)
		{
			envParam[i]=envParamDef[i];
			colParam[i]=colParamDef[i];
		}
		for( ; i<93;++i)//edit Julien Papaix
		{
			colParam[i]=colParamDef[i];
		}
	}

/************************************************************************************************
 * 																								*
 *  							Environment functions											*
 *  																							*
 ************************************************************************************************/

	void Prepare_environment_file(char** filename)
	{
		MyEnv.load(*filename);
	}

	void Prepare_environment_vectors(double *daysv, double *tempv, double *logrelflowv, double *n)
	{
		MyEnv.load(daysv,tempv,logrelflowv,n);
	}

	void Reset_environment()
	{
		MyEnv.Reset();
	}

	void recall_nb_day_simulations(double *nb)
	{
		*nb=MyEnv.nb_days();
	}

	void look_environment_data(long* nb_days, double* days, double* temperatures, double* logflows)
	{
		for(long d=1; d<=*nb_days;++d)
		{
			days[(unsigned)(d-1)]=MyEnv.days[(unsigned)(d-1)];
			temperatures[(unsigned)(d-1)]=MyEnv.temperatures[(unsigned)(d-1)];
			logflows[(unsigned)(d-1)]=MyEnv.logRelativeFlows[(unsigned)(d-1)];
		}
	}


/////////////////GROWTH RELATED////////////////////////////
	void setup_environment_parameters(double *Parameters)
	{
		MyEnv.setup_parameters(Parameters);
	}

	void Marine_growth(double *mean, double *sd)
	{
		MyEnv.Set_InfluenceDWsea(mean,sd);
	}

	void Omega(double *time_step_length, double *Omega)
	{
		*Omega=MyEnv.Omega(*time_step_length);
	}

	void OmegaS(double *time_step_length, double *OmegaS)
	{
		*OmegaS=MyEnv.OmegaS(*time_step_length);
	}

	void DensEffect(double *nb_days, double *effectiveDensity, double *DensEff)
	{
		*DensEff=MyEnv.DensEffect(*nb_days,*effectiveDensity);
	}

/////////////////TIME HANDLING////////////////////////////
	void time_tick(double* incr, double* time)
	{
		MyEnv.increment_date(*incr);
		*time=MyEnv.actual_date();
	}

	void time_look(double* time)
	{
		time[0]=MyEnv.actual_date();
		time[1]=MyEnv.actual_year();
	}



/************************************************************************************************
 * 																								*
 *  							Population functions											*
 *  																							*
 ************************************************************************************************/

	void setup_collection_parameters(double *colParam)
	{
		MyCollec.setup_collection_parameters(colParam);
		std::set_new_handler(out_of_memory);
		std::set_terminate(my_terminate);

	}

	void add_individuals(double *gParam)
	{
		MyCollec.add_individuals(gParam,&MyEnv);
	}

	void add_eggs(long *N, long *Nredds)
	{
		MyCollec.add_eggs(*N,*Nredds, &MyEnv);
	}

	void Number_individuals(long *N)
	{
		*N=(long)MyCollec.N();
	}

	void observe(double *allind)
	{
		MyCollec.observe(allind);
	}

	void length_observe_redds(long *N)
	{
		*N=(long)(MyCollec.Nredds());
	}

	void observe_redds(double *allredds)
	{
		MyCollec.observe_redds(allredds);
	}

	void n_details_one_redd(long *N,long *motherID)
	{
		*N=(long)MyCollec.n_details_one_redd(*motherID);
	}

	void details_one_redd(double *info,long *motherID)
	{
		MyCollec.details_one_redd(info,*motherID);
	}

	void memory_success_sizes(long *N)
	{
		N[0]=(long)(MyCollec.memory_success_size1());
		N[1]=(long)(MyCollec.memory_success_size2());
	}

	void memory_success(double *allinorder)
	{
		MyCollec.restitute_memory_success(allinorder);
	}

	void empty_memory_success()
	{
		MyCollec.empty_memory_success();
	}

	void grow(double *nb_days)
	{
		MyCollec.grow(*nb_days,&MyEnv);
	}

	void compensatory_growth()
	{
		MyCollec.compensatory_growth(&MyEnv);
	}

	void empty()
	{
		MyCollec.empty();
	}

	void check_spring_maturation_river()
	{
		MyCollec.check_spring_maturation_river();
	}

	void check_autumn_maturation_ocean()
	{
		MyCollec.check_autumn_maturation_ocean();
	}

	void check_smoltification()
	{
		MyCollec.check_smoltification();
	}

	void force_smolt_run()
	{
		MyCollec.force_smolt_run();
	}

	void check_return()
	{
		MyCollec.check_return();
	}

	void stop_river_maturation()
	{
		MyCollec.stop_river_maturation();
	}

	void reinitialize_salmon_maturation()
	{
		MyCollec.reinitialize_salmon_maturation();
	}

	void reinitialize_parr_maturation()
	{
		MyCollec.reinitialize_parr_maturation();
	}

	void effective_density(double *effD)
	{
		*effD=MyCollec.effective_density();
	}
	void mortality(double *nb_days)
	{
		MyCollec.mortality(*nb_days);
		MyCollec.removedead();
	}

	void emergence()
	{
		MyCollec.emergence(&MyEnv);
	}


	void reproduce()
	{
		MyCollec.reproduce(&MyEnv);
	}

	void post_repro_mortality()
	{
		MyCollec.post_repro_mortality();
	}

	void fishing(double *fishParam)
	{
		FishedCollec=MyCollec.fishing(fishParam);
	}

	void N_fished(long *N)
	{
		*N=(long)FishedCollec.N();
	}

	void observe_fished(double *allind)
	{
		FishedCollec.observe(allind);
	}

	/*************************************************************
	 * 															 *
	 * 		Wrappers of temporal processes						 *
	 * 															 *
	 *************************************************************/

	void autumn()
	{
		MyCollec.check_smoltification();//and prepare activity winter
		//before repro
		MyCollec.grow(47.0,&MyEnv) ;
		MyCollec.mortality(47.0);
		MyCollec.removedead();
		MyEnv.increment_date(47.0);
		MyCollec.check_autumn_maturation_ocean();
	}

	void winter()
	{
		MyCollec.reproduce(&MyEnv);
		MyCollec.post_repro_mortality();
		MyCollec.stop_river_maturation();//changed on 31/05/2010 !!
		//after repro
		MyCollec.grow(135.0,&MyEnv) ;
		MyCollec.mortality(135.0);
		MyCollec.removedead();
		MyEnv.increment_date(135.0);
		MyCollec.compensatory_growth(&MyEnv);
		MyCollec.reinitialize_parr_maturation();
	}

	void spring()
	{
		MyCollec.check_return();
		MyCollec.force_smolt_run(); //and prepare activity summer
		MyCollec.emergence(&MyEnv);
		MyCollec.grow(61.0,&MyEnv);
		MyCollec.mortality(61.0);
		MyCollec.removedead();
		MyEnv.increment_date(61.0);
		MyCollec.check_spring_maturation_river();
	}

	void summer()
	{
		MyCollec.grow(122.0,&MyEnv);
		MyCollec.mortality(122.0);
		MyCollec.removedead();
		MyEnv.increment_date(122.0);
		MyCollec.reinitialize_salmon_maturation();
	}

	void go_winter()
	{
		autumn();
		winter();
	}

	void go_summer()
	{
		spring();
		summer();
	}

	/*************************************************************
	 * 															 *
	 * 		Memory handling and other small stuffs				 *
	 * 															 *
	 *************************************************************/

	void keep_in_memory()
	{
		RefEnv = MyEnv;
		RefCollec = MyCollec;
	}

	void restore_in_memory()
	{
		MyEnv = RefEnv;
		MyCollec = RefCollec;
	}

	void rloci(long * N)
	{
		*N=rloci(*N);
	}

	void set_seed(long * s)
	{
		modify_seed(static_cast<unsigned>(*s));
	}



}//extern C
