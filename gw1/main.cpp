#include <iostream>
#include <string>
#include <vector>
#include "FileOperations.h"

using namespace std;

void displayMenu()
{
     cout << "\n===== File Operations Menu =====" << endl;
     cout << "1. Print file content character by character" << endl;
     cout << "2. Print file content line by line" << endl;
     cout << "3. Append file contents" << endl;
     cout << "4. Merge two files" << endl;
     cout << "5. Count word occurrences in a file" << endl;
     cout << "6. Count occurrences of a word in a file" << endl;
     cout << "7. Count lines in a file" << endl;
     cout << "8. Count characters in a file" << endl;
     cout << "9. Check if a word exists in a file" << endl;
     cout << "10. Encrypt a file" << endl;
     cout << "11. Decrypt a file" << endl;
     cout << "12. Add new temperature record" << endl;
     cout << "13. Display city records" << endl;
     cout << "14. Update a temperature record" << endl;
     cout << "15. Delete a temperature record" << endl;
     cout << "16. Find minimum temperature in a city" << endl;
     cout << "17. Find maximum temperature in a city" << endl;
     cout << "18. Find average temperature in a city" << endl;
     cout << "19. Exit" << endl;
     cout << "Please choose an option (1-19): ";
}

void executeOption(int choice)
{
     vector<FileOperations::CityRecord> cities;
     string filename, fileToAppend, resultFile, word, cityName, date;
     int newTemp;
     int minTemp, maxTemp, avgTemp; // Declare the variables outside the switch statement

     switch (choice)
     {
     case 1:
          cout << "Enter filename: ";
          cin >> filename;
          FileOperations::printFileContentCharByChar(filename);
          break;
     case 2:
          cout << "Enter filename: ";
          cin >> filename;
          FileOperations::printFileContentLineByLine(filename);
          break;
     case 3:
          cout << "Enter file to append: ";
          cin >> fileToAppend;
          cout << "Enter source file: ";
          cin >> filename;
          FileOperations::appendFileContents(fileToAppend, filename);
          break;
     case 4:
          cout << "Enter first file to merge: ";
          cin >> filename;
          cout << "Enter second file to merge: ";
          cin >> fileToAppend;
          cout << "Enter result file: ";
          cin >> resultFile;
          FileOperations::mergeFiles(filename, fileToAppend, resultFile);
          break;
     case 5:
          cout << "Enter word to search: ";
          cin >> word;
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Occurrences: " << FileOperations::countOccurrences(word, filename) << endl;
          break;
     case 6:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Lines count: " << FileOperations::countLines(filename) << endl;
          break;
     case 7:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Character count: " << FileOperations::countCharacters(filename) << endl;
          break;
     case 8:
          cout << "Enter word to check: ";
          cin >> word;
          cout << "Enter filename: ";
          cin >> filename;
          cout << (FileOperations::wordExists(word, filename) ? "Word found!" : "Word not found!") << endl;
          break;
     case 9:
          cout << "Enter filename to encrypt: ";
          cin >> filename;
          cout << "Enter output encrypted filename: ";
          cin >> resultFile;
          cout << "Enter encryption key: ";
          cin >> word;
          FileOperations::encrypt_file(filename, resultFile, word);
          break;
     case 10:
          cout << "Enter filename to decrypt: ";
          cin >> filename;
          cout << "Enter output decrypted filename: ";
          cin >> resultFile;
          cout << "Enter decryption key: ";
          cin >> word;
          FileOperations::decrypt_file(filename, resultFile, word);
          break;
     case 11:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Enter city name: ";
          cin >> cityName;
          cout << "Enter date (dd-mm-yyyy): ";
          cin >> date;
          cout << "Enter temperature: ";
          cin >> newTemp;
          FileOperations::addNewTempRecord(filename, cities, cityName, date, newTemp);
          break;

     case 12:
          cout << "Enter filename to display city records: ";
          cin >> filename;
          FileOperations::readFile(filename, cities);
          FileOperations::displayFile(cities);
          break;
     case 13:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Enter city name: ";
          cin >> cityName;
          cout << "Enter date (dd-mm-yyyy): ";
          cin >> date;
          cout << "Enter new temperature: ";
          cin >> newTemp;
          FileOperations::updateTemp(filename, cities, cityName, date, newTemp);
          break;
     case 14:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Enter city name: ";
          cin >> cityName;
          cout << "Enter date (dd-mm-yyyy): ";
          cin >> date;
          FileOperations::deleteTempRecord(filename, cities, cityName, date);
          break;
     case 15:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Enter city name: ";
          cin >> cityName;
          minTemp = FileOperations::minTempCity(cities, cityName);
          cout << "Minimum temperature in " << cityName << " is: " << minTemp << endl;
          break;
     case 16:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Enter city name: ";
          cin >> cityName;
          maxTemp = FileOperations::maxTempCity(cities, cityName);
          cout << "Maximum temperature in " << cityName << " is: " << maxTemp << endl;
          break;
     case 17:
          cout << "Enter filename: ";
          cin >> filename;
          cout << "Enter city name: ";
          cin >> cityName;
          avgTemp = FileOperations::avgTempCity(cities, cityName);
          cout << "Average temperature in " << cityName << " is: " << avgTemp << endl;
          break;
     case 18:
          cout << "Exiting program. Goodbye!" << endl;
          break;
     default:
          cout << "Invalid choice! Please choose a valid option (1-18)." << endl;
     }
}

int main()
{
     int choice;

     do
     {
          displayMenu();
          cin >> choice;
          executeOption(choice);
     } while (choice != 13);

     return 0;
}
