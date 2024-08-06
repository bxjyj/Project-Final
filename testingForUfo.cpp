#include <iostream>
#include <fstream>
#include <sstream>
#include "HashMap.h"
#include "Map.h"
#include <chrono>
#include <algorithm>
#include <string>
#include "UFO.h"
#include <vector>
using namespace std::chrono;
using namespace std;
// for the clock timing 
// https://stackoverflow.com/questions/31552193/difference-between-steady-clock-vs-system-clock

void displayMenu() {
	cout << endl;
	cout << "Menu:" << endl;
	cout << "1. Insert" << endl;
	cout << "2. Search by City" << endl;
	cout << "3. Search by Shape" << endl;
	cout << "4. Search by Year" << endl;
	cout << "5. Search by State" << endl;
	cout << "6. Remove" << endl;
	cout << "7. Print" << endl;
	cout << "8. Exit" << endl;
	cout << "Enter your choice: ";
}
void menu(HashMap& hashMap, Map& customMap) {
	int choice;
	string state, city, shape, duration, year, combined, input;
	do {
		displayMenu();
		cin >> input;
        cin.ignore();
		choice = atoi(input.c_str());
		switch (choice) {
		case 1: { //insert
			cout << "Enter state: ";
			cin >> state;
			cin.ignore();
			cout << "Enter city: ";
			getline(cin, city);
			cout << "Enter shape: ";
			getline(cin, shape);
			while (true) {
				cout << "Enter duration: ";
				getline(cin, duration);
				try {
					stof(duration);
					break;
				}
				catch (invalid_argument) {
					cout << "Enter a number" << endl;
				}
			}
			while (true) {
				cout << "Enter year: ";
				getline(cin, year);
				try {
					stoi(year);
					break;
				}
				catch (invalid_argument) {
					cout << "Enter a number" << endl;
				}
			}
			combined = "State: " + state + ", City: " + city + ", Shape: " + shape + ", Duration: " + duration + ", Year: " + year;

			auto startInsertHashMap = steady_clock::now();
			if (hashMap.insert(city + state, combined)) {
				cout << "Inserted into HashMap: " << combined << endl;
			}
			else {
				cout << "Failed to insert into HashMap: " << combined << endl;
			}
			auto stopInsertHashMap = steady_clock::now();
			auto durationInsertHashMap = duration_cast<milliseconds>(stopInsertHashMap - startInsertHashMap);
			cout << "HashMap insert took " << durationInsertHashMap.count() << " milliseconds" << endl;

			auto startInsertCustomMap = steady_clock::now();
			customMap.Insert(city, state, shape, stof(duration), stoi(year));
			auto stopInsertCustomMap = steady_clock::now();
			auto durationInsertCustomMap = duration_cast<milliseconds>(stopInsertCustomMap - startInsertCustomMap);
			cout << "Custom Map insert took " << durationInsertCustomMap.count() << " milliseconds" << endl;

			break;
		}

		case 2: { //search city
			cout << "Enter city: ";
			cin >> city;
            cin.ignore();

			auto startCityHashMap = steady_clock::now();
			hashMap.searchCity(city);
			auto stopCityHashMap = steady_clock::now();
			auto durationCityHashMap = duration_cast<milliseconds>(stopCityHashMap - startCityHashMap);
			cout << "HashMap search for city took " << durationCityHashMap.count() << " milliseconds." << endl;

			cout << "Press any button to continue" << endl;
			cin.ignore();
			cin.get();
			auto startCityCustomMap = steady_clock::now();
			customMap.SearchCity(city, state);  // Update state value
			auto stopCityCustomMap = steady_clock::now();
			auto durationCityCustomMap = duration_cast<milliseconds>(stopCityCustomMap - startCityCustomMap);
			cout << "Custom Map search for city took " << durationCityCustomMap.count() << " milliseconds." << endl;

			break;
		}

		case 3: { //search shape
			cout << "Enter shape: ";
			cin >> shape;
            cin.ignore();

			auto startShapeHashMap = steady_clock::now();
			hashMap.searchShape(shape);
			auto stopShapeHashMap = steady_clock::now();
			auto durationShapeHashMap = duration_cast<milliseconds>(stopShapeHashMap - startShapeHashMap);
			cout << "HashMap search for shape took " << durationShapeHashMap.count() << " milliseconds." << endl;

			cout << "Press any button to continue" << endl;
			cin.ignore();
			cin.get();
			auto startShapeCustomMap = steady_clock::now();
			customMap.SearchShape(shape);
			auto stopShapeCustomMap = steady_clock::now();
			auto durationShapeCustomMap = duration_cast<milliseconds>(stopShapeCustomMap - startShapeCustomMap);
			cout << "Custom Map search for shape took " << durationShapeCustomMap.count() << " milliseconds." << endl;

			break;
		}

		case 4: { //search year
			while (true) {
				cout << "Enter year: ";
				cin >> year;
				try {
					stoi(year);
					break;
				}
				catch (invalid_argument) {
					cout << "Enter a number" << endl;
				}
			}

			auto startYearHashMap = steady_clock::now();
			hashMap.searchYear(year);
			auto stopYearHashMap = steady_clock::now();
			auto durationYearHashMap = duration_cast<milliseconds>(stopYearHashMap - startYearHashMap);
			cout << "HashMap search for year took " << durationYearHashMap.count() << " milliseconds." << endl;

			cout << "Press any button to continue" << endl;
			cin.ignore();
			cin.get();
			int yearInt = stoi(year);
			auto startYearCustomMap = steady_clock::now();
			customMap.SearchYear(yearInt);
			auto stopYearCustomMap = steady_clock::now();
			auto durationYearCustomMap = duration_cast<milliseconds>(stopYearCustomMap - startYearCustomMap);
			cout << "Custom Map search for year took " << durationYearCustomMap.count() << " milliseconds." << endl;

			break;
		}

		case 5: { //search state
			cout << "Enter state: ";
			cin >> state;
            cout << "\"" << state << "\"" << endl;


			auto startStateHashMap = steady_clock::now();
			hashMap.searchState(state);
			auto stopStateHashMap = steady_clock::now();
			auto durationStateHashMap = duration_cast<milliseconds>(stopStateHashMap - startStateHashMap);
			cout << "HashMap search for state took " << durationStateHashMap.count() << " milliseconds." << endl;

			cout << "Press any button to continue" << endl;
			cin.ignore();
			cin.get();
			auto startStateCustomMap = steady_clock::now();
			customMap.SearchState(state);
			auto stopStateCustomMap = steady_clock::now();
			auto durationStateCustomMap = duration_cast<milliseconds>(stopStateCustomMap - startStateCustomMap);
			cout << "Custom Map search for state took " << durationStateCustomMap.count() << " milliseconds." << endl;

			break;
		}

		case 6: { //remove
			cout << "Enter state: ";
			cin >> state;
            cin.ignore();
			cout << "Enter city: ";
			cin >> city;
            cin.ignore();

			auto startRemoveHashMap = steady_clock::now();
			if (hashMap.remove(city)) {
				cout << "Removed from HashMap: " << state << ", " << city << endl;
			}
			else {
				cout << "Couldn't find in HashMap: " << state << ", " << city << endl;
			}
			auto stopRemoveHashMap = steady_clock::now();
			auto durationRemoveHashMap = duration_cast<milliseconds>(stopRemoveHashMap - startRemoveHashMap);
			cout << "HashMap remove took " << durationRemoveHashMap.count() << " milliseconds." << endl;

			cout << "Press any button to continue" << endl;
			cin.ignore();
			cin.get();
			auto startRemoveCustomMap = steady_clock::now();
			int count = customMap.Remove(city, state);
			auto stopRemoveCustomMap = steady_clock::now();
			auto durationRemoveCustomMap = duration_cast<milliseconds>(stopRemoveCustomMap - startRemoveCustomMap);
			cout << "Custom Map remove took " << durationRemoveCustomMap.count() << " milliseconds." << endl;
			cout << count << " records removed from Custom Map." << endl;

			break;
		}

		case 7: { //print
			auto startPrintHashMap = steady_clock::now();
			hashMap.print();
			auto stopPrintHashMap = steady_clock::now();
			auto durationPrintHashMap = duration_cast<milliseconds>(stopPrintHashMap - startPrintHashMap);
			cout << "HashMap print took " << durationPrintHashMap.count() << " milliseconds." << endl;

			cout << "Press any button to continue" << endl;
			cin.ignore();
			cin.get();
			auto startPrintCustomMap = steady_clock::now();
			customMap.Print();
			auto stopPrintCustomMap = steady_clock::now();
			auto durationPrintCustomMap = duration_cast<milliseconds>(stopPrintCustomMap - startPrintCustomMap);
			cout << "Custom Map print took " << durationPrintCustomMap.count() << " milliseconds." << endl;

			break;
		}

		case 8: //exit
			cout << "Goodbye" << endl;
			break;

		default:
			cout << "Invalid choice" << endl;
			break;
		}
	} while (choice != 8);
}

