HELLO!
========
              
This file should help you install the Ibasam package on your machine.

Contents of the folder:  
- this file  
- helper file for windows installation (do the II. steps automatically, remove the ~in the name)  
- helper file for linux installation (do the II. steps automatically)  
- an Ibasam folder that contains:  
  *src* folder : C++ codes of the model  
  *data* folder : data used in the model  
  *R* folder : R codes to interface with the dynamic library  
  *man* folder : R documentation (unfinished)  

Below are the steps for:  
1. a windows installation              
2. a linux installation

Sorry for the others...


1. Windows installation
=============================================

**Tested with Win7 and WinXP**

I. Pre-required:
---
  a) R installed (32bit and/or 64bit)  
  b) R binaries on the "path" (see http://en.wikipedia.org/wiki/Environment_variable if really you have no ideas what is your "path")  
  c) Download and unzip Boost to something like "c:/Program Files (x86)/boost"   
  d) Rtools installed and MinGW correctly accessible in the "path" (see https://cran.r-project.org/bin/windows/Rtools/) 

II. Steps for installation
---
  a) allow the G++ compiler to find the place where the boost folder is (typically inside a boost_1_NN_N folder) either by:   
      i) copying the boost folder into the include directory of you MinGW distribution (I know it's brutal but avoid so many troubles when using different IDEs)  
      ii) modify the Ibasam/src/Makevars.win file in giving the place (and eventual boost version) where you unziped boost  
  b) open a Console and go on the parent folder of Ibasam (e.g. your documents folder)  
  c) run the following command on the console: R CMD build Ibasam  
  d) check that the Ibasam_2.3.0.tar.gz file was created  
  e) run the following command on the console: R CMD INSTALL Ibasam_2.3.0.tar.gz  
  f) if you have an error message about dynamic_bitset of boost, it is because the compiler did not find boost, check the step II-b again and redo the following steps. If you have an error of installation of the package after compilation of the Ibasam.dll, check that R is finding the library path correctly and has installed Ibasam in the default folder, maybe then the problem is your adminstrative rights (to change them, run the console as administrator). 
  
If you still have problems, write to me.
      



2. Linux installation
=============================================

 **Tested with Ubuntu 14.04**
 

I. Pre-required:  
----
  a) R installed  
  
  ```
  
  sudo sudo apt-get update
  
  sudo apt-get install r-base
  
  sudo apt-get install r-base-dev  
 ```
 
    
  b) Download and unzip Boost (in my case it was located at /home/piou/boost)

II. Steps for installation
---
  a) allow the G++ compiler to find the place where the boost folder is (typically inside a boost_1_NN_N folder) either by modifying the Ibasam/src/Makevars file in giving the place (and eventual boost version) where you unziped boost  
  b) open a terminal and go on the parent folder of Ibasam (e.g. your documents folder)  
  c) run the following command on the console: 
  ````R CMD build Ibasam ````
   
  d) check that the Ibasam_2.3.0.tar.gz file was created  
  e) run the following command on the console: 
  ````R CMD INSTALL Ibasam_2.3.0.tar.gz ````
   
  f) if you have an error message about dynamic_bitset of boost, it is because the compiler did not find boost, check the step II-b again and and redo the following steps. If you have an error of installation of the package after compilation of the Ibasam.dll, check that R is finding the library path correctly and has installed Ibasam in the default folder, maybe then the problem is your adminstrative rights. 
  
If you still have problems, write to me.

      
Hope you'll enjoy,  
Cyril Piou

piou.cyril< at < yahoo.fr
  
