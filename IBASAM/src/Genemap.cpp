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
#include <math.h>
#include "Genemap.h"

Genemap::Genemap() {
}

Genemap::Genemap(unsigned nloci,double heritability, double mean, double sd)
{
	heritability_=heritability;
	mean_=mean;
	sd_=sd;
	if(heritability_>0.)
	{
		myassert(nloci>0);
		nloci_ = nloci;
		br1.resize(nloci_);
		br2.resize(nloci_);
		if(nloci_<30)
		{
			br1= dbitset(static_cast<int>(nloci_),rloci(nloci_));
			br2= dbitset(static_cast<int>(nloci_),rloci(nloci_));
		}else{
			for(unsigned i=0;i<nloci;++i) //could use this structure if want nloci to be >30
			{
				br1[i]=rbool();
				br2[i]=rbool();
			}
		}
		initialize_lims();
	}
}

Genemap::Genemap(dbitset b1, dbitset b2,double heritability,double mean, double sd)
{

	heritability_=heritability;
	mean_=mean;
	sd_=sd;
	if(heritability_>0.)
	{
		nloci_ = b1.size();
		br1=b1;
		br2=b2;
		myassert(nloci_>0);
		myassert(br2.size()==br1.size());
		initialize_lims();
	}
}

Genemap::Genemap(double mean, double sd)
{
	mean_=mean;
	sd_=sd;
	heritability_=0.;
}

Genemap::~Genemap() {
}

void Genemap::initialize_lims()
{
	double hr=sqrt(sd_*sd_*2*nloci_/(0.25*(1+(1-heritability_)/heritability_)))/2;
	liminf_ = mean_ - hr;
	limsup_ = mean_ + hr;
}

dbitset Genemap::reassort()
{
	dbitset br(nloci_);
	if(heritability_>0.)
	{
		if(nloci_<30)
		{
			dbitset rand(static_cast<int>(nloci_),rloci(nloci_));
			for(unsigned i=0;i<nloci_;++i)
			{
				if(rand[i])
					br[i]=br1[i];
				else
					br[i]=br2[i];
			}
		}else{
			for(unsigned i=0;i<nloci_;++i)
			{
				if(rbool())
					br[i]=br1[i];
				else
					br[i]=br2[i];
			}
		}
	}
	return br;
}
double Genemap::standardized_value()
{
	double res=0;
	if(heritability_>0.)
	{
		res+= static_cast<double>(br1.count());
		res+= static_cast<double>(br2.count());
		res/= static_cast<double>(nloci_*2);
	}
	return res;
}

double Genemap::expression()
{
	double res=0;
	if(heritability_>0.)
	{
		res+= static_cast<double>(br1.count());
		res+= static_cast<double>(br2.count());
		res/= static_cast<double>(nloci_*2);
		res=res*(limsup_-liminf_)+liminf_;
	}else
		res=rnorm(mean_,sd_);
	return res;
}

double Genemap::phenotype()
{
	double res=expression();
	if(heritability_>0.){
		double varG = (limsup_-liminf_)*(limsup_-liminf_) * 0.25/(nloci_*2);
		double varE = varG * (1-heritability_)/heritability_;
		double sdE = sqrt(varE);
		res = rnorm(res,sdE);
	}
	return res;
}

Genemap reproduction(Genemap *mother, Genemap* father)
{
	if(mother->heritability()>0.)
		return Genemap(mother->reassort(), father->reassort(),mother->heritability(),mother->mean(),mother->sd());
	else
		return Genemap(mother->mean(),mother->sd());
}

