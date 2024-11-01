#include "../include/measurement.h"
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TAxis.h>
#include <TPaveStats.h>
#include <iostream>
#include <map>

void given_year_temp(int year) {
    // Initialize Measurement branch
    Measurement* m = new Measurement();
    
    // Open the ROOT file
    TFile* f = TFile::Open("measurement_file.root");
    
    // Get the TTree from the file
    TTree* T = static_cast<TTree*>(f->Get("tree"));

    T->SetBranchAddress("Measurement", &m);

    // Get number of entries
    Long64_t N = T->GetEntries();

    // Map to store temperature and counts per day
    std::map<int, std::pair<double, int>> dayData;

    // Days in each month (non-leap year)
    const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Loop over the tree entries
    for (Int_t i = 0; i < N; i++) {
        T->GetEntry(i);
        int yearTemp = m->Gety();
        int monthTemp = m->Getm();
        int dayTemp = m->Getd();

        // Check if the year matches
        if (yearTemp == year) {
            // Calculate day of year
            int dayOfYear = 0;
            for (int m = 0; m < monthTemp - 1; m++) {
                dayOfYear += daysInMonth[m]; // Add days of previous months
            }
            dayOfYear += dayTemp; // Add current day
            
            // Handle leap year for February
            if (monthTemp > 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
                dayOfYear++; // Increase by one if it's a leap year
            }
            // Store the temperature data
            dayData[dayOfYear].first += m->Gettemp(); // Sum of temperatures
            dayData[dayOfYear].second += 1;           // Count of entries
        }
    }

    // Create a TGraph to store average daily temperatures
    TGraph *gr = new TGraph();
    int point = 0;

    // Fill the graph with the average temperature per day
    for (const auto& entry : dayData) {
        int dayOfYear = entry.first;
        double sumTemp = entry.second.first;
        int count = entry.second.second;

        if (count > 0) {
            double avgTemp = sumTemp / count; // Calculate average temperature
            gr->SetPoint(point++, dayOfYear, avgTemp);
        }
    }

    // Set axis titles and limits
    gr->SetTitle(Form("Temperatures of the year %d", year));
    gr->GetXaxis()->SetTitle("Days");
    gr->GetYaxis()->SetTitle("Temperature [Celsius]");
    gr->GetXaxis()->SetLimits(0, 365);
    gr->GetYaxis()->SetLimits(-20, 40);
    
    // Create canvas to draw the graph
    TCanvas* c1 = new TCanvas("c1", Form("Temperatures of the year %d", year), 800, 600);
    c1->cd();
    gr->Draw("ACP");

    // Define fit function with a period of 365
    TF1 *fitFunc = new TF1("fitFunc", "[0] + [1]*cos(2 * TMath::Pi() * x / 365 + [2])", 0, 365);
    fitFunc->SetParameters(10, 1, 0);  // Set initial guesses for amplitude, frequency, phase
    fitFunc->SetLineColor(kRed);
    gr->Fit(fitFunc);
    fitFunc->Draw("SAME");
    c1->Update();

    // Construct the name of the image and save it as a pdf
    std::string imageName = "Temperatures_of_the_year_" + std::to_string(year) + ".pdf";
    c1->SaveAs(imageName.c_str());

    // Clean up
    f->Close();
    delete m;
}
