Track of change from Ibasam in 2012-2015 papers to new version of Ibasam:  

1. Collection.cpp and .h:
	- Include tradeoff parameters maxRIV_, sigRIV_, kappaRIV_, maxSEA_, sigSEA_, kappaSEA_.
	
2. defaultParameters.h – colParamDef: 
*(note that these are not always the parameters used for papers)*
	- new parameters for tradeoff
	- increase of size of Scorff (default was 10% (but not in realized simulations), now 25%) Nmax (Beverton & Holt relationship) 
	- increase nloci for all coded traits from 10 to 20
	- set heritability of gG and gG_sea at 0.9 (0 before)
	
3. defaultParameters.h – other parameters: 
*(note that these are not always the parameters used for papers)*
	- increase of size of Scorff (default was 10% (but now in realized simulations), now 25%) 
	- N initials of each class (gParamDef, parrParamDef, smoltsParamDef,grilseParamDef, mswParamDef) and envParam
	
4. Externdlllight.cpp:
	- Number of parameters to consider

5. Salmon.cpp and .h:
	- Implementation of individual penalty for survival depending on phenotypic expression of individual growth capacity (pG_ and pG_sea_) for both river and sea
	- Include a switch when maxRIV or maxSEA parameters are set to negative values (-1 for e.g.) to remove the tradeoff effect

6. STILL TODO:
	- 

