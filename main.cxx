
#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "date.h"

using namespace date;
using namespace std::chrono;

int main(int agc, char *argv[]r) {
  io::CSVReader<4, io::trim_chars<>, io::no_quote_escape<','>> in("./datasets/test.csv");
  in.read_header(io::ignore_extra_column, "day", "year", "month", "measurement");
  int day, year, month; 
  double measurement;
  while (in.read_row(day, year, month, measurement)) {
        std::cout << "Day: " << day << ", Year: " << year << 
        ", Month: " << month << ", Measurement: " << measurement << std::endl;
  }
  return 0;
}
