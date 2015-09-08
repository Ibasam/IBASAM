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

#include "Redd.h"
#include <math.h>

Redd::Redd() {
}

Redd::Redd(Genes _female)
:female(_female){
}

Redd::~Redd() {
}

void Redd::setup(unsigned date,double Neggs, double MeanW)
{
	dateRepro_=date;
	Neggs_=Neggs;
	Mean_egg_W_=MeanW;
}

double Redd::percentStrategy(unsigned strategy)
{
	unsigned strati;
	double perc=0.;
	for(unsigned i=0;i<size();++i)
	{
		strati=static_cast<unsigned>(floor(10.*at(i).strategy()));
		if(strati==strategy)
			perc+=Eggs_per_selected_males.at(i);
	}
	return perc;///Neggs_;
}
