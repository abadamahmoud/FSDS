#include "FileOperations.h"
#include <fstream>
#include <sstream>
#include <cstring> // For strtok and strcmp
#include <iostream>
#include <vector>
#include <algorithm> // Include for std::remove_if

/*struct TempRecord
{
     char date[11]; // dd-mm-yyyy
     int temp;
};

struct CityRecord
{
     char city[20];
     TempRecord tempRecords[20];
     int nbTempRecords;
};
*/
const char delimiters[] = " \t\n,;.=\"()_{}<>!?&-$*=+:";

namespace FileOperations
{

     void printFileContentCharByChar(const std::string &filename)
     {
          std::ifstream file(filename);
          if (!file.is_open())
          {
               std::cerr << "Error: Cannot open file " << filename << std::endl;
               return;
          }

          std::cout << "======================================\n";
          char ch;
          while (file.get(ch))
          {
               std::cout << ch;
          }
          std::cout << "\n======================================\n";
          file.close();
     }

     void printFileContentLineByLine(const std::string &filename)
     {
          std::ifstream file(filename);
          if (!file.is_open())
          {
               std::cerr << "Error: Cannot open file " << filename << std::endl;
               return;
          }

          std::cout << "======================================\n";
          std::string line;
          while (std::getline(file, line))
          {
               std::cout << line << '\n';
          }
          std::cout << "======================================\n";
          file.close();
     }

     void appendFileContents(const std::string &fileToAppend, const std::string &sourceFile)
     {
          std::ofstream outFile(fileToAppend, std::ios::app);
          std::ifstream inFile(sourceFile);

          if (!outFile.is_open() || !inFile.is_open())
          {
               std::cerr << "Error opening one or more files.\n";
               return;
          }

          std::string line;
          outFile << "\n"; // Separate content
          while (std::getline(inFile, line))
          {
               outFile << line << '\n';
          }

          std::cout << "File append complete.\n";
          outFile.close();
          inFile.close();
     }

     void mergeFiles(const std::string &file1, const std::string &file2, const std::string &resultFile)
     {
          std::ofstream result(resultFile);
          std::ifstream file1Stream(file1);
          std::ifstream file2Stream(file2);

          if (!result.is_open() || !file1Stream.is_open() || !file2Stream.is_open())
          {
               std::cerr << "Error opening one or more files.\n";
               return;
          }

          std::cout << "======================================\n";

          std::string line;
          while (std::getline(file1Stream, line))
          {
               result << line << '\n';
          }

          result << "\n"; // Separate the files

          while (std::getline(file2Stream, line))
          {
               result << line << '\n';
          }

          std::cout << "File merging complete.\n";

          result.close();
          file1Stream.close();
          file2Stream.close();
     }

     int countWordOccurrencesInLine(const std::string &word, const std::string &line)
     {
          int count = 0;
          char lineCStr[line.size() + 1];
          std::strcpy(lineCStr, line.c_str());

          char *token = std::strtok(lineCStr, delimiters);
          while (token != nullptr)
          {
               if (word == token)
               {
                    count++;
               }
               token = std::strtok(nullptr, delimiters);
          }

          return count;
     }

     int countOccurrences(const std::string &word, const std::string &filename)
     {
          std::ifstream file(filename);
          if (!file.is_open())
          {
               std::cerr << "Error: Cannot open file " << filename << std::endl;
               return -1;
          }

          std::string line;
          int totalOccurrences = 0;

          while (std::getline(file, line))
          {
               totalOccurrences += countWordOccurrencesInLine(word, line);
          }

          file.close();
          return totalOccurrences;
     }

     int countLines(const std::string &filename)
     {
          std::ifstream file(filename);
          if (!file.is_open())
          {
               std::cerr << "Error: Cannot open file " << filename << std::endl;
               return -1;
          }

          int lineCount = 0;
          std::string line;
          while (std::getline(file, line))
          {
               lineCount++;
          }

          file.close();
          return lineCount;
     }

     int countCharacters(const std::string &filename)
     {
          std::ifstream file(filename);
          if (!file.is_open())
          {
               std::cerr << "Error: Cannot open file " << filename << std::endl;
               return -1;
          }

          int charCount = 0;
          char c;
          while (file.get(c))
          {
               charCount++;
          }

          file.close();
          return charCount;
     }

     bool wordExists(const std::string &word, const std::string &filename)
     {
          std::ifstream file(filename);
          if (!file.is_open())
          {
               std::cerr << "Error: Cannot open file " << filename << std::endl;
               return false;
          }

          std::string line;
          while (std::getline(file, line))
          {
               if (countWordOccurrencesInLine(word, line) > 0)
               {
                    return true;
               }
          }

          file.close();
          return false;
     }

