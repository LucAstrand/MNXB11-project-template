#include <TTree.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <iostream>
#include <map>
#include <vector>
#include "../include/measurement.h"

void generateTemperatureGraph() {
    // Open the ROOT file generated from writeTree.cxx
    TFile *file = TFile::Open("measurement_file.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Get the TTree from the file
    TTree *tree = (TTree*)file->Get("tree");
    if (!tree) {
        std::cerr << "Error: TTree not found!" << std::endl;
        return;
    }

    Measurement* m = new Measurement();
    tree->SetBranchAddress("Measurement", &m);

    // Use maps to store min and max temperatures by year
    std::map<int, double> minTemp, maxTemp;

    // Initialize min and max temps
    for (int i = 1900; i <= 2020; ++i) {
        if (i == 1957) continue; // Exclude year 1957
        minTemp[i] = 1e6; // Large initial value for min
        maxTemp[i] = -1e6; // Small initial value for max
    }

    // Loop over all entries to populate min and max temps
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        int year = m->Gety();
        int temp = m->Gettemp();
        if (year == 1957) continue; // Skip year 1957
        if (temp < minTemp[year]) minTemp[year] = temp;
        if (temp > maxTemp[year]) maxTemp[year] = temp;
    }

    // Prepare data for TGraph
    std::vector<int> years;
    std::vector<double> lowestTemps, highestTemps;
    for (int i = 1900; i <= 2020; ++i) {
        if (i == 1957) continue;
        years.push_back(i);
        lowestTemps.push_back(minTemp[i]);
        highestTemps.push_back(maxTemp[i]);
    }

    // Convert vectors to arrays
    int n = years.size();
    double *yearArray = new double[n];
    for (int i = 0; i < n; ++i) {
        yearArray[i] = static_cast<double>(years[i]);
    }
    double *lowTempArray = &lowestTemps[0];
    double *highTempArray = &highestTemps[0];

    // Create graphs
    TGraph *graphLow = new TGraph(n, yearArray, lowTempArray);
    TGraph *graphHigh = new TGraph(n, yearArray, highTempArray);

    // Customize graphs
    graphLow->SetMarkerStyle(21);      // Different marker style
    graphLow->SetMarkerColor(kBlue);
    graphHigh->SetMarkerStyle(20);
    graphHigh->SetMarkerColor(kRed);

    // Set the y-axis range
    graphHigh->SetMinimum(-50);  
    graphHigh->SetMaximum(50); 

    // Create canvas and draw
    TCanvas *canvas = new TCanvas("canvas", "Yearly Temperature Extremes", 800, 600);

    // Draw the high temperature graph first, setting up the axis
    graphHigh->SetTitle("Yearly Temperature Extremes;Year;Temperature (°C)");
    graphHigh->Draw("ALP"); 

    // Draw the low temperature graph on the same plot
    graphLow->Draw("LP SAME"); 

    // Add a legend
    TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    legend->AddEntry(graphLow, "Lowest Temperature", "p");
    legend->AddEntry(graphHigh, "Highest Temperature", "p");
    legend->Draw();

    // Update canvas to display everything
    canvas->Update();

    // Save the graph as an image
    canvas->SaveAs("output/Yearly_Temperature_Extremes.png");

    // Clean up
    delete m;
    delete[] yearArray; // Free the allocated memory
    delete canvas;
    file->Close();
    delete file;
}