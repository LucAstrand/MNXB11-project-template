void root_macro() {
    gSystem->AddIncludePath("-I./include");

    gROOT->ProcessLine(".L src/measurement.cxx+");
    gROOT->ProcessLine(".L src/writeTree.cxx+");
    gROOT->ProcessLine("write(\"/home/ad6224sh/git/MNXB11-project/baredata_smhi-opendata_1_53430_20231007_155558_Lund.csv\")");

    gROOT->ProcessLine(".L src/yr_avg_temp.cxx+");
    gROOT->ProcessLine("yr_avg_temp(\"1900-01-01\",\"2022-01-01\")");
}