/*
int main() {
	auto start = steady_clock::now();
	HashMap hashMap(1000);
	auto startMap = steady_clock::now();
	Map customMap;
	auto stopMap = steady_clock::now();
	auto durationMap = duration_cast<milliseconds>(stopMap - startMap);
	cout << "Inserting Map data took " << durationMap.count() << " milliseconds." << endl;
	openFile(hashMap, "../ufo_sightings.csv");
	cout << "2" << endl;
	auto stop = steady_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Inserting total data took " << duration.count() << " milliseconds." << endl;

	menu(hashMap, customMap);
	return 0;
}
*/


/*
void comparePerformance(HashMap& hashMap, Map& customMap) {
	auto startHashMap = steady_clock::now();
	hashMap.print();
	auto stopHashMap = steady_clock::now();
	auto durationHashMap = duration_cast<milliseconds>(stopHashMap - startHashMap);
	cout << "HashMap print took " << durationHashMap.count() << " milliseconds." << endl;

	auto startCustomMap = steady_clock::now();
	customMap.Print();
	auto stopCustomMap = steady_clock::now();
	auto durationCustomMap = duration_cast<milliseconds>(stopCustomMap - startCustomMap);
	cout << "Custom Map print took " << durationCustomMap.count() << " milliseconds." << endl;
}*/

