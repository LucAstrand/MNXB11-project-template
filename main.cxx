
#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "date.h"

using namespace date;
using namespace std::chrono;

int main(int argc, char *argv[]) {
  const std::string csv_file = {"./datasets/test.csv"}
  io::CSVReader<4> in(csv_file);
  in.read_header(io::ignore_extra_column, "date", "hour", "temperature", "quality");
  date::year_month_day date;
  int year, month, day; 
  double temperature;
  char quality;
  while(in.read_row(date, hour, temperature, quality)){
    // do stuff with the data
  }
  return 0;
}