     void readFile(const std::string &fileName, std::vector<CityRecord> &cities)
     {
          std::ifstream inFile(fileName, std::ios::binary);
          if (!inFile)
          {
               std::cerr << "Error opening file for reading.\n";
               return;
          }

          cities.clear();
          CityRecord city;
          while (inFile.read(reinterpret_cast<char *>(&city), sizeof(city)))
          {
               cities.push_back(city);
          }

          nbCityRecords = static_cast<int>(cities.size());
          inFile.close();
          std::cout << "Successful reading\n";
     }

     void displayFile(const std::vector<CityRecord> &cities)
     {
          std::cout << "=================== File display ==============\n";
          for (const auto &city : cities)
          {
               std::cout << city.city << " has the following temp records:\n";
               for (const auto &record : city.tempRecords)
               {
                    std::cout << "\t Date: " << record.date << "; Temp: " << record.temp << "\n";
               }
          }
     }

     // Encrypt a file by applying the encryption key on each character
     void encrypt_file(const std::string &inputFile, const std::string &outputFile, const std::string &key)
     {
          std::ifstream input(inputFile);
          std::ofstream output(outputFile);

          if (!input.is_open())
          {
               std::cerr << "Error opening the input file." << std::endl;
               exit(1);
          }

          if (!output.is_open())
          {
               std::cerr << "Error opening the output file." << std::endl;
               exit(1);
          }

          int keyLength = key.length();
          int i = 0;
          char ch;

          // Encrypt the file
          while (input.get(ch))
          {
               ch += key[i % keyLength]; // Encrypt by adding the key char
               i++;
               output.put(ch); // Write the encrypted character to the output file
          }

          // Close the files
          input.close();
          output.close();

          std::cout << "File encryption complete." << std::endl;
     }

     // Encrypt file line by line, applying the key character by character
     void encrypt_file_line_by_line(const std::string &inputFile, const std::string &outputFile, const std::string &key)
     {
          std::ifstream input(inputFile);
          std::ofstream output(outputFile);

          if (!input.is_open())
          {
               std::cerr << "Error opening the input file." << std::endl;
               exit(1);
          }

          if (!output.is_open())
          {
               std::cerr << "Error opening the output file." << std::endl;
               exit(1);
          }

          std::string line;
          int j = 0;

          // Read and encrypt each line from the input file
          while (std::getline(input, line))
          {
               int i = 0;

               // Encrypt each character by adding the corresponding key character
               while (i < line.length())
               {
                    line[i] += key[j]; // Add key char
                    j++;               // Move to the next character in the key
                    i++;               // Move to the next character in the line

                    // Reset key index if it reaches the end of the key
                    if (key[j] == '\0')
                    {
                         j = 0; // Reset to the beginning of the key
                    }
               }

               output << line << std::endl; // Write the encrypted line to the output file
          }

          // Close the files
          input.close();
          output.close();

          std::cout << "File encryption complete." << std::endl;
     }
     // Decrypt a file by applying the decryption key on each character
     void decrypt_file(const std::string &inputFile, const std::string &outputFile, const std::string &key)
     {
          std::ifstream input(inputFile);
          std::ofstream output(outputFile);

          if (!input.is_open())
          {
               std::cerr << "Error opening the input file." << std::endl;
               exit(1);
          }

          if (!output.is_open())
          {
               std::cerr << "Error opening the output file." << std::endl;
               exit(1);
          }

          int keyLength = key.length();
          int i = 0;
          char ch;

          // Decrypt the file
          while (input.get(ch))
          {
               ch -= key[i % keyLength]; // Decrypt by subtracting the key char
               i++;
               output.put(ch); // Write the decrypted character to the output file
          }

          // Close the files
          input.close();
          output.close();

          std::cout << "File decryption complete." << std::endl;
     }

     // Decrypt file line by line, applying the key character by character
     void decrypt_file_line_by_line(const std::string &inputFile, const std::string &outputFile, const std::string &key)
     {
          std::ifstream input(inputFile);
          std::ofstream output(outputFile);

          if (!input.is_open())
          {
               std::cerr << "Error opening the input file." << std::endl;
               exit(1);
          }

          if (!output.is_open())
          {
               std::cerr << "Error opening the output file." << std::endl;
               exit(1);
          }

          std::string line;
          int j = 0;

          // Read and decrypt each line from the input file
          while (std::getline(input, line))
          {
               int i = 0;

               // Decrypt each character by subtracting the corresponding key character
               while (i < line.length())
               {
                    line[i] -= key[j]; // Subtract key char
                    j++;               // Move to the next character in the key
                    i++;               // Move to the next character in the line

                    // Reset key index if it reaches the end of the key
                    if (key[j] == '\0')
                    {
                         j = 0; // Reset to the beginning of the key
                    }
               }

               output << line << std::endl; // Write the decrypted line to the output file
          }

          // Close the files
          input.close();
          output.close();

          std::cout << "File decryption complete." << std::endl;
     }

