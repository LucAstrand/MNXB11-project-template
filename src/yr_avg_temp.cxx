#include "include/measurement.h"

// Date parser includes
#include <iomanip>

// Plot includes
#include <TCanvas.h>
#include <TColor.h>
#include <TGraph.h>
#include <TLegend.h>
#include <iostream>
#include <sstream>
#include <TF1.h>

// Read file includes
#include <map>
#include <vector>
#include <numeric>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>







// Parses the date to "YY-MM-DD" format
std::tm parseDate(const std::string& dateStr) {
    std::tm date = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&date, "%Y-%m-%d");
    if (ss.fail()) {
        std::cerr << "Error parsing date: " << dateStr << std::endl;
    }
    return date;
}

// Read class
void yr_avg_temp(const std::string& startDateStr, const std::string& endDateStr) {
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
    // ADD ANY OTHER MAP YOU PREFR HERE
    std::map<int, std::vector<double>> yearlyTemperatures;

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
            
            if (difftime(mktime(&date), mktime(&startDate)) >= 0 &&
            difftime(mktime(&date), mktime(&endDate)) <= 0) {

            // Store the date and temperature in the map
            // ADD ANY OTHER MAP YOU PREFR HERE
            yearlyTemperatures[m->Gety()].push_back(m->Gettemp());// For yearly average plot
        }; 
    }
    
    
    
//=======================Yearly Average Plot + Rate of Change=========================
    std::vector<int> years;
    std::vector<double> avgTemps;
    // Calculate average temperatures for each year
    for (const auto& [year, temps] : yearlyTemperatures) {
        double sum = std::accumulate(temps.begin(), temps.end(), 0.0);
        double avgTemp = sum / temps.size();
        years.push_back(year);
        avgTemps.push_back(avgTemp);
    }
    // Create a graph for the average temperatures
    TGraph* avgGraph = new TGraph(years.size());
    avgGraph->SetTitle("Average Temperature per Year;Year;Temperature (C)");
    for (size_t i = 0; i < years.size(); i++) {
        avgGraph->SetPoint(i, years[i], avgTemps[i]);
    }
    avgGraph->SetMarkerStyle(20);
    avgGraph->SetMarkerColor(kBlack);
    
    // Create a linear fit function
    TF1* fitFunc = new TF1("fitFunc", "pol1", years.front(), years.back());
    avgGraph->Fit(fitFunc, "R");

    // Draw the graphs on a canvas
    TCanvas* c = new TCanvas("c", Form("Average temperature of each year between %s and %s", startDateStr.c_str(), endDateStr.c_str()), 800, 600);
    c->SetTitle("Yearly average temperature");

    avgGraph->Draw("AP");

    // Draw the fit function
    fitFunc->SetLineColor(kRed);
    fitFunc->Draw("SAME");

    // Calculate the slope (rate of change) from the fit function
    double slope = fitFunc->GetParameter(1);
    std::ostringstream oss;
    oss << "Rate of Change: " << slope << " C/year";


    // Add legend
    auto legend = new TLegend(0.55, 0.19, 0.76 + 0.2, 0.1 + 0.2);
    legend->AddEntry(avgGraph, "Average Temperature", "p");
    legend->AddEntry(fitFunc, "Linear Fit", "l");
    legend->AddEntry((TObject*)0, oss.str().c_str(), "");
    legend->Draw();


    c->Update();
    c->SaveAs("yearly_average_temperature.png");
//=======================Next=========================

    
    // Clean up
    delete c;
    f->Close();
}
