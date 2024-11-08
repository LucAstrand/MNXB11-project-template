# MNXB11 Project Template - Homework 7

## Project Overview

The repository contains folders and files related to this project

### Folders

#### `datasets/`
- Contains data files used in the project

#### `dependencies/`
- External libraries required for the project, such as:
  - **Lyra**: A command-line argument parsing library.
  - **fmt**: A modern formatting library for C++.

#### `include/`
- Header files such as:
  - **csv.h**: Utilities for handling CSV files.
  - **date.h**: Utilities for handling date
  - **fmt**: Header files from the fmt library.

#### `src/`
- Source code files

---

### Key Files

#### `.clang-format`
- Configuration for automated code

#### `.gitignore`
- Specifies files and directories to be ignored by Git.

#### `AUTHORS`

#### `LICENSE`

#### `Makefile`
- Defines the build process:
  - `make`: Builds the project.
  - `make clean`: Removes generated files.


#### `main.cxx`
- The main program file where the logic of the project is implemented.


---

## Build Instructions

### Prerequisites

- A C++17 compliant compiler (e.g., GCC or Clang).
- [ROOT](https://root.cern.ch) framework installed.

### Build Steps

1. Clone the repository:
   ```bash
      git clone https://github.com/Adib-Sh/MNXB11-project-template.git
      cd MNXB11-project-template-homework7
   ```

2. Build the project:
   ```bash
      make
   ```

3. Run the main program:
   ```bash
      ./main
   ```
