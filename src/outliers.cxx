#include <algorithm>
#include <vector>
#include <utility>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>

#include "../include/measurement.h"

void outliers(int startYear, int endYear) {
    printf("i was found");
    // Initialize Measurement object
    Measurement* m = new Measurement();
    
    // Open the ROOT file
    auto f = TFile::Open("../measurement_file.root");

    
    // Get the TTree from the file
    TTree* T = static_cast<TTree*>(f->Get("tree"));

    
    // Access Measurement objects
    T->SetBranchAddress("Measurement", &m);
    Long64_t N = T->GetEntries();

    // Use a map to store temperatures for each year, as in to correlate 
    // each entry to the corresponding temperature
    // ADD ANY OTHER MAP YOU PREFR HERE
    std::vector<std::pair<double, std::tm>> temperatureDatePairs;

    // Loop over the tree entries
    for (Int_t i = 0; i < N; i++) {
        T->GetEntry(i);

        if (m->Gety() >= startYear && m->Gety() <= endYear) {
        
            std::tm date = {};
            date.tm_year = m->Gety() - 1900;
            date.tm_mon = m->Getm() - 1;
            date.tm_mday = m->Getd();
            
            // Store the date and temperature in the map
            // ADD ANY OTHER MAP YOU PREFR HERE
            temperatureDatePairs.emplace_back(m->Gettemp(), date);
        }
    }
    
//=======================Calculate Outliers=========================
    std::vector<double> temperatures;
    for (const auto& pair : temperatureDatePairs) {
        temperatures.push_back(pair.first);
    }
    // Sort the temperature according to the Date
    std::sort(temperatures.begin(), temperatures.end());
    
    // Calculate Q1 (25th percentile) and Q3 (75th percentile)
    int n = temperatures.size();
    double Q1 = temperatures[n / 4];// 25th percentile
    double Q3 = temperatures[(3 * n) / 4];// 75th percentile
    double IQR = Q3 - Q1;

    // Define boundries for outliers
    double lowerBound = Q1 - 1.5 * IQR;
    double upperBound = Q3 + 1.5 * IQR;

    // Vector pairs of outlier temperature-date
    std::vector<std::pair<double, std::tm>> outliers;

    // Find outliers
    for (const auto& pair : temperatureDatePairs) {
        if (pair.first < lowerBound || pair.first > upperBound) {
            outliers.push_back(pair);
        }
    }



    // Print outlier information with date and write to a text file
    std::ofstream outFile("outliers.txt");
    if (outFile.is_open()) {
        outFile << "Outlier Temperatures from " << startYear << " to " << endYear << ":\n";
        for (const auto& outlier : outliers) {
            // Format the date for output
            outFile << std::put_time(&outlier.second, "%Y-%m-%d") << ": " << outlier.first << " C\n";
        }
        outFile.close();
        std::cout << "Outlier data written to outliers.txt\n";
    } else {
        std::cerr << "Failed to open outliers.txt for writing.\n";
    }

    // Clean up
    delete m;
    f->Close();
}