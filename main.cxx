
#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "date.h"
#include "iso_week.h"

using namespace date;
using namespace std::chrono;

int main(int agc, char *argv[]r) {
  //Open CSV file and specify columns to read
  io::CSVReader<4, io::trim_chars<>, io::no_quote_escape<','>> in("./datasets/test.csv");
  in.read_header(io::ignore_extra_column, "day", "year", "month", "measurement");

  int day, year, month; 
  double measurement;

  //Read each row of the CSV file
  while (in.read_row(day, year, month, measurement)) {
    //Get the weekday that corresponds to the given date
    year_month_day ymd{date::year(year), date::month(month), date::day(day)};
    sys_days date = ymd;
    weekday wd = date::weekday(date);
    //Print the date with the corresponding weekday and measurement
    std::cout << "Date: " << ymd << ", Weekday: " << wd << ", Measurement: " << measurement << std::endl;
  }
  return 0;
}
