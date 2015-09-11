Track of change from Ibasam to IbasamCompromis:  

1. Collection.cpp and .h:
	- Include tradeoff parameters maxRIV_, sigRIV_, kappaRIV_, maxSEA_, sigSEA_, kappaSEA_.
	
2. defaultParameters.h – colParamDef:
	- new parameters for tradeoff
	- increase of size of Scorff (default was 10% (but not in realized simulations), now 25%) Nmax (Beverton & Holt relationship) 
	- increase nloci for all coded traits from 10 to 20
	- set heritability of gG and gG_sea at 0.9 (0 before)
	
3. defaultParameters.h – other parameters: 
	- increase of size of Scorff (default was 10% (but now in realized simulations), now 25%) 
	- N initials of each class (gParamDef, parrParamDef, smoltsParamDef,grilseParamDef, mswParamDef) and envParam
	- NOTE: fixed a bug of inversion of parameter orders (bF was after logCrit flow parameters)
	
4. Externdlllight.cpp:
	- Number of parameters to consider

5. Salmon.cpp and .h:
	- Implementation of individual penalty for survival depending on phenotypic expression of individual growth capacity (pG_ and pG_sea_) for both river and sea
	- NOTE: improved the code by computing only once the coefSURV_ and coefSURVsea_ in the individual constructor instead of each time the growth/survival functions are called.
	- NOTE: I also added a asserting test to verify that coefSURV_ and coefSURVsea_ are >0 and <=1

6. STILL TODO:
	- Include a switch (or when some parameters are set to -1 for e.g.) to remove the tradeoff effect

