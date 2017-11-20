HELLO!
========
           
           
<img width="630" alt="ibasam" src="https://user-images.githubusercontent.com/14179200/33024686-0efb54d8-ce0c-11e7-957f-a956b12cbcf7.png">
       
           
           
Contents of the folder:  
- this file  
- helper file for windows installation (do the II. steps automatically)  
- helper file for linux installation (do the II. steps automatically)  
- an Ibasam folder that contains:  
  *src* folder : C++ codes of the model  
  *data* folder : data used in the model  
  *R* folder : R codes to interface with the dynamic library  
  *man* folder : R documentation (unfinished)  

Below are the steps that should help you install the Ibasam package on your machine for:  
1. Windows              
2. Linux 

On the 3. Literature, you'll find links to the papers published about Ibasam.

If you still have problems for the installation, write to me.
      
Hope you'll enjoy,  
Cyril Piou

piou.cyril< at < yahoo.fr



1. Windows installation  
=============================================

**Tested with Win7 64bit and WinXP 32bit**

I. Pre-required:
---
  a) R installed (32bit and/or 64bit)  
  b) R binaries on the "path" (see http://en.wikipedia.org/wiki/Environment_variable if really you have no ideas what is your "path")  
  c) Download and unzip Boost (http://www.boost.org/) to something like "c:/Program Files (x86)/boost"   
  d) Rtools installed and MinGW correctly accessible in the "path" (see https://cran.r-project.org/bin/windows/Rtools/) 

II. Steps for installation
---
  a) allow the G++ compiler to find the place where the boost folder is (typically inside a boost_1_NN_N folder) either by:  
  - copying the boost folder into the include directory of you MinGW distribution (I know it's brutal but avoid so many troubles when using different IDEs)  
  - modifying the Ibasam/src/Makevars.win file in giving the place (and eventual boost version) where you unziped boost  
      
  b) open a Console and go on the parent folder of Ibasam (e.g. your documents folder)  
  c) run the following command on the console: 
  ```R CMD build Ibasam ```  
  d) check that the Ibasam_2.3.1.tar.gz file was created  
  e) run the following command on the console: 
  ```R CMD INSTALL Ibasam_2.3.1.tar.gz ```  
  f) if you have an error message about dynamic_bitset of boost, it is because the compiler did not find boost, check the step II-a again and redo the following steps. If you have an error of installation of the package after compilation of the Ibasam.dll, check that R is finding the library path correctly and has installed Ibasam in the default folder, maybe then the problem is your administrative rights (to change them, run the console as administrator).  



2. Linux installation
=============================================

 **Tested with Ubuntu 14.04 64bit**
 

I. Pre-required:  
----
  a) R installed  
  
  ```
  
  sudo sudo apt-get update
  
  sudo apt-get install r-base
  
  sudo apt-get install r-base-dev  
 ```
 
    
  b) Install Boost (http://www.boost.org/):
  ```sudo apt-get install libboost-all-dev ```
  or download and unzip the Boost library (in my case it was located at /home/piou/boost)

II. Steps for installation
---
  a) allow the G++ compiler to find the place where the boost folder is (typically inside a boost_1_NN_N folder) either by: 
  - having it installed right into the /usr/include directly
  - modifying the Ibasam/src/Makevars file in giving the place (and eventual boost version) where you unziped boost 
  
  b) open a terminal and go on the parent folder of Ibasam (e.g. your documents folder)  
  c) run the following command on the console: 
  ```R CMD build Ibasam ```
   
  d) check that the Ibasam_2.3.0.tar.gz file was created  
  e) run the following command on the console: 
  ```R CMD INSTALL Ibasam_2.3.1.tar.gz ```
   
  f) if you have an error message about dynamic_bitset of boost, it is because the compiler did not find boost, check the step II-a again and and redo the following steps. If you have an error of installation of the package after compilation of the Ibasam.so, check that R is finding the library path correctly and has installed Ibasam in the default folder, maybe then the problem is your administrative rights. 
  
  

3. Literature  
=============================================

Piou, C., Taylor, M. H., Papaïx, J., & Prévost, E. (2015). Modelling the interactive effects of selective fishing and environmental change on Atlantic salmon demogenetics. *Journal of Applied Ecology*, 52(6), 1629-1637. [Link](http://onlinelibrary.wiley.com/doi/10.1111/1365-2664.12512/abstract)

Piou, C., Prévost, E. (2013). Contrasting effects of climate change in continental vs. oceanic environments on population persistence and microevolution of Atlantic salmon. *Global Change Biology*, 19 (3) : 711-723. [Link](http://onlinelibrary.wiley.com/doi/10.1111/gcb.12085/abstract)

Piou, C. & Prévost, E. (2012) A demo-genetic individual-based model for Atlantic salmon populations: Model structure, parameterization and sensitivity. *Ecological Modelling*, 231, 37–52. [Link](http://www.sciencedirect.com/science/article/pii/S0304380012000543)


License
---

This project is licensed under the terms of the GNU General Public License GPLV3.0.
