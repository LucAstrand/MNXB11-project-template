#include <TSystem.h>
#include <TString.h>
#include <TList.h>
#include <TObjArray.h>
#include <TObjString.h>

void root_macro() {
    gSystem->AddIncludePath("-I./include");

    gROOT->ProcessLine(".L src/measurement.cxx+");
    gROOT->ProcessLine(".L src/writeTree.cxx+");

    // Find the CSV file starting with "baredata"
    TString command = "ls baredata*.csv";
    TString result = gSystem->GetFromPipe(command);

    // Split the result into lines
    TObjArray* files = result.Tokenize("\n");

    // Check if any files were found
    if (files->GetEntries() > 0) {
        // Get the first file
        TString csvFileName = ((TObjString*)files->At(0))->GetString();
        gROOT->ProcessLine(Form("write(\"%s\")", csvFileName.Data()));
    } else {
        printf("Error: No CSV file starting with 'baredata' found in the current directory.\n");
        return;
    }

    gROOT->ProcessLine(".L src/yr_avg_temp.cxx+");
    gROOT->ProcessLine("yr_avg_temp(\"1900-01-01\",\"2022-01-01\")");

    gROOT->ProcessLine(".L src/outlier.cxx+");
    gROOT->ProcessLine("outlier(1800,2022)");
}