#pragma once
#include <iostream>
#include <vector>
#include "UFO.h"
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

class Map
{
private:
	UFO* sightings = new UFO[34];  // Our group number! :D
	int buckets = 34;
	int occupied = 0;
public:
	Map();
	~Map();
	void Rehash();
	void Insert(UFO& obj);
	void Insert(string& city, string& state, string& shape, float duration, int year);
	int Remove(string& city, string& state);
	string SearchCity(string& city);
	string SearchState(string& state);
	string SearchShape(string& shape);
	string SearchYear(int& year);
	string Print();
	double LoadFactor();
};


Map::Map() {
	ifstream inFile("../ufo_sightings.csv");

	if (inFile.is_open())
	{
        cout << "1" << endl;
		// Get header line and immediately throw it away
		string currLine;
		getline(inFile, currLine);

		while (getline(inFile, currLine))
		{
			istringstream stream(currLine);
			UFO newUFO;
			newUFO.ReadLine(stream);
			Insert(newUFO);
		}
	}
	else {
		cout << "An error has occurred!";
	}
	inFile.close();
}

Map::~Map() {
	delete[] sightings;
}

void Map::Rehash()
{
	UFO* oldSightings = new UFO[buckets];
	copy(sightings, sightings + buckets, oldSightings);
	delete[] sightings;
	sightings = new UFO[buckets * 2];
	occupied = 0;
	for (int i = 0; i < buckets; i++) {
		if (oldSightings[i].getState() != "") {
			Insert(oldSightings[i]);
		}
	}
	delete[] oldSightings;
	buckets *= 2;
}

void Map::Insert(UFO& obj) {
	if (LoadFactor() > 0.8)
		Rehash();
	int i = obj.Hash(buckets);
	while (sightings[i].getState() != "")
		i = (++i) % buckets;
	sightings[i] = obj;
	occupied++;
}

void Map::Insert(string& city, string& state, string& shape, float duration, int year) {
	UFO newUFO(city, state, shape, duration, year);
	Insert(newUFO);
}

int Map::Remove(string& city, string& state) {
	int count = 0;
	for (int i = 0; i < buckets; i++) {
		if (sightings[i].getCity() == city && sightings[i].getState() == state) {
			sightings[i].Reset();
			occupied--;
			count++;
		}
	}
	return count;
}

string Map::SearchCity(string& city) {
    int count = 0;
    string total;
    for (int i = 0; i < buckets; i++) {
        if (sightings[i].getCity() == city) {
            total += (sightings[i].Print() + '\n');
            count++;
        }
    }
    return total;
}

string Map::SearchState(string& state) {
	string total = "";
	for (int i = 0; i < buckets; i++) {
		if (sightings[i].getState() == state) {
            total += sightings[i].Print() + "\n";
		}
	}
	return total;
}

string Map::SearchShape(string& shape) {
	string total = "";
	for (int i = 0; i < buckets; i++) {
		if (sightings[i].getShape() == shape) {
            total += sightings[i].Print() + "\n";
		}
	}
	return total;
}

string Map::SearchYear(int& year) {
	string total = "";
	for (int i = 0; i < buckets; i++) {
		if (sightings[i].getYear() == year) {
            total += sightings[i].Print() + "\n";
		}
	}
	return total;
}

string Map::Print() {
    string total = "";
	for (int i = 0; i < buckets; i++) {
		if (sightings[i].getState() != "")
            total += sightings[i].Print() + "\n";
	}
    return total;
}

double Map::LoadFactor() { return occupied / buckets; }