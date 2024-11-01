## Overview
This project involves the analysis of historical temperature data using ROOT, a data analysis framework commonly used in high-energy physics. The main objectives include reading measurement data from a ROOT file and perform several analysis functions. 

## Project Structure
- **src/**: Contains the main executables written in C++ (`.cxx` files).
- **include/**: Stores header files (`.h`).
- **root_macro.C**: The `root_macro.C` script automates the execution of the ROOT functionalities in the project. Specifically, it:

  - Adds the necessary include path for header files.
  - Loads essential C++ files:
      - measurement.cxx: defines the `Measurement` class, which encapsulates environmental measurement data, including date and time components, temperature, and air quality, with corresponding constructors, destructors, and setter/getter methods.

      - writeTree.cxx: reads measurement data from a CSV file, parses the date and time, populates a `Measurement` object with this data, and fills a ROOT TTree with the populated measurements for later analysis.

      - yr_avg_temp.cxx: calculates and plots the average temperature per year within a specified date range by reading measurement data from a ROOT TTree, storing temperatures by year, and performing a linear fit to analyze the rate of change in temperature over time.

      - runFourier.cxx: reads temperature data from a ROOT TTree, calculates monthly averages, applies a Fast Fourier Transform (FFT) to analyze the frequency components of temperature variations, and visualizes the results by generating a time series graph of temperature.

      - outlier.cxx: extracts temperature and date information from a ROOT file, and considers only the data within a specified date range. Using the IQR method to determine outliers in the temperature data and writes in a `.txt` file.



  - Executes the following functions:
      - write(): Loads and processes a dataset specified by a CSV path.
      - yr_avg_temp(): Computes and outputs the average temperature between two specified dates.
- **run_project.sh**: The `run_project.sh` script serves as the main automation tool for executing the project. It performs the following tasks:
  - Input Validation: Checks if a CSV file path is provided as an argument. If not, it displays a usage message and exits.
  - File Existence Check: Verifies the existence of the specified CSV file. If the file is not found, it outputs an error message and exits.
  - Running SMHICleaner: Makes the `smhicleaner.sh` script executable to ensure it can run without permission issues.
  - ROOT Environment Setup: Sources the ROOT environment script to ensure that ROOT commands can be executed correctly.
  - ROOT Environment Setup: Sources the ROOT environment script to ensure that ROOT commands can be executed correctly.

## Getting Started

### Prerequisites
- ROOT (for data analysis and plotting).
- A compatible C++ compiler (e.g., g++).
- Bash (for running the automation script).

### Installation
1. Clone this repository:
  ```bash
  git clone https://github.com/Adib-Sh/your-repo-name.git
  cd your-repo-name
  ```
### Running the project
- To run the project execute the following bash script in a terminal
  ```bash
  ./run_project.sh /path/to/your/csv
  ```

 This script will:
- Run smhicleaner.sh for the given .csv file.
- Execute the ROOT macro (`root_macro.C`)

#### yr_avg_temp
- To choose the desire date interval for this function, edit the following line in `root_macro.C`:
```root_macro.C
gROOT->ProcessLine("yr_avg_temp(\"YYYY-MM-DD\",\"YYYY-MM-DD\")");
```
The output of this function is a `.png` file saved in the base folder. 


#### given_year_temp
- To choose the desire year for this function, edit the following line in `root_macro.C`:
```root_macro.C
gROOT->ProcessLine("given_year_temp(YYYY)");
```


#### outlier
- To choose the desire date interval for this function, edit the following line in `root_macro.C`:
```root_macro.C
gROOT->ProcessLine("outlier(YYYY,YYYY)");

```
