2024-10-30


Add read.cxx: Reading the "Measurement" branch from the tree

Edit read.cxx: Added the mapping of date/time format to the imported tree. The reason is to access the leafs/elements better for plot functions.


Edit read.cxx: Added the date parse condition to choose a "yy-mm-dd" format for the read class.

Edit read.cxx: Added the average yearly temp plot. The class calculates the average temperature of each year and plot it. On the top of that a fitted line is plotted and the rate of change (slope of the fitted line) is printed