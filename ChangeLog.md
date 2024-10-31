#2024-10-30

- Added read.cxx: Reading the "Measurement" branch from the tree

- Edited read.cxx: Added the mapping of date/time format to the imported tree. The reason is to access the leafs/elements better for plot functions.

- Edited read.cxx: Added the date parse condition to choose a "yy-mm-dd" format for the read class.

- Edited read.cxx: Added the average yearly temp plot. The class calculates the average temperature of each year and plot it. On the top of that a fitted line is plotted and the rate of change (slope of the fitted line) is printed



#2024-10-31

- Added root_micro.C: This micro opens root, compile and load the root scripts used for plotting/analysis

- Added run_project: This bash script runs everything needed to be loaded for the project.

- Removed example files from include and src

- Cleaned up directory: moved all header to include, all .cxx scripts to src and updated root micro

- Added README

- Changed name root_micro.C -> root_macro.C

- Removed write.cxx main.cxx Makefile

- Fixed the baredata autofinder in root_macro.C

- Fixed yr_avg_temp() plot legend


