#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <measurement.h>
#include <algorithm> // For std::sort
#include <vector> // Include the vector header
#include <utility>   // For std::pair
#include <iomanip>   // For std::put_time
#include <ctime>     // For std::tm

void read(int startYear, int endYear) {
    // Initialize your Measurement object
    Measurement* m = new Measurement();
    
    // Open the ROOT file
    auto f = TFile::Open("measurement_file.root");
    if (!f || f->IsZombie()) {
        std::cerr << "Failed to open the ROOT file.\n";
        return;
    }
    
    // Get the TTree from the file
    TTree* T = static_cast<TTree*>(f->Get("tree"));
    if (!T) {
        std::cerr << "Failed to retrieve the TTree.\n";
        f->Close();
        return;
    }
    
    // Set the branch address to access Measurement objects
    T->SetBranchAddress("Measurement", &m);
    
    // Get the number of entries in the tree
    Long64_t N = T->GetEntries();

    // Use a vector to store pairs of temperatures and corresponding dates
    std::vector<std::pair<double, std::tm>> temperatureDatePairs;

    // Loop over the tree entries
    for (Int_t i = 0; i < N; i++) {
        T->GetEntry(i);
        
        // Check if the entry is from the specified year range
        if (m->Gety() >= startYear && m->Gety() <= endYear) {
            // Create a tm structure to store the date
            std::tm date = {};
            date.tm_year = m->Gety() - 1900; // tm_year is years since 1900
            date.tm_mon = m->Getm() - 1;      // tm_mon is 0-11
            date.tm_mday = m->Getd();         // tm_mday is 1-31
            
            // Store the temperature and date
            temperatureDatePairs.emplace_back(m->Gettemp(), date);
        }
    }

    
    // Clean up
    //delete h2;
    //delete c1;
    //delete m;       // Ensure to free the Measurement object
    //f->Close();     // Close the ROOT file
}
