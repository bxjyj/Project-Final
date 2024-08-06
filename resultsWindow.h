#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "HashMap.h"
#include "Map.h"
#include "entryWindow.h"
#include <tuple>
#include <algorithm>

using namespace std::chrono;
using namespace std;

bool resultsWindow(HashMap &hashMap, Map& customMap, tuple<string, string, bool> &entry) {
    bool backClicked = false;

    sf::Font font;
    font.loadFromFile("../files/font.ttf");

    int width = 1500;
    int height = 1000;

    sf::Text topText;
    topText.setFont(font);
    topText.setCharacterSize(50);
    topText.setStyle(sf::Text::Bold);
    topText.setOutlineColor(sf::Color::Black);
    topText.setOutlineThickness(3);
    topText.setFillColor(sf::Color::White);
    topText.setPosition(width / 2.0f, height / 8.0f);
    topText.setOrigin(topText.getGlobalBounds().width / 2.0f, 0);

    sf::Text parameterPrompt; // display title and parameters
    parameterPrompt.setFont(font);
    parameterPrompt.setStyle(sf::Text::Bold);
    parameterPrompt.setFillColor(sf::Color::White);
    parameterPrompt.setCharacterSize(34);
    parameterPrompt.setPosition(width / 5.5f , height / 6.1f );
    parameterPrompt.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text output; // outputs map
    output.setFont(font);
    output.setStyle(sf::Text::Bold);
    output.setFillColor(sf::Color::White);
    output.setCharacterSize(30);
    output.setPosition(width / 3.0f, height / 5.0f + 34);
    output.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text outputHash; // outputs hashMap
    outputHash.setFont(font);
    outputHash.setStyle(sf::Text::Bold);
    outputHash.setFillColor(sf::Color::White);
    outputHash.setCharacterSize(12);
    outputHash.setPosition(width / 1.8f, height / 5.0f + 34);
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

    string hashMapTime = "";
    string mapTime = "";
    string strHashMap = "";
    string strMap = "Map";
    // makes the entry window

    string insertionDeletion;
    topText.setString("Searching for UFOs via " + get<0>(entry) + ": " + get<1>(entry));

    // TODO: OUTPUT THE TIME CALCULATIONS INTO THE SECOND PAGE SO THAT THE USER CAN READ IT
    if (get<0>(entry) == "insert") {
        vector<string> input = newInsertPage("Insert");
        string city = input[0];
        string state = input[1];
        string shape = input[2];
        string duration = input[3];
        string year = input[4];

        string combined =
                "State: " + input[1] + ", City: " + input[0] + ", Shape: " + input[2] + ", Duration: " + input[3] +
                ", Year: " + input[4];

        auto startInsertHashMap = steady_clock::now();
        if (hashMap.insert(input[0] + input[1], combined)) {
            insertionDeletion =  "Inserted into HashMap:\n";
            topText.setString(insertionDeletion);
            parameterPrompt.setString(combined + "\n");
        } else {
            insertionDeletion =  "Failed to insert into HashMap: \n";
            topText.setString(insertionDeletion);
            parameterPrompt.setString(combined + "\n");
        }
        auto stopInsertHashMap = steady_clock::now();
        auto durationInsertHashMap = duration_cast<milliseconds>(stopInsertHashMap - startInsertHashMap);
        hashMapTime = "HashMap insert took " + to_string(durationInsertHashMap.count()) + " milliseconds\n";

        auto startInsertCustomMap = steady_clock::now();
        customMap.Insert(city, state, shape, stof(duration), stoi(year));
        auto stopInsertCustomMap = steady_clock::now();
        auto durationInsertCustomMap = duration_cast<milliseconds>(stopInsertCustomMap - startInsertCustomMap);
        mapTime =  "Custom Map insert took " + to_string(durationInsertCustomMap.count()) +  " milliseconds\n";


    }
    else if (get<0>(entry) == "remove") {
        vector<string> input = removePage();
        string state = input[0];
        string city = input[1];

        auto startRemoveHashMap = steady_clock::now();
        if (hashMap.remove(city)) {
            insertionDeletion =  "Removed from HashMap: \n\t";
            topText.setString(insertionDeletion);
            parameterPrompt.setString(state +  ", " + city + "\n");
        } else {
            insertionDeletion =  "Couldn't find in HashMap: \n\t";
            topText.setString(insertionDeletion);
            topText.setString(state + ", " + city + "\n");
        }
        auto stopRemoveHashMap = steady_clock::now();
        auto durationRemoveHashMap = duration_cast<milliseconds>(stopRemoveHashMap - startRemoveHashMap);
        hashMapTime = "HashMap remove took " + to_string(durationRemoveHashMap.count()) + " milliseconds.\n";

        auto startRemoveCustomMap = steady_clock::now();
        int count = customMap.Remove(city, state);
        auto stopRemoveCustomMap = steady_clock::now();
        auto durationRemoveCustomMap = duration_cast<milliseconds>(stopRemoveCustomMap - startRemoveCustomMap);
        mapTime = "Custom Map remove took " + to_string(durationRemoveCustomMap.count()) + " milliseconds.\n";
        mapTime += to_string(count) + " records removed from Custom Map.\n";

    }
    else if (get<0>(entry) == "City") {
        auto startCityHashMap = steady_clock::now();
        strHashMap = hashMap.searchCity(get<1>(entry));
        auto stopCityHashMap = steady_clock::now();
        auto durationCityHashMap = duration_cast<milliseconds>(stopCityHashMap - startCityHashMap);
        hashMapTime = "HashMap search for city took " + to_string(durationCityHashMap.count()) + " milliseconds.\n";

        auto startCityCustomMap = steady_clock::now();
        strMap = customMap.SearchCity(get<1>(entry));  // Update state value
        auto stopCityCustomMap = steady_clock::now();
        auto durationCityCustomMap = duration_cast<milliseconds>(stopCityCustomMap - startCityCustomMap);
        mapTime = "Custom Map search for city took " + to_string(durationCityCustomMap.count()) + " milliseconds.\n";

    }
    else if (get<0>(entry) == "State") {
        auto startStateHashMap = steady_clock::now();
        strHashMap = hashMap.searchState(get<1>(entry));
        auto stopStateHashMap = steady_clock::now();
        auto durationStateHashMap = duration_cast<milliseconds>(stopStateHashMap - startStateHashMap);
        hashMapTime = "HashMap search for state took " + to_string(durationStateHashMap.count()) + " milliseconds.\n";

        auto startStateCustomMap = steady_clock::now();
        strMap = customMap.SearchState(get<1>(entry));
        auto stopStateCustomMap = steady_clock::now();
        auto durationStateCustomMap = duration_cast<milliseconds>(stopStateCustomMap - startStateCustomMap);
        mapTime =  "Custom Map search for state took " + to_string(durationStateCustomMap.count()) + " milliseconds.\n";


    }
    else if (get<0>(entry) == "Shape") {
        auto startShapeHashMap = steady_clock::now();
        strHashMap = hashMap.searchShape(get<1>(entry));
        auto stopShapeHashMap = steady_clock::now();
        auto durationShapeHashMap = duration_cast<milliseconds>(stopShapeHashMap - startShapeHashMap);
        hashMapTime = "HashMap search for shape took " + to_string(durationShapeHashMap.count()) + " milliseconds.\n";

        auto startShapeCustomMap = steady_clock::now();
        strMap = customMap.SearchShape(get<1>(entry));
        auto stopShapeCustomMap = steady_clock::now();
        auto durationShapeCustomMap = duration_cast<milliseconds>(stopShapeCustomMap - startShapeCustomMap);
        strMap = "Custom Map search for shape took " + to_string(durationShapeCustomMap.count()) + " milliseconds.\n";

    }
    else if (get<0>(entry) == "Year") {
        auto startYearHashMap = steady_clock::now();
        strHashMap = hashMap.searchYear(get<1>(entry));
        auto stopYearHashMap = steady_clock::now();
        auto durationYearHashMap = duration_cast<milliseconds>(stopYearHashMap - startYearHashMap);
        hashMapTime = "HashMap search for year took " + to_string(durationYearHashMap.count()) + " milliseconds.\n";

        int yearInt = stoi(get<1>(entry));
        auto startYearCustomMap = steady_clock::now();
        strMap = customMap.SearchYear(yearInt);
        auto stopYearCustomMap = steady_clock::now();
        auto durationYearCustomMap = duration_cast<milliseconds>(stopYearCustomMap - startYearCustomMap);
        mapTime = "Custom Map search for year took " + to_string(durationYearCustomMap.count()) + " milliseconds.\n";

    } else {
        topText.setString("All UFO Sightings in the USA");
        auto startPrintHashMap = steady_clock::now();
        strHashMap = hashMap.print();
        auto stopPrintHashMap = steady_clock::now();
        auto durationPrintHashMap = duration_cast<milliseconds>(stopPrintHashMap - startPrintHashMap);
        hashMapTime = "HashMap print took " + to_string(durationPrintHashMap.count()) + " milliseconds.\n";

        auto startPrintCustomMap = steady_clock::now();
        strMap = customMap.Print();
        auto stopPrintCustomMap = steady_clock::now();
        auto durationPrintCustomMap = duration_cast<milliseconds>(stopPrintCustomMap - startPrintCustomMap);
        mapTime = "Custom Map print took " +  to_string(durationPrintCustomMap.count()) + " milliseconds.\n";

    }


    // Creating the second window to display the data
    sf::RenderWindow Results(sf::VideoMode(1500, 1000), "Hashmap vs Hashtable",
                             sf::Style::Close | sf::Style::Titlebar);

    // creating a static window so that the user can scroll down
    sf::View view(sf::FloatRect(0, 0, width, height));
    view.setCenter(width / 2, height / 2);
    sf::RectangleShape largeContent(sf::Vector2f(800, 2000));
    largeContent.setFillColor(sf::Color::Green);


    while (Results.isOpen() && get<2>(entry) == true) {
        sf::Event event;

        // center text
        topText.setOrigin(topText.getGlobalBounds().width / 2.0f, 0);

        while (Results.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Results.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    // Adjust the view's center to scroll up or down
                    float scrollSpeed = 60.0f;
                    view.move(0, -event.mouseWheelScroll.delta * scrollSpeed);
                }
            }

            // Handle Back button click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = Results.mapPixelToCoords(sf::Mouse::getPosition(Results));

                    if (backButton.isClicked(mousePos)) {
                        // Close the results window and return to the entry window
                        Results.close();
                        backClicked = true;// Reopen entry window
                    }
                }
            }

            // adjust view of the screen while the user scrolls
            float viewHeight = height;
            float contentHeight = largeContent.getSize().y;
            sf::Vector2f viewCenter = view.getCenter();
            if (viewCenter.y - viewHeight / 2 < 0) {
                view.setCenter(viewCenter.x, viewHeight / 2);
            } else if (viewCenter.y + viewHeight / 2 > contentHeight) {
                view.setCenter(viewCenter.x, contentHeight - viewHeight / 2);
            }

            output.setString(mapTime + strMap);
            outputHash.setString(hashMapTime + strHashMap);
        }

        // create elements for the results screen
        ufo.setTexture(ufoImage2);
        Results.clear(sf::Color((35, 35, 70)));
        Results.draw(ufo);
        Results.setView(view);
        Results.draw(output);
        Results.draw(outputHash);
        Results.draw(topText);
        Results.draw(parameterPrompt);
        Results.draw(backButton.shape);
        Results.draw(backButton.text);
        Results.display();

    }
    return backClicked;
}
