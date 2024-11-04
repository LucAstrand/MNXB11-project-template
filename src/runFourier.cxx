#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TH1.h>
#include <iostream>
#include <TVirtualFFT.h>
#include <TStyle.h>
#include <map>
#include <TPaveText.h>
#include "../include/measurement.h"

struct DailyData {
    double sum;
    int count;
    DailyData() : sum(0), count(0) {}
};

struct MonthlyData {
    double sum;
    int count;
    MonthlyData() : sum(0), count(0) {}
};

void readDataAndFillHistogram(const char* filename, TH1D* hist) {
    TFile* f = new TFile(filename, "READ");
    if (!f->IsOpen()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        delete f;
        return;
    }

    TTree* tree = static_cast<TTree*>(f->Get("tree"));
    if (!tree) {
        std::cerr << "Could not find tree in file: " << filename << std::endl;
        f->Close();
        delete f;
        return;
    }

    Measurement* m = new Measurement();
    tree->SetBranchAddress("Measurement", &m);
    Long64_t nEntries = tree->GetEntries();
    
    std::map<int, DailyData> dailyTemp;
    std::map<int, MonthlyData> monthlyTemp;

    // First pass: calculate daily averages
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        int year = m->Gety();
        int month = m->Getm();
        int day = m->Getd(); 
        int dailyKey = year * 10000 + month * 100 + day;

        dailyTemp[dailyKey].sum += m->Gettemp();
        dailyTemp[dailyKey].count++;
    }

    // Second pass: calculate monthly averages from daily averages
    for (const auto& pair : dailyTemp) {
        int key = pair.first; // Daily key
        int year = key / 10000;
        int month = (key / 100) % 100;
        double dailyAvg = pair.second.sum / pair.second.count;

        int monthlyKey = year * 100 + month;
        monthlyTemp[monthlyKey].sum += dailyAvg;
        monthlyTemp[monthlyKey].count++;
    }

    // Calculate overall mean temperature
    double totalSum = 0;
    int totalMonths = 0;
    for (const auto& pair : monthlyTemp) {
        totalSum += pair.second.sum / pair.second.count;
        totalMonths++;
    }
    double meanTemp = totalSum / totalMonths;

    // Fill histogram with monthly averages
    int monthIndex = 0;
    for (const auto& pair : monthlyTemp) {
        double monthlyAvg = pair.second.sum / pair.second.count;
        hist->Fill(monthIndex, monthlyAvg - meanTemp);
        monthIndex++;
    }

    delete m;
    f->Close();
    delete f;
}

void performFourierAnalysis() {
    gStyle->SetOptStat(0);
    gStyle->SetPadGridX(true);
    gStyle->SetPadGridY(true);

    const int startYear = 1860; //1780;
    const int endYear = 2023;
    const int nMonths = ((endYear - startYear + 1) * 12) - 5;

    // Create and fill histogram
    TH1D* tempHist = new TH1D("tempHist", "Monthly Temperature Variation", 
                             nMonths, 0, nMonths);
    readDataAndFillHistogram("measurement_file.root", tempHist); 

    tempHist->Smooth(4, "G"); 

    // Create time series graph
    TGraph* gr = new TGraph(nMonths);
    gr->SetTitle("Detrended Monthly Temperature Time Series");
    for (int i = 1; i <= nMonths; ++i) {
        double year = startYear + (double)(i-1) / 12.0;
        gr->SetPoint(i - 1, year, tempHist->GetBinContent(i));
    }

    // Perform FFT
    TVirtualFFT::SetTransform(0);
    TH1* fft = tempHist->FFT(0, "MAG");
    if (!fft) {
        std::cerr << "FFT failed!" << std::endl;
        return;
    }

    // Create frequency spectrum graph
    const int nFreqs = nMonths / 2;
    TGraph* fftGraph = new TGraph(nFreqs);
    fftGraph->SetTitle("Frequency Spectrum (Peak Period Analysis)");

    // Fill FFT graph with period on x-axis
    const double samplingRate = 12.0; // 12 samples per year
    for (int i = 0; i < nFreqs; i++) {
        double freq = i * (samplingRate / nMonths); // frequency in cycles per year
        double period = (freq > 0) ? 1.0 / freq : 0; // period in years
        double magnitude = fft->GetBinContent(i + 1) / nMonths;
        fftGraph->SetPoint(i, period, magnitude);
    }

    // Create and set up canvas
    TCanvas* canvas = new TCanvas("canvas", "Temperature Analysis", 1200, 1000);
    canvas->Divide(1, 2);

    // Plot original time series
    canvas->cd(1);
    gr->Draw("AL");
    gr->SetLineColor(kBlue);
    gr->SetLineWidth(2);
    gr->GetXaxis()->SetTitle("Year");
    gr->GetYaxis()->SetTitle("Temperature Deviation (C)");
    gr->GetXaxis()->SetRangeUser(startYear, endYear);

    // Plot FFT result
    canvas->cd(2);
    fftGraph->Draw("AL");
    fftGraph->SetLineColor(kRed);
    fftGraph->SetLineWidth(2);
    fftGraph->GetXaxis()->SetTitle("Period (years)");
    fftGraph->GetYaxis()->SetTitle("Magnitude");
    gPad->SetLogx(true);
    
    fftGraph->GetXaxis()->SetRangeUser(1.0 / 12.0, 50);

    // Add explanation text
    TPaveText* pt = new TPaveText(0.6, 0.7, 0.95, 0.95, "NDC");
    pt->SetFillColor(0);
    pt->AddText("How to interpret peaks:");
    pt->AddText("- X-axis shows cycle length");
    pt->AddText("- Y-axis shows strength of cycle");
    pt->AddText("- Larger peak = stronger cycle");
    pt->AddText("Common patterns to look for:");
    pt->AddText("- 1 year: Annual cycle");
    pt->AddText("- 2-7 years: El Ni#tilde{n}o cycles");
    pt->AddText("- 11 years: Solar cycle");
    canvas->cd(2);
    pt->Draw();

    canvas->Update();
    canvas->SaveAs("fourier_analysis.pdf");

    // Clean up
    delete tempHist;
    delete fft;
    delete gr;
    delete fftGraph;
    delete pt;
    delete canvas;
}

int main() {
    performFourierAnalysis();
    return 0;
}