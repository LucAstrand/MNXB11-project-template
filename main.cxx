
#include <iostream>
#include <lyra/lyra.hpp>
#include <string>
int main(int argc, char *argv[]) {
  std::string inputFile;
  bool showHelp = false; // Flag for showing help message

  // Create a command line parser using Lyra
  auto cli = lyra::cli()
      | lyra::help(showHelp).description("This program will help you upload and proccess the CSV files.") // Help command -h
      | lyra::opt(inputFile, "input_file") // input file -i
          ["-i"]["--input-file"]("Name of the input CSV file");

  auto responce = cli.parse({argc, argv});

  // Check if the responce is made
  if (!responce) {
        std::cerr << "Error: " << responce.message() << std::endl;
        return 1;
    }
  
  if (showHelp) {
    std::cout << cli << std::endl;
    return 0; 
    }

  // Check if the inputFile is provided
  if (inputFile.empty()) {
      std::cerr << "Error: No input file provided. Use -i or --input-file to specify the file." << std::endl;
      return 1;
  }

  // Confirms the inputFile
  std::cout << "Input file: " << inputFile << std::endl;

  return 0;
}
