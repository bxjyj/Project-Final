#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "HashMap.h"
#include "Map.h"
#include "entryWindow.h"
#include "resultsWindow.h"
#include <tuple>
#include <algorithm>

using namespace std::chrono;
using namespace std;

void openFile(HashMap& hashMap, const string& filename) {
    //int lineCount = 0;
    ifstream file(filename);
    string line, state, city, shape, duration, year;
    auto startHashMap = steady_clock::now();
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            istringstream ss(line);
            if (getline(ss, city, ',') && getline(ss, state, ',') &&
                getline(ss, shape, ',') && getline(ss, duration, ',') &&
                getline(ss, year, ',')) {
                string combined = "State: " + state + ", City: " + city + ", Shape: " + shape + ", Duration: " + duration + ", Year: " + year;
                string uniqueKey = city + state + shape + duration + year;
                hashMap.insert(uniqueKey, combined);
            }
        }
        file.close();
    }
    else {
        cerr << "failed to open " << filename << endl;
        return;
    }
    auto stopHashMap = steady_clock::now();
    auto durationHashMap = duration_cast<milliseconds>(stopHashMap - startHashMap);
    cout << "Inserting data into HashMap took " << durationHashMap.count() << " milliseconds." << endl;
}

int main() {
    sf::Font font;
    font.loadFromFile("../files/font.ttf");

    int width = 1500;
    int height = 1000;

    sf::Text topText;
    topText.setFont(font);
    topText.setCharacterSize(50);
    topText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    topText.setOutlineColor(sf::Color::Black);
    topText.setOutlineThickness(3);
    topText.setFillColor(sf::Color::White);
    topText.setPosition(width / 2.0f, height / 8.0f);
    topText.setOrigin(topText.getGlobalBounds().width / 2.0f, 0);

    sf::Text output; // outputs map
    output.setFont(font);
    output.setStyle(sf::Text::Bold);
    output.setFillColor(sf::Color::White);
    output.setCharacterSize(30);
    output.setPosition(width/ 4.0f, height / 5.0f + 14);
    output.setOrigin(output.getLocalBounds().width / 2.0f, 0);

    sf::Text outputHash; // outputs hashMap
    outputHash.setFont(font);
    outputHash.setStyle(sf::Text::Bold);
    outputHash.setFillColor(sf::Color::White);
    outputHash.setCharacterSize(12);
    outputHash.setPosition(width / 1.8f, height / 5.0f + 14);
    outputHash.setOrigin(outputHash.getLocalBounds().width / 2.0f, 0);

    sf::Texture ufoImage2; // sets the background image
    ufoImage2.loadFromFile("../files/images/ufoResults.png");

    sf::Sprite ufo;
    ufo.setTexture(ufoImage2);
    ufo.setPosition(width / 2.0f, height / 2.0f - 75);
    ufo.setOrigin(ufo.getLocalBounds().width / 2, ufo.getLocalBounds().height / 2.35);
    ufo.setScale(2, 2);
    ufo.setColor(sf::Color(255, 255, 255, 128));

    // Create the Back button
    sf::Vector2f buttonSize(150, 50);
    Button backButton(buttonSize, sf::Vector2f(width - 200, height - 100), "Back", font);


    // TODO: LOAD DATA FROM CSV TO THE DATA STRUCTURES
    // TODO: OUTPUT THIS INTO THE SECOND PAGE SO THAT THE USER CAN READ IT

    auto start = steady_clock::now();
    HashMap hashMap(1000);
    auto startMap = steady_clock::now();
    // TODO : UNCOMMENT WHEN TRANSFERRING TO VSTUDIO
    //Map customMap;

    auto stopMap = steady_clock::now();
    auto durationMap = duration_cast<milliseconds>(stopMap - startMap);
    cout << "Inserting Map data took " << durationMap.count() << " milliseconds." << endl;
    openFile(hashMap, "../ufo_sightings.csv");
    auto stop = steady_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Inserting total data took " << duration.count() << " milliseconds." << endl;

    string hashMapTime = "";
    string mapTime = "";
    string strHashMap = "";
    string strMap = "Map";

    // TODO: figure out how to make it loop
    tuple<string, string, bool> entry = createEntryWindow();
    resultsWindow(hashMap, entry);

}
