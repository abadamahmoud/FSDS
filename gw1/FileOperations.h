#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <vector> // Include vector for std::vector

namespace FileOperations
{
     // Function declarations
     void printFileContentCharByChar(const std::string &filename);
     void printFileContentLineByLine(const std::string &filename);
     void appendFileContents(const std::string &fileToAppend, const std::string &sourceFile);
     void mergeFiles(const std::string &file1, const std::string &file2, const std::string &resultFile);
     int countWordOccurrencesInLine(const std::string &word, const std::string &line);
     int countOccurrences(const std::string &word, const std::string &filename);
     int countLines(const std::string &filename);
     int countCharacters(const std::string &filename);
     bool wordExists(const std::string &word, const std::string &filename);
     void encrypt_file(const std::string &inputFile, const std::string &outputFile, const std::string &key);
     void encrypt_file_line_by_line(const std::string &inputFile, const std::string &outputFile, const std::string &key);
     void decrypt_file(const std::string &inputFile, const std::string &outputFile, const std::string &key);
     void decrypt_file_line_by_line(const std::string &inputFile, const std::string &outputFile, const std::string &key);
     // Define TempRecord struct
     struct TempRecord
     {
          std::string date; // dd-mm-yyyy
          int temp;         // Temperature value
     };

     // Define CityRecord struct
     struct CityRecord
     {
          std::string city;                    // City name
          std::vector<TempRecord> tempRecords; // List of temperature records for the city
     };

     // Extern variable declaration
     extern int nbCityRecords;

     // Function declarations for working with CityRecord and file operations
     void addCityRecord(const std::string &fileName, const CityRecord &city);
     void readFile(const std::string &fileName, std::vector<CityRecord> &cities);
     void displayFile(const std::vector<CityRecord> &cities);
     void addNewTempRecord(const std::string &fileName, std::vector<CityRecord> &cities,
                           const std::string &givenCity, const std::string &newDate, int newTemp);
     int minTempCity(const std::vector<CityRecord> &cities, const std::string &cityName);
     int maxTempCity(const std::vector<CityRecord> &cities, const std::string &cityName);
     int avgTempCity(const std::vector<CityRecord> &cities, const std::string &cityName);
     void updateTemp(const std::string &fileName, std::vector<CityRecord> &cities,
                     const std::string &cityName, const std::string &date, int newTemp);
     void deleteTempRecord(const std::string &fileName, std::vector<CityRecord> &cities,
                           const std::string &cityName, const std::string &date);
}

#endif // FILE_OPERATIONS_H
