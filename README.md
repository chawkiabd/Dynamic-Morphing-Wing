<a href="https://www.researchgate.net/publication/324760492_Morphing_airfoils_analysis_using_dynamic_meshing"><img src="https://github.com/chawkiabd/Dynamic-Morphing-Wing/blob/master/image34.gif" title="Dynamic Morphing" alt="Morphing" align="middle"></a>

 Flow Response to Rapid Morphing Flap Deflection from [Article](https://www.researchgate.net/publication/332244621_Flow_response_to_rapid_morphing_flap_deflection)



# Dynamic Morphing Wing CFD
This project contains the user-defined functions (UDF) necessary to perform unsteady computational fluid dynamics (CFD) analysis of dynamically morphing wings equipped with morphing flaps.

There are three UDFs for each of the following applications:
1.	2D Downward Dynamic Morphing Flap
2.	2D Harmonic Morphing Flap
3.	3D Morphing Wing with Seamless Side-edge Transition

## Prerequisites
The UDFs were specifically developed and tested for ANSYS Fluent 18.1 and above, there is backward compatibility although some differences might be present in the building and compiling process within ANSYS Fluent.

Make sure that a proper compiler is installed on the machine, Visual Studio 2012 for instance, and the environment variables are set accordingly.

## Getting Started

1. When the mesh is created, make sure that the origin of the coordinates system is at the leading-edge start
2. Make sure that the upper/lower surfaces of the wing are defined and names separately
3. Download the UDF needed for the application required (2D downward, 2D harmonic or 3D downward)
4. select Define > User Defined > Functions > Compiled.
5. Select the Add button to add your source file.
6. Select Build.
7. After the UDF has been successfully built it is necessary to load the built library by clicking load 
8. Once this is done, make sure to go to the dynamic mesh tab and assign to each of the wing surfaces a user-defined function (Up or down)
9.The user could preview the mesh motion from preview mesh option
10. Durig an unsteady run the mesh deformation will start from the user-defined morphing start time chosen by the user, this needs to be specified within the UDF

## Author(s)
Dr Chawki Abdessemed,
[Cranfield University](https://www.cranfield.ac.uk/people/dr-chawki-abdessemed-24525903)
[UWE Bristol](https://people.uwe.ac.uk/Person/ChawkiAbdessemed)
[Linkdin](https://www.linkedin.com/in/chawki/), 
[Researchgate](https://www.researchgate.net/profile/Chawki_Abdessemed), 
[Google Scholar](https://scholar.google.co.uk/citations?user=vbTcxkUAAAAJ&hl=en).

## Citing
If you use one of the UDFs in a thesis work or scientific publication, we would appreciate citations to the following paper and PhD thesis from the list below:

- Abdessemed, C.; Bouferrouk, A.; Yao, Y. (2021) “Aerodynamic and Aeroacoustic Analysis of a Harmonically Morphing Airfoil Using Dynamic Meshing“. Acoustics 2021, 3, 177-199. https://doi.org/10.3390/acoustics3010013
- Abdessemed, C., Yao, Y., Bouferrouk, A., and Narayan, P., 2020. Dynamic Mesh Framework for Morphing Wings CFD - UDF. <a href="https://doi.org/10.5281/zenodo.3724146"><img src="https://zenodo.org/badge/DOI/10.5281/zenodo.3724146.svg" alt="DOI"></a>
- Abdessemed, C., 2020. Dynamic Mesh Framework for Morphing Wings CFD (Doctoral dissertation).https://uwe-repository.worktribe.com/output/1490739
-	Abdessemed, C., Yao, Y., Bouferrouk, A., and Narayan, P., (2017) “Morphing Airfoils Analysis Using Dynamic Meshing” International Journal of Numerical Methods for Heat and Fluid Flow., Vol. 28 Issue: 5, pp.1117-1133. https://doi.org10.1108/HFF-06-2017-0261
-	Abdessemed, C., Yao, Y., Bouferrouk, A. and Narayan, P. (2018) “Analysis of a 3D Unsteady Morphing Wing with Seamless Side-edge Transition”. In: 2018 Applied Aerodynamics Conference Atlanta, Georgia, 25 - 29 June 2018. https://doi.org/10.2514/6.2018-3178
-	Abdessemed, C., Yao, Y., Bouferrouk, A. and Narayan, P. (2018) “Aerodynamic Analysis of a Harmonically Morphing Flap Using a Hybrid Turbulence Model and Dynamic Meshing”, In: 2018 Applied Aerodynamics Conference Atlanta, Georgia, 25 - 29 June 2018. https://doi.org/0.2514/6.2018-3813
-	Abdessemed, C., Yao, Y., Bouferrouk, A., and Narayan, P., (2019) “Flow Response to Rapid Morphing Flap Deflection”, in: 54th 3AF International Conference on Applied Aerodynamics, Paris, France, 26 – 28 March 2019. [Link](https://www.researchgate.net/publication/332244621_Flow_response_to_rapid_morphing_flap_deflection)

## Acknowledgments
Chawki Abdessemed gratefully acknowledges the studentship funding  received  from  the  Engineering  Modelling  and Simulation  Research  Group,  University  of  the  West  of England, Bristol, UK.

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
