#include <measurement.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include "include/csv.h"
#include "include/date.h"



void writeTree(const char* filename, TTree *tree){

    std::string date_str, time_str;
    Double_t temp;
    Char_t airQ;

    // Create a CSV reader object
    io::CSVReader<4> reader(filename); 
    reader.read_header(io::ignore_extra_column, "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet");

    Measurement m;

    tree->Branch("Measurement", &m); // Store the entire measurement object, then each one will the leafs "Datum", "Tid (UTC)", "Lufttemperatur", "Kvalitet".

    while (reader.read_row(date_str, time_str, temp, airQ)) {
        
        // Combine date and time strings for parsing
        std::string datetime_str = date_str + " " + time_str;
        
        // Parse date and time 
        std::istringstream in{datetime_str};
        date::sys_time<std::chrono::seconds> tp;

        in >> date::parse("%Y-%m-%d %H:%M:%S", tp);

        if (in.fail()) {
            std::cerr << "Failed to parse date/time: " << datetime_str << "\n";
            continue;
        }

        // Extract year, month, day, hour, minute, and second components
        auto dp = date::floor<date::days>(tp);
        date::year_month_day ymd{dp};
        auto time = date::make_time(tp - dp);

        // Use the setter methods to set each value
        m.SetYear(static_cast<int>(ymd.year()));
        m.SetMonth(static_cast<unsigned>(ymd.month()));
        m.SetDay(static_cast<unsigned>(ymd.day()));
        m.SetHour(time.hours().count());
        m.SetMinute(time.minutes().count());
        m.SetSecond(time.seconds().count());
        m.SetTemperature(temp);
        m.SetAirQuality(airQ);

        // Fill the TTree with this entry
        tree->Fill();
    }

}

int write(const char* filename) {
    // Create your root file here
    TFile f("measurement_file.root","RECREATE");
    // Create your TTree here
    TTree *tree = new TTree("tree","measurement tree");
    writeTree(filename, tree);
    tree->Write();
    f.Close();
    std::cout << "Data written to measurement_file.root \n";
    return 0;
}

// int write(int argc, char *argv[]){
    
//     if (argc < 2) {
//         std::cerr << "Usage: " << argv[0] << " <CSV file>\n";
//         return 1;
//     }

//     const char* filename = argv[1];
//     // Create your root file here
//     TFile f("measurement_file.root","RECREATE");

//     // Create your TTree here
//     TTree *tree = new TTree("tree","measurement tree");

//     writeTree(filename, tree);

//     tree->Write();
//     f.Close();

//     std::cout << "Data written to measurement_file.root \n";

//     return 0;
// }