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

#ifndef REDD_H_
#define REDD_H_
#include <vector>
#include "Genes.h"

using namespace std;

class Redd : public vector<Genes>
{
public:
	Redd();
	Redd(Genes _female);
	~Redd();
	unsigned dateRepro() const{return dateRepro_;};
	void setup(unsigned date, double Neggs, double MeanW);
	vector<double> Eggs_per_selected_males;
	double Mean_egg_W()const{return Mean_egg_W_;};
	double Neggs()const{return Neggs_;};
	double percentStrategy(unsigned strategy);
private:
	unsigned dateRepro_;
	double Neggs_;
	double Mean_egg_W_;
public:
	Genes female;

};

#endif /* REDD_H_ */
