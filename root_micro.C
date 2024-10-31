void root_micro() {
    gROOT->ProcessLine(".L measurement.cxx+");
    gROOT->ProcessLine(".L write.cxx+");
    gROOT->ProcessLine("write(\"baredata_smhi-opendata_1_53430_20231007_155558_Lund.csv\")");

    gROOT->ProcessLine(".L yr_avg_temp.cxx+");
    gROOT->ProcessLine("yr_avg_temp(\"1900-01-01\",\"2022-01-01\")");
}