     int nbCityRecords = 0;

     void addCityRecord(const std::string &fileName, const CityRecord &city)
     {
          std::ofstream outFile(fileName, std::ios::binary | std::ios::app);
          if (!outFile)
          {
               std::cerr << "Error opening file for writing.\n";
               return;
          }

          outFile.write(reinterpret_cast<const char *>(&city), sizeof(city));
          outFile.close();
          std::cout << "The new record has been added successfully\n";
     }

     void addNewTempRecord(const std::string &fileName, std::vector<CityRecord> &cities,
                           const std::string &givenCity, const std::string &newDate, int newTemp)
     {
          for (auto &city : cities)
          {
               if (city.city == givenCity)
               {
                    city.tempRecords.push_back({newDate, newTemp});
                    break;
               }
          }

          std::ofstream outFile(fileName, std::ios::binary | std::ios::trunc);
          if (!outFile)
          {
               std::cerr << "Error opening file for writing.\n";
               return;
          }

          for (const auto &city : cities)
          {
               outFile.write(reinterpret_cast<const char *>(&city), sizeof(city));
          }
          outFile.close();
          std::cout << "The new temperature record has been added successfully\n";
     }

     int minTempCity(const std::vector<CityRecord> &cities, const std::string &cityName)
     {
          int minTemp = 100;
          for (const auto &city : cities)
          {
               if (city.city == cityName)
               {
                    for (const auto &record : city.tempRecords)
                    {
                         if (record.temp < minTemp)
                         {
                              minTemp = record.temp;
                         }
                    }
               }
          }
          return minTemp;
     }

     int maxTempCity(const std::vector<CityRecord> &cities, const std::string &cityName)
     {
          int maxTemp = -100;
          for (const auto &city : cities)
          {
               if (city.city == cityName)
               {
                    for (const auto &record : city.tempRecords)
                    {
                         if (record.temp > maxTemp)
                         {
                              maxTemp = record.temp;
                         }
                    }
               }
          }
          return maxTemp;
     }

     int avgTempCity(const std::vector<CityRecord> &cities, const std::string &cityName)
     {
          int totalTemp = 0, count = 0;
          for (const auto &city : cities)
          {
               if (city.city == cityName)
               {
                    for (const auto &record : city.tempRecords)
                    {
                         totalTemp += record.temp;
                         ++count;
                    }
               }
          }
          return count == 0 ? -1 : totalTemp / count;
     }

     void updateTemp(const std::string &fileName, std::vector<CityRecord> &cities,
                     const std::string &cityName, const std::string &date, int newTemp)
     {
          for (auto &city : cities)
          {
               if (city.city == cityName)
               {
                    for (auto &record : city.tempRecords)
                    {
                         if (record.date == date)
                         {
                              record.temp = newTemp;
                              break;
                         }
                    }
               }
          }

          std::ofstream outFile(fileName, std::ios::binary | std::ios::trunc);
          if (!outFile)
          {
               std::cerr << "Error opening file for writing.\n";
               return;
          }

          for (const auto &city : cities)
          {
               outFile.write(reinterpret_cast<const char *>(&city), sizeof(city));
          }
          outFile.close();
          std::cout << "The temperature record has been updated successfully\n";
     }

     void deleteTempRecord(const std::string &fileName, std::vector<CityRecord> &cities,
                           const std::string &cityName, const std::string &date)
     {
          for (auto &city : cities)
          {
               if (city.city == cityName)
               {
                    auto &records = city.tempRecords;
                    records.erase(std::remove_if(records.begin(), records.end(),
                                                 [&date](const TempRecord &record)
                                                 {
                                                      return record.date == date;
                                                 }),
                                  records.end());
                    break;
               }
          }

          std::ofstream outFile(fileName, std::ios::binary | std::ios::trunc);
          if (!outFile)
          {
               std::cerr << "Error opening file for writing.\n";
               return;
          }

          for (const auto &city : cities)
          {
               outFile.write(reinterpret_cast<const char *>(&city), sizeof(city));
          }
          outFile.close();
          std::cout << "The temperature record has been deleted successfully\n";
     }
}
