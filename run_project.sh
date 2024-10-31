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

# Make smhicleaner.sh executable (just in case)
chmod +x smhicleaner.sh

# Run the smhicleaner script with the CSV file
./smhicleaner.sh "$CSV_FILE"

# Source ROOT environment (adjust path as needed)
source /opt/apps/root/bin/thisroot.sh

# Run ROOT macro
root -b -q root_macro.C