# What is IBASAM?

IBASAM (Individual Based Atlantic Salmon Model) is an individual-based demo-genetic model developed to simulate S. salar population dynamics in southern European populations.


- **How does IBASAM work?**

IBASAM is made of 8 submodels representing fundamental biological processes :
1. Reproduction and reddcreation
2. Emergence from the redds and individual birth
3. Genetic coding and transmission
4. Growth
5. Survival
6. Smoltification
7. Maturation
8. Migrations

It also includes 2 environmental submodels :
10. River climate (Water temperature and flow)
11. Ocean climate

For the sake of conciseness, all submodels are not extensively justified here. Please see [Wiki](https://github.com/Ibasam/IBASAM/wiki) and Piou et al. (2012) for further explanations and graphics of some of the mathematical functions used.

- **How to use IBASAM?**

The IBASAM model was developed in C++ and interfaced as a shared library for R (R Development Core, 2010) to make easy the statistical analyses of model outputs. The C++ source codes and R scripts to create and use the model as R package are available online on Github. More detailed explanations are provided in the [Wiki](https://github.com/Ibasam/IBASAM/wiki).

[Installation procedure](docs/installation.md)

- **What is IBASAM’ goal?**

IBASAM is a cohesive and novel tool to assess the effect of potential stressors on evolutionary demography of Atlantic salmon. It includes a demo-genetic structure coupled with the explicit representation of individual variability and complex life histories.

More detailed explanations (processes, installation procedure,...), are provided in the [Wiki](https://github.com/Ibasam/IBASAM/wiki).

# Contributors
[Cyril Piou](http://agents.cirad.fr/index.php/cyril.piou) (CIRAD, CBGP, Montpellier).
[Mathieu Buoro](https://ecobiop.com/a-propos/) (INRA, Ecobiop, St Pée s/ Nivelle).
[Etienne Prévost](https://ecobiop.com/a-propos/) (INRA, Ecobiop, St Pée s/ Nivelle).
[Julien Papaïx](https://informatique-mia.inra.fr/biosp/trombinoscope) (INRA, Biosp, Avignon).

# Sponsor
This work is financed under the [AFB](https://www.afbiodiversite.fr)-INRA conventions.

References
=============================================

Piou, C., Taylor, M. H., Papaïx, J., & Prévost, E. (2015). Modelling the interactive effects of selective fishing and environmental change on Atlantic salmon demogenetics. *Journal of Applied Ecology*, 52(6), 1629-1637. [Link](http://onlinelibrary.wiley.com/doi/10.1111/1365-2664.12512/abstract)

Piou, C., Prévost, E. (2013). Contrasting effects of climate change in continental vs. oceanic environments on population persistence and microevolution of Atlantic salmon. *Global Change Biology*, 19 (3) : 711-723. [Link](http://onlinelibrary.wiley.com/doi/10.1111/gcb.12085/abstract)

Piou, C. & Prévost, E. (2012) A demo-genetic individual-based model for Atlantic salmon populations: Model structure, parameterization and sensitivity. *Ecological Modelling*, 231, 37–52. [Link](http://www.sciencedirect.com/science/article/pii/S0304380012000543)


License
---

This project is licensed under the terms of the GNU General Public License GPLV3.0.
