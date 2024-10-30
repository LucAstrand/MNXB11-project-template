#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TGraph.h>
#include <TLegend.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <measurement.h>

std::tm parseDate(const std::string& dateStr) {
    std::tm date = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&date, "%Y-%m-%d"); // Parse the date string
    if (ss.fail()) {
        std::cerr << "Error parsing date: " << dateStr << std::endl;
    }
    return date;
}

void read(const std::string& startDateStr, const std::string& endDateStr) {
    std::tm startDate = parseDate(startDateStr);
    std::tm endDate = parseDate(endDateStr);

    // Initialize Measurement branch
    Measurement* m = new Measurement();
    
    // Open the ROOT file
    auto f = TFile::Open("measurement_file.root");
    
    // Get the TTree from the file
    TTree* T = static_cast<TTree*>(f->Get("tree"));

    
    // Access Measurement objects
    T->SetBranchAddress("Measurement", &m);
    Long64_t N = T->GetEntries();

    // Use a map to store temperatures for each year, as in to correlate 
    // each entry to the corresponding temperature
    std::map<int, std::vector<std::pair<std::tm, double>>> yearlyData;

    // Loop over the tree entries
    for (Int_t i = 0; i < N; i++) {
        T->GetEntry(i);
        
            std::tm date = {};
            date.tm_year = m->Gety() - 1900;
            date.tm_mon = m->Getm() - 1;
            date.tm_mday = m->Getd();
            date.tm_hour = m->Geth();
            date.tm_min = m->Getmin();
            date.tm_sec = m->Getsec();
            
            // Store the date and temperature in the map
            // ADD ANY OTHER MAP YOU PREFR HERE
            if (difftime(mktime(&date), mktime(&startDate)) >= 0 &&
            difftime(mktime(&date), mktime(&endDate)) <= 0) {
            
            // Store the date and temperature in the map
            yearlyData[m->Gety()].emplace_back(date, m->Gettemp());// For yearly average plot
        }; 
        }
}

    
    // Clean up
    //delete h2;
    //delete c1;
    //delete m;       // Ensure to free the Measurement object
    //f->Close();     // Close the ROOT file

