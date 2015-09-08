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
#ifndef DEFAULTPARAMETERS_H_
#define DEFAULTPARAMETERS_H_

//Parameters
static double envParamDef[]={//Parameters for setup_environment (should stay constant, eventually to adjust)

1.,    //Mean influence on DW in ocean (noise) -> MeanNoiseSea
0.01, //Sd of influence on DW in ocean (noise) -> Variance of NoiseSea

0.427,//Growth speed according to temperature -> dr

//Minimal, maximal and parameter regulating the optimum temperature for growth 
0.208,//gr
6.,//Tlr 
24.5,//Tur

0.2,//	Relative Critical_flow = Critical flow/module (Critical flow reinforcing density-dependent effect on growth) -> cFgi

142.7,// Density-dependent growth regulating parameter -> betadens

200811*0.25,//m² of equivalent fast running water... 200811m² for Scorf, given by Etienne.

//Parameters to relate water temperature to egg survival 
0.00019346,  //aRt
5161.93,     //bRt
0.608211,    //cRt
19.055,      //dRt

//Parameters to relate water flow to egg survival 
0.01, //aF
//Critical flow influencing on egg survival 
log(0.1),  //logCritInfFlow_ , log of relative flow that create too low water level for redds in river and influence survival -> cFi
log(7.),    //logCritSupFlow_ , log of relative flow that create too high water level for redds in river and influence survival -> cFs
100.//bF
};





static double gParamDef[]={//Parameters for add_individuals (should vary to initialize a real population and not only a cohort)
round(200811*0.25*8*0.15),// N -> here set given that we get ~3% of emerging parrs reaching smolt run stage and we assume a 0.45% from eggs to smolt survival (0.15=0.0045/0.03), the conservation limit of egg deposition is 4.75eggs/m², here assumed to be the limit of conservation for Scorff

0.2,// Wmean        -> to get ~25mm of length
0.1,//0.01,// Wsd          -> 0.087estimated from Scorf data MCMC 09032009
0.5,// femaleprob   -> start condition hypothesis
1.0,// parrprob      -> start condition hypothesis
0.0,// matureprob    -> start condition hypothesis
0.0,// at_seaprob    -> start condition hypothesis
0.0,// smoltprob      -> start condition hypothesis
0.0,// ageRiver       -> start condition hypothesis
0.0, // ageSea         -> start condition hypothesis
0.0,// Fat_m         -> start condition hypothesis
0.0,// Fat_sd        -> start condition hypothesis
0.0 // Fat_add_fem   -> start condition hypothesis
};

static double parrParamDef[]={round(200811*0.25*8*0.15 * 0.011),// N emergence *  0.011 here from  SP0^183 * SP1^182  when SPO is for 5.3% survival from emergence to parr 0 in october
7.7,// Wmean
1.8,// Wsd
0.5,// femaleprob   -> start condition hypothesis
1.0,// parrprob      -> start condition hypothesis
0.0,// matureprob    -> start condition hypothesis
0.0,// at_seaprob    -> start condition hypothesis
0.0,// smoltprob      -> start condition hypothesis
1.0,// ageRiver       -> start condition hypothesis
0.0, // ageSea         -> start condition hypothesis
0.64,// Fat_m         -> start condition hypothesis
0.28,// Fat_sd        -> start condition hypothesis
0.0// Fat_add_fem   -> start condition hypothesis
};


static double smoltsParamDef[]={round(200811*0.25*8*0.15 * 0.03),// N -> here set given that we get ~3% of emerging parrs reaching smolt run stage
30.8,// Wmean         mean of smolts 1 of scorff 2000   (not really normally distributed but best year (middle of distribution))
5,// Wsd							sd of smolts 1 of scorff 2000 ~ /2 (because else too small sizes occurs)
0.5,// femaleprob   -> start condition hypothesis
0.0,// parrprob      -> start condition hypothesis
0.0,// matureprob    -> start condition hypothesis
0.0,// at_seaprob    -> start condition hypothesis
1.0,// smoltprob      -> start condition hypothesis
1.0,// ageRiver       -> start condition hypothesis
0.0,// ageSea         -> start condition hypothesis
2,// Fat_m         -> start condition hypothesis
1.6,// Fat_sd        -> start condition hypothesis
0.0// Fat_add_fem   -> start condition hypothesis
};

static double grilseParamDef[]={round(200811*0.25*8*0.15 * 0.003),// N -> 0.03*0.10 (0.10 of "ocean survival" from scorff data)
2500 ,// Wmean
500, // Wsd
0.467 ,// femaleprob   -> start condition hypothesis
0.0,// parrprob      -> start condition hypothesis
1.0,// matureprob    -> start condition hypothesis
0.0,// at_seaprob    -> start condition hypothesis
0.0,// smoltprob      -> start condition hypothesis
1.0,// ageRiver       -> start condition hypothesis
1.0, // ageSea         -> start condition hypothesis
370,// Fat_m
100,// Fat_sd
350 // Fat_add_fem
};

static double mswParamDef[]={round(200811*0.25*8*0.15 * 0.0005),// N -> 0.03*0.017 (0.017 of "ocean survival" from scorff data)
4560 ,// Wmean
760, // Wsd
0.81 ,// femaleprob   -> start condition hypothesis
0.0,// parrprob      -> start condition hypothesis
1.0,// matureprob    -> start condition hypothesis
0.0,// at_seaprob    -> start condition hypothesis
0.0,// smoltprob      -> start condition hypothesis
1.0,// ageRiver       -> start condition hypothesis
2.0,// ageSea         -> start condition hypothesis
590,// Fat_m
110,// Fat_sd
240 // Fat_add_fem
};


static double colParamDef[]={     //Parameters for setup_collection
////////////////////////////////////////////////////////////////////////////////////////////////
//         Constants                            //
////////////////////////////////////////////////////////////////////////////////////////////////
////////Size Weight relationships  1 --> 4
3.804,// lwa, Scorff 1993-2007 data
0.32,// lwb, Scorff 1993-2007 data
3.82568,// lwa_sea, //Vibert's data (also good for smolts)    4.2652,//Scorff,
0.333779,// lwb_sea, //Vibert's data (also good for smolts) 0.2764,//Scorff,

////////Growth in River         5 --> 12
0.31,// b_allom, Elliott Hurley 1997
2,// effective_density_influence_growth: default=effective density on all parrs, 1 = effective density on 1+ and more parrs, 0 = no effect
2,// exponent_effective_size_
1, //	temperature_influence_growth_ //default and 1 = temperature function of Forseth, 0 = no effect
3.0, // mean_percent_growth_ used if temperature_influence_growth is false
0.725,//smolt1_activity         TO SEARCH
0.1,//winterLMG_activity     TO SEARCH             e.g. Bacon et al. 2005 show low winter growth
0.188,//smoltN_activity         TO SEARCH

////////Survival in River    13 --> 21
0.9841606,//SP0~5.3%, adjusted from an emergence to smolt of 3% and with SP1S given... daily survival prob parr 0 to 0.5
0.9914398, //SP1, daily survival prob parr 0.5 to 1.0 -> Buoro (estimated over 6months)
0.9967923, //SP1S, daily survival prob smolts 0.5 to run -> Buoro (estimated over 6months)
0.9863295, //SP1M, daily survival prob parr mature 0.5 to 1.0 -> Buoro (estimated over 6months)
0.9911798, //SPnM, daily survival prob parr mature n.5 to n+1 -> Buoro (estimated over 6months)
0.99775,//SPn, daily survival prob parr any other situations -> Buoro (estimated over 6months)
//edit Julien Papaix:
50,//maxRIV maximum growth rate, aded for the incorporation of trade-off growth/survival
10,//sigRIV shape of the trade-off function
921.6,//kappaRIV shape of the trade-off function
50,//maxSEA maximum growth rate, aded for the incorporation of trade-off growth/survival
10,//sigSEA shape of the trade-off function
921.6,//kappaSEA shape of the trade-off function

////////Growth at Sea    25 --> 27
0.003057074, //K, daily speed parameter of gompertz growth for ocean life, adjusted to Scorff Data
8500, //Wmax, parameter of gompertz growth for ocean life, fixed for Scorff Data
125.0, //nb of days additional of ocean life for grilse... could become stochastic!   120 from scorff data!

////////Survival at Sea    28 --> 29
2.533333,  //RickA, parameter for Psurv~(1-RickA*W^RickB) in ocean      TO SEARCH
-0.524,  //RickB, parameter for Psurv~(1-RickA*W^RickB) in ocean

////////Reproduction    30 -->  37
73, //Loss_Fat_Repro_, Amount of fat lost after 1 reproduction for anadromous males-> estimated as 59% of Fmid[2]  (59% from Fleming 1998)
1, //loose only their eggs... Loss_female_Fat_Repro_Coefficient_, Amount of fat lost after 1 reproduction for anadromous females = Neggs * Weggs * Loss_female_Fat_Repro_Coefficient_ (for the moment 1)
3, //Loss_parr_Fat_Repro, Amount of fat lost after 1 reproduction for parr males-> estimated as mean Fat of mature 1+ in november (previously using 59% of   Fmid[0]=20)  (59% from Fleming 1998)
0.5, //  Exponent_W_fert_males, used to calculate ratio of fertility of males depending on their mass (here square roots to adjust to ~40% male parr fertilization with a mean of 3 anadromous and 10 parrs participating in reproduction)
3, //Mean_number_males, mean number of males fertilizing the egg of 1 female (over several nest)       (Beall et al. ...)   4 for MSW
10, // Mean_number_parrs, mean number of male parrs fertilizing the egg of 1 female (over several nest)  (Beall et al. ...)
0.999,  //ReproMortality_[0], Male Mortality after reproduction
0.99,  //ReproMortality_[1], Female mortality after reproduction

////////Emergence   38 -->  53
880, //DDEmergeMin  -> guestimated
920, //DDEmergeMax  -> guestimated
0.1,	 //gBH     Speed Parameter on Beverton & Holt relationship     TO SEARCH
200811*0.25*10,//10, //	Nmax  Limit Parameter on Beverton & Holt relationship
0.034, //Wcv_emergence  3.4% of variance around mean W of eggs for one female (Fleming Jonsson Gross Lamber 1996) transmitted to equivalent at emergence
0.1, //	Mean_egg_W_pop, ~as in Jonsson et al. 1996
0.06,//	Min_egg_W_pop, Jonsson et al. 1996
0.2,//	Max_egg_W_pop,    Jonsson et al. 1996
0.168,//0.21,//	WtoWegg_a,    Jonsson et al. 1996
0,//0.013,//	WtoWegg_b,   Jonsson et al. 1996
5.68,//6.6,//	WtoWegg_c,       Jonsson et al. 1996
0.86,//	WtoNegg_a,    Jonsson et al. 1996
1.63,//	WtoNegg_b,    Jonsson et al. 1996
106.5,//	specific_growth_river_m,    Jonsson et al. 1996
4.4, //	specific_growth_river_sd,    Jonsson et al. 1996
0.2, //	Wini, as in gParam[2] but for population level purpose

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Phenotypic traits varying eventually under genetic influence //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1,   //genetic_on_ should the genetic material of parents be given to their offspring?  (0=no, anything else=yes)

////////Fat percentage during growth 			55 -->  60
0.12 ,// gPercFm   -> estimated  from Thorpe fat~weight relationship.        I assume 50% of reserves go to GSI for males and 66% for females
0.01,// gPercFsd   -> estimated         TO SEARCH
0.0,//25,  //gPercF_heritability, Gjerde 1996
10,   // gPercF_nloci  -> estimated
0.04,//MaturationPercF[0] percent addition of fat after maturation of males    ->estimated to obtain ~7% GSI for male
0.18,//MaturationPercF[1] percent addition of fat after maturation of females  ->estimated to obtain GSI~20% for female (Fleming 1998)

////////Growth in river       61 -->   64
0.0 ,// gGmean       center of the lognormal -> estimated
0.2,// gGsd        small variance at start -> estimated
0.9,//0.0,//14,  //	gG_heritability, (considered idem as marine, Gjerde 1994)
20,   // gG_nloci

////////Growth at sea       65 -->   68
0.0 ,// gGmeanSea    center of the lognormal -> estimated
0.2 ,// gGsdSea     small variance at start -> estimated
0.9,//14,  //	gG_sea_heritability  Gjerde 1994
20,   // gG_sea_nloci

////////Smoltification      69 -->  76
89.03333,// LmidSm           ->Norm reaction smoltification on L : logit(prob smolt)=alphaS * (L - Lmid) {recalculated to avoid using betaS}
0, //gSLmid_sd           TO SEARCH
0.,//2, //gSLmid_heritability
10, //gSLmid_nloci
0.15,//alphaS (betasmolt2 in paper) ->Buoro 2008
0.,  //galphaS_sd             TO SEARCH
0.0,//2,  //galphaS_heritability
10,   //galphaS_nloci

////////Maturation reaction norms   77 -->  88
1.250,//Fmid[0] threshold of parr males          TO SEARCH
0.65,//Fmid_sd[0] threshold_sd of parr males           TO SEARCH
0.,// NOT USED
40.0,//Fmid[1] threshold of parr females      FIXED
5.0,//Fmid_sd[1] threshold sd of parr females        FIXED
0.,// NOT USED
40,//Fmid[2] threshold of salmon males        TO SEARCH
40,//alphaF[2] threshold sd of salmon males       TO SEARCH
0.,// NOT USED
85,//Fmid[3] threshold of salmon females     TO SEARCH
75,//alphaF[3] threshold sd of salmon females     TO SEARCH
0.,// NOT USED
                                //  89 --> 91
0.,// NOT USED
0.4,//PRMN_H2, heritability of all intercept and slopes  Vandeputte et al 2004 & Blanc 2005 (in Jonsson & Jonsson 2009)
20,//PRMN_nloci, number of loci of all intercept and slopes PRMN traits

0.,//Memory success turn on/off
//NOT USED:
25071979.
};


#endif /* DEFAULTPARAMETERS_H_ */
