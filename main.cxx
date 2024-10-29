<<<<<<< HEAD
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>

int main() {
    TCanvas *c = new TCanvas("c", "Canvas", 800, 600);
    TH1F *h = new TH1F("h", "Test Histogram", 100, -4, 4);
    h->FillRandom("gaus", 10000);
    h->Draw();
    c->SaveAs("histogram.png");
    std::cout << "Histogram saved as histogram.png" << std::endl;
    return 0;
}
=======

#include <iostream>
#include <fstream>    // For file input
#include <string>    // For std::string
#include <vector>    // For std::vector
#include "csv.h"     // Include your CSV library header

int main(int argc, char *argv[]) {
    // Check if a filename is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_file>" << std::endl;
        return 1; // Return error code
    }

    const char* filename = argv[1];

    // Create a CSV reader object
    io::CSVReader<4> reader(filename); // Assuming there are 5 columns, but we'll skip the 4th
    reader.read_header(io::ignore_extra_column, "day", "year", "month", "measurement"); // Ignoring "ignoreme"

    // Define variables for each column
    int day, year, month;
    double measurement;

    // Read and print each row
    while (reader.read_row(day, year, month, measurement)) {
        std::cout << "Day: " << day << ", Year: " << year << ", Month: " << month << ", Measurement: " << measurement << std::endl;
    }

    return 0;
}

>>>>>>> team/homework7
