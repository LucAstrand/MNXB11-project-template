#include "measurement.h"
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <iostream>

// void read(int year) {
//     // Initialize your Measurement object
//     Measurement* m = new Measurement();
    
//     // Open the ROOT file
//     auto f = TFile::Open("measurement_file.root");
//     if (!f || f->IsZombie()) {
//         std::cerr << "Failed to open the ROOT file.\n";
//         return;
//     }
    
//     // Get the TTree from the file
//     TTree* T = static_cast<TTree*>(f->Get("tree"));
//     if (!T) {
//         std::cerr << "Failed to retrieve the TTree.\n";
//         f->Close();
//         return;
//     }
    
//     // Set the branch address to access Measurement objects
//     T->SetBranchAddress("Measurement", &m);
    
//     // Get the number of entries in the tree
//     Long64_t N = T->GetEntries();
    
//     // Create a 2D histogram for temperature across months for the specified year
//     TH2F* h2 = new TH2F("h2", Form("Temperature Distribution for %d; Month; Temperature (C)", year), 
//                         12, 1, 13, 60, -10, 40);  // 12 bins for months (1-12), temperature range -10 to 40 °C
    
//     // Loop over the tree entries
//     for (Int_t i = 0; i < N; i++) {
//         T->GetEntry(i);
        
//         // Check if the entry is from the specified year
//         if (m->Gety() == year) {
//             // Fill the histogram with month on x-axis and temperature on y-axis
//             h2->Fill(m->Getm(), m->Gettemp());
//         }
//     }
    
//     // Create a canvas to draw the histogram
//     TCanvas* c1 = new TCanvas("c1", Form("Temperature Distribution for %d", year), 800, 600);
//     h2->Draw("COLZ");  // Use "COLZ" option for color map display
    
//     c1->Update();
    
//     // Clean up
//     delete m;
//     f->Close();
//     // delete f;
// }

void read(int syear, int eyear) {

    Int_t nYears = eyear - syear + 1;

    // Initialize your Measurement object
    Measurement* m = new Measurement();
    
    // Open the ROOT file
    auto f = TFile::Open("measurement_file.root");

    
    // Get the TTree from the file
    TTree* T = static_cast<TTree*>(f->Get("tree"));

    // Set the branch address to access Measurement objects
    T->SetBranchAddress("Measurement", &m);
    
    // Get the number of entries in the tree
    Long64_t N = T->GetEntries();
    
    // Create a 2D histogram for the average yearly temperature across years
    TH2F* h2 = new TH2F("h2", Form("Avg Yearly Temperature Distribution between %d - %d; Year; Average Temperature (C)", syear, eyear), 
                        nYears, syear, eyear, 60, -10, 40);  // Temperature range -10 to 40 °C
    
    // Map to store accumulated temperature and count per year
    std::map<int, std::pair<double, int>> yearData;

    // Loop over the tree entries
    for (Int_t i = 0; i < N; i++) {
        T->GetEntry(i);
        
        int year = m->Gety();
        if (year >= syear && year <= eyear) {
            // Accumulate temperature data for the year
            yearData[year].first += m->Gettemp(); // Sum of temperatures
            yearData[year].second += 1;           // Count of entries
        }
    }

    // Fill the histogram with average temperature per year
    for (auto& entry : yearData) {
        int year = entry.first;
        double sumTemp = entry.second.first;
        int count = entry.second.second;
        
        if (count > 0) {
            double avgTemp = sumTemp / count; // Calculate average temperature
            h2->Fill(year, avgTemp);          // Fill histogram with the average
        }
    }
    
    // Create a canvas to draw the histogram
    TCanvas* c1 = new TCanvas("c1", Form("Avg Yearly Temperature Distribution between %d - %d", syear, eyear), 800, 600);
    h2->Draw("COLZ");  // Use "COLZ" option for color map display
    
    c1->Update();
    
    // Clean up
    delete m;
    // f->Close();
    // delete f;
}