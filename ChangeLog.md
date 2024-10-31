#2024-10-25

- Added date.h: Header file for date parsing library.

#2024-10-27

- Added csv.h: Header file for csv parsing library.

#2024-10-29

- Added suport for ROOT in makefile.

## 2024-10-30

- Added measurement.h: Header file for measurement class.

- Added measurement.cxx: Implementation file for measurement class.

- Added write.cxx: Script used to create ROOT files to be used in the analysis

- Added read.cxx: Reading the "Measurement" branch from the tree

- Edited read.cxx: Added the mapping of date/time format to the imported tree. The reason is to access the leafs/elements better for plot functions.

- Edited read.cxx: Added the date parse condition to choose a "yy-mm-dd" format for the read class.

- Edited read.cxx: Added the average yearly temp plot. The class calculates the average temperature of each year and plot it. On the top of that a fitted line is plotted and the rate of change (slope of the fitted line) is printed



## 2024-10-31

- Added root_micro.C: This micro opens root, compile and load the root scripts used for plotting/analysis

- Added run_project: This bash script runs everything needed to be loaded for the project.

- Removed example files from include and src

- Cleaned up directory: moved all header to include, all .cxx scripts to src and updated root micro

- Added README

- Changed name root_micro.C -> root_macro.C

- Removed write.cxx main.cxx Makefile

- Fixed the baredata autofinder in root_macro.C

- Added runFourier.cxx: Script to run a Fourier analysis of the temperature data.

- Changed name write.cxx -> writeTree.cxx

- Removed Example files and refined the structure of the repository

- Moved Scripts to src/

- Added Workplan.md 

- Moved runFourier.cxx and writeTree.cxx to src/

- Updated README.md

- Fixed path issues in runFourier.cxx

- Added Ourliers.cxx to src/

- Fixed yr_avg_temp() plot legend

- Added outlier.cxx: This sript finds the outliers within the defined time interval 

- Update README