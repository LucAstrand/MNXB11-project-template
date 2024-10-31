## Overview
This project is a ROOT-based application designed to [briefly describe the project's purpose, e.g., "analyze data," "simulate particle interactions," etc.]. It includes various components organized to facilitate ease of use and automated execution.

## Project Structure
- **src/**: Contains the main executables written in C++ (`.cxx` files).
- **include/**: Stores header files (`.h`) for shared definitions and function declarations.
- **root_micro.C**: A ROOT macro that [briefly explain its function, e.g., "performs data analysis" or "plots data"].
- **run_project.sh**: A bash script that automatically compiles and runs the entire project.

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
. /run_project.sh /path/to/your/csv
 ```

 This script will:
- Run smhicleaner.sh for the given .csv file.
- Execute the ROOT macro (`root_macro.C`)

