## Overview
This project is a ROOT-based application designed to [briefly describe the project's purpose, e.g., "analyze data," "simulate particle interactions," etc.]. It includes various components organized to facilitate ease of use and automated execution.

## Project Structure
- **src/**: Contains the main executables written in C++ (`.cxx` files).
- **include/**: Stores header files (`.h`).
- **root_macro.C**: The `root_micro.C` script automates the execution of the ROOT functionalities in the project. Specifically, it:

  - Adds the necessary include path for header files.
  - Loads essential C++ files:
      - measurement.cxx: defines the `Measurement` class, which encapsulates environmental measurement data, including date and time components, temperature, and air quality, with corresponding constructors, destructors, and setter/getter methods.
      - writeTree.cxx: reads measurement data from a CSV file, parses the date and time, populates a `Measurement` object with this data, and fills a ROOT TTree with the populated measurements for later analysis.
      - yr_avg_temp.cxx: calculates and plots the average temperature per year within a specified date range by reading measurement data from a ROOT TTree, storing temperatures by year, and performing a linear fit to analyze the rate of change in temperature over time.
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

