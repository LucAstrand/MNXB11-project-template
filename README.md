## Overview
This project is a ROOT-based application designed to [briefly describe the project's purpose, e.g., "analyze data," "simulate particle interactions," etc.]. It includes various components organized to facilitate ease of use and automated execution.

## Project Structure
- **src/**: Contains the main executables written in C++ (`.cxx` files).
- **include/**: Stores header files (`.h`).
- **root_macro.C**: The `root_micro.C` script automates the execution of the ROOT functionalities in the project. Specifically, it:

  - Adds the necessary include path for header files.
  - Loads essential C++ files:
      - measurement.cxx: [Briefly explain purpose, e.g., processes measurement data].
      - writeTree.cxx: [Explain purpose, e.g., writes data into a ROOT TTree].
      - yr_avg_temp.cxx: [Explain purpose, e.g., calculates yearly average temperature].
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

