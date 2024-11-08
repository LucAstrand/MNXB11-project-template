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

- Georgios Floros <ge1554fl-s@student.lu.se>
- Adib Shaker <ad6224sh@lu.se>
- Lucas Åstrand <lu3626as@lu.se>
- Keyu Yang <stacyyamg@gmail.com>

#### `LICENSE`

- GNU GENERAL PUBLIC LICENSE

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

### Build Steps for the Project

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

## Libraries Overview

For this project, the following libraries are used

- Lyra 
- Fast C++ CSV Parsing 
- Date 
- fmt 

### Build steps for the Libraries

The following is a suggested directory structure, which can be used to build and install the libraries needed for this project:

```
MNXB11-project-template-homework7/
├── external/
│   └── include/
│   └── lib/
│   └── lib64/
└── Makefile
```


#### Header only libraries

- For the header only libraries Lyra, Fast C++ CSV Parsing and Date, the installation procedure is as described below. All commands are intended to be executed from the root directory of the project, unless otherwise specified.

1. Lyra:

```bash
git clone https://github.com/bfgroup/Lyra.git
cp Lyra/include/lyra/lyra.hpp external/include/

```
2. Fast C++ CSV Parsing

```bash
git clone https://github.com/ben-strasser/fast-cpp-csv-parser.git
cp fast-cpp-csv-parser/csv.h external/include/

```
3. Date

```bash
git clone https://github.com/HowardHinnant/date.git
cp -r date/include/date external/include/

```
Note: This will include all the header files from the date library. For this project, use:

```bash
cp date/include/date.h external/include/
cp date/include/iso_week.h external/include/

```
## Compiled library

- The fmt library requires compilation. Follow these steps:

1. Clone the repository:

```bash
git clone https://github.com/fmtlib/fmt.git

```

2. Build fmt with CMake:

```bash
cd fmt
mkdir build
cd build
cmake ..
make

```

3. Move the compiled library files and headers to `external/lib/`and `external/include/`:

```bash
cp -r ../include/fmt external/include/
cp build/libfmt.a external/lib/

```