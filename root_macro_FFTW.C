#include <TSystem.h>
#include <TString.h>
#include <TList.h>
#include <TObjArray.h>
#include <TObjString.h>

void root_macro_FFTW() {
    printf("Setting include paths and loading measurement.cxx and writeTree.cxx\n");
    gSystem->AddIncludePath("-I./include");

    gROOT->ProcessLine(".L src/measurement.cxx+");
    gROOT->ProcessLine(".L src/writeTree.cxx+");

    // Find the CSV file starting with "baredata"
    printf("Searching for CSV file starting with 'baredata'...\n");
    TString command = "ls baredata*.csv";
    TString result = gSystem->GetFromPipe(command);

    // Split the result into lines
    TObjArray* files = result.Tokenize("\n");

    // Check if any files were found
    if (files->GetEntries() > 0) {
        // Get the first file
        TString csvFileName = ((TObjString*)files->At(0))->GetString();
        printf("CSV file found: %s\n", csvFileName.Data());
        printf("Calling write function with CSV file...\n");
        gROOT->ProcessLine(Form("write(\"%s\")", csvFileName.Data()));
    } else {
        printf("Error: No CSV file starting with 'baredata' found in the current directory.\n");
        return;
    }

    printf("Loading and executing yr_avg_temp function...\n");
    gROOT->ProcessLine(".L src/yr_avg_temp.cxx+");
    gROOT->ProcessLine("yr_avg_temp(\"1900-01-01\",\"2022-01-01\")");

    printf("Loading and executing given_year_temp function...\n");
    gROOT->ProcessLine(".L src/given_year_temp.cxx+");
    gROOT->ProcessLine("given_year_temp(1998)");

    printf("Loading and executing outliers function...\n");
    gROOT->ProcessLine(".L src/outliers.cxx+");
    gROOT->ProcessLine("outliers(1800,2022)");

    printf("Loading and executing yr_low_high_temp function to generate temperature graph...\n");
    gROOT->ProcessLine(".L src/yr_low_high_temp.cxx+");
    gROOT->ProcessLine("generateTemperatureGraph();");

    printf("Loading and executing runFourier to generate fourier analysis graph...\n");
    gROOT->ProcessLine(".L src/runFourier.cxx+");
    gROOT->ProcessLine("performFourierAnalysis();");



    printf("Execution of root_macro completed.\n");
}