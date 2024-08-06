#pragma once
#include "Map.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class UFO
{
private:
	string city;
	string state;
	string shape;
	float duration;
	int year;
public:
	UFO();
	UFO(string c, string st, string sh, float d, int y);
	void ReadLine(istringstream& stream);
	string getCity();
	string getState();
	string getShape();
	float getDuration();
	int getYear();
	string FormatDuration();
	string Print();
	void Reset();
	int Hash(int buckets);
};


UFO::UFO() : city(""), state(""), shape(""), duration(0.0f), year(0) {}

UFO::UFO(string c, string st, string sh, float d, int y) : city(c), state(st), shape(sh), duration(d), year(y) {}

void UFO::ReadLine(istringstream& stream)
{
	// city, state, and shape are all strings, no special consideration necessary
	getline(stream, city, ',');
	getline(stream, state, ',');
	getline(stream, shape, ',');
    cout << "2" << endl;

    //duration and year are integers, use a token to get string then convert using stoi()
	string token = " ";
    getline(stream, token, ',');
    duration = std::stof(token);
    cout << "3" << endl;
    getline(stream, token, ',');
    year = std::stoi(token);

}

// Accessors
string UFO::getCity() { return city; }
string UFO::getState() { return state; }
string UFO::getShape() { return shape; }
float UFO::getDuration() { return duration; }
int UFO::getYear() { return year; }

string UFO::FormatDuration()
{
	string d = to_string(duration);
	// Remove trailing zeros
	d.erase(d.find_last_not_of('0') + 1, string::npos);
	// If string ends with a decimal point, pop it off
	if (d.back() == '.')
		d.pop_back();
	return d;
}

string UFO::Print()
{
	return "City: " + city + " | State: " + state + " | Shape: " + shape + " | Duration: " + FormatDuration() + " | Year: " + to_string(year);
}

void UFO::Reset() { city = ""; state = ""; shape = ""; duration = 0.0f; year = 0; }

int UFO::Hash(int buckets)
{
	return ((year * int(duration)) / city.size()) % buckets;
}
