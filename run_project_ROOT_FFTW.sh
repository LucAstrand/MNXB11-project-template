#!/bin/bash

# Check if CSV file is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <path_to_csv_file>"
    exit 1
fi

# Store CSV file path
CSV_FILE="$1"

# Ensure the CSV file exists
if [ ! -f "$CSV_FILE" ]; then
    echo "Error: CSV file not found at $CSV_FILE"
    exit 1
fi

# Load the required modules
module load GCC/12.3.0
module load OpenMPI/4.1.5
module load ROOT/6.30.06

# Make smhicleaner.sh executable (just in case)
chmod +x smhicleaner.sh

# Run the smhicleaner script with the CSV file
./smhicleaner.sh "$CSV_FILE"

# Create the output directory if it doesn't exist
OUTPUT_DIR="output"
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir "$OUTPUT_DIR"
    echo "Created output directory: $OUTPUT_DIR"
fi

# Run the ROOT macro using the module-provided ROOT version
root -b -q root_macro_FFTW.C

# Clean up CSV and ROOT files
echo "Cleaning up files..."
rm -f *.csv *.root
rm -f src/*.d src/*.so src/*.pcm


echo "Cleanup complete."

