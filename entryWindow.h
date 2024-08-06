#pragma once
#include "Button.h"

vector<string> newInsertPage(string option){
    // option like insert or remove
    vector<string> options = {"City", "State", "Shape", "Duration", "Year"};
    int width = 1500;
    int height = 1000;
    sf::RenderWindow optionWindow(sf::VideoMode(width, height), option + " UFO", sf::Style::Close | sf::Style::Titlebar);
    sf::Font font;
    font.loadFromFile("../files/font.ttf");

    sf::Text welcomeText;
    welcomeText.setString("INSERT UFO SIGHTINGS");
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(50);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setOutlineColor(sf::Color::Black);
    welcomeText.setOutlineThickness(3);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(width / 2.0f, 75);
    welcomeText.setOrigin(welcomeText.getGlobalBounds().width / 2.0f, 0);
    std::vector<sf::Text> inputTexts(5);
    std::vector<std::string> inputs(5, "");

    for (int i = 0; i < 5; ++i) {
        inputTexts[i].setFont(font);
        inputTexts[i].setCharacterSize(30);
        inputTexts[i].setFillColor(sf::Color::White);
        inputTexts[i].setPosition(340.0f, 200.0f + i * 50.0f);
        inputTexts[i].setString("Input " + std::to_string(i + 1) + ": ");
    }

    int currentInput = 0; // Track which input is currently being entered

    while (optionWindow.isOpen()) {
        sf::Event event;
        while (optionWindow.pollEvent(event)) {
            if (currentInput == 5 || event.type == sf::Event::Closed ) {
                optionWindow.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                // Handle text input
                if (event.text.unicode < 128) { // ASCII characters only
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b') { // Handle backspace
                        if (!inputs[currentInput].empty()) {
                            inputs[currentInput].pop_back();
                        }
                    }
                    else if (enteredChar == '\r' || enteredChar == '\n') { // Handle Enter key
                        if (currentInput < 5) {
                            currentInput++; // Move to the next input
                        }
                    }
                    else if (enteredChar == 27) { // Handle Escape key to clear current input
                        inputs[currentInput] = "";
                    }
                    else {
                        inputs[currentInput] += enteredChar;
                    }
                }
            }
        }

        // Update text objects with current inputs
        for (int i = 0; i < 5; ++i) {
            inputTexts[i].setString(options[i] + ": " + inputs[i]);
        }

        optionWindow.clear();
        for (const auto& text : inputTexts) {
            optionWindow.draw(text);
        }
        optionWindow.draw(welcomeText);
        optionWindow.display();
    }

    // Output the captured inputs
    std::cout << "Collected Inputs:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << options[i] << ": " << inputs[i] << std::endl;
    }
    return inputs;
}

vector<string> removePage(){
    // option like insert or remove

    vector<string> options = {"State", "City"};
    int width = 1500;
    int height = 1000;
    sf::RenderWindow optionWindow(sf::VideoMode(width, height), "Remove UFO", sf::Style::Close | sf::Style::Titlebar);
    sf::Font font;
    font.loadFromFile("../files/font.ttf");

    sf::Text welcomeText;
    welcomeText.setString("REMOVE UFO SIGHTINGS");
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(50);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setOutlineColor(sf::Color::Black);
    welcomeText.setOutlineThickness(3);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(width / 2.0f, 75);
    welcomeText.setOrigin(welcomeText.getGlobalBounds().width / 2.0f, 0);

    std::vector<sf::Text> inputTexts(2);
    std::vector<std::string> inputs(2, "");

    for (int i = 0; i < 2; ++i) {
        inputTexts[i].setFont(font);
        inputTexts[i].setCharacterSize(30);
        inputTexts[i].setFillColor(sf::Color::White);
        inputTexts[i].setPosition(340.0f, 200.0f + i * 50.0f);
        inputTexts[i].setString("Input " + std::to_string(i + 1) + ": ");
    }

    int currentInput = 0; // Track which input is currently being entered

    while (optionWindow.isOpen()) {
        sf::Event event;
        while (optionWindow.pollEvent(event)) {
            if (currentInput == 2 || event.type == sf::Event::Closed ) {
                optionWindow.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                // Handle text input
                if (event.text.unicode < 128) { // ASCII characters only
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b') { // Handle backspace
                        if (!inputs[currentInput].empty()) {
                            inputs[currentInput].pop_back();
                        }
                    }
                    else if (enteredChar == '\r' || enteredChar == '\n') { // Handle Enter key
                        if (currentInput < 2) {
                            currentInput++; // Move to the next input
                        }
                    }
                    else if (enteredChar == 27) { // Handle Escape key to clear current input
                        inputs[currentInput] = "";
                    }
                    else {
                        inputs[currentInput] += enteredChar;
                    }
                }
            }
        }

        // Update text objects with current inputs
        for (int i = 0; i < 2; ++i) {
            inputTexts[i].setString(options[i] + ": " + inputs[i]);
        }

        optionWindow.clear();
        for (const auto& text : inputTexts) {
            optionWindow.draw(text);
        }
        optionWindow.draw(welcomeText);
        optionWindow.display();
    }

    // Output the captured inputs
    std::cout << "Collected Inputs:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        std::cout << options[i] << ": " << inputs[i] << std::endl;
    }
    return inputs;
}


tuple<string,string, bool> createEntryWindow() {
    //https://www.geeksforgeeks.org/tuples-in-c/# used for storing the parameters
    tuple<string,string, bool> selection;
    int width = 1500;
    int height = 1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "UFO Sightings!", sf::Style::Close | sf::Style::Titlebar);

    // Load font
    sf::Font font;
    font.loadFromFile("../files/font.ttf");

    // Define button attributes
    sf::Vector2f buttonSize(160, 70);
    std::vector<std::string> labels = {"City", "State", "Shape", "Year"};
    std::vector<Button> buttons;

    // Create buttons for parameters
    for (size_t i = 0; i < labels.size(); i++) {
        buttons.emplace_back(buttonSize, sf::Vector2f(380 + i * 200, 360), labels[i], font);
    }

    // Create insert and remove buttons
    Button insertButton(buttonSize, {500, 700}, "Insert", font);
    Button removeButton(buttonSize, {800, 700}, "Remove", font);

    // create submit button
    Button submit(buttonSize, {680, height / 2.0f + 400}, "Submit", font);

    // create Texts for Entry Page
    sf::Text welcomeText;
    welcomeText.setString("USA UFO SIGHTINGS!");
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(50);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setOutlineColor(sf::Color::Black);
    welcomeText.setOutlineThickness(3);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(width / 2.0f, height / 5.0f);
    welcomeText.setOrigin(welcomeText.getGlobalBounds().width / 2.0f, 0);

    sf::Text parameterPrompt; // display title and parameters
    parameterPrompt.setString(" Hashmap vs Map\nSelect Parameter:");
    parameterPrompt.setFont(font);
    parameterPrompt.setStyle(sf::Text::Bold);
    parameterPrompt.setFillColor(sf::Color::White);
    parameterPrompt.setCharacterSize(34);
    parameterPrompt.setPosition(width / 2.0f, height / 5.0f + 75);
    parameterPrompt.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text specific; // specified type of city, state, shape, and year for the search
    specific.setString("Enter Specific Search:\n\n\n\n\t\tOr\n Insert / Remove UFOS");
    specific.setFont(font);
    specific.setStyle(sf::Text::Bold);
    specific.setFillColor(sf::Color::White);
    specific.setCharacterSize(34);
    specific.setPosition(width / 2.0f - 20, height / 2.0f - 20);
    specific.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text byPass; // bypass all parameters to print out all stored data
    byPass.setString("For all Sightings, Press Submit Only");
    byPass.setFont(font);
    byPass.setStyle(sf::Text::Bold);
    byPass.setFillColor(sf::Color(255, 255, 255, 128));
    byPass.setCharacterSize(34);
    byPass.setPosition(width / 2.0f - 200, height / 2.0f + 340);
    byPass.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text output; // outputs map
    output.setFont(font);
    output.setStyle(sf::Text::Bold);
    output.setFillColor(sf::Color::White);
    output.setCharacterSize(30);
    output.setPosition(width / 2.0f, height / 5.0f + 75);
    output.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text outputHash; // outputs hashMap
    outputHash.setFont(font);
    outputHash.setStyle(sf::Text::Bold);
    outputHash.setFillColor(sf::Color::White);
    outputHash.setCharacterSize(12);
    outputHash.setOrigin(parameterPrompt.getLocalBounds().width / 2.0f, 0);

    sf::Text userInput;
    userInput.setFont(font);
    userInput.setCharacterSize(34);
    userInput.setStyle(sf::Text::Bold);
    userInput.setFillColor(sf::Color::Yellow);
    userInput.setPosition(width / 2.0f, height / 5.0f + 340);
    userInput.setOrigin(userInput.getLocalBounds().width / 2.0f, 0);

    sf::RectangleShape rectangle(sf::Vector2f(3, 34)); // created a cursor to follow text that the user enters
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setPosition(width / 2.0f, height / 5.0f + 340);
    int adjustment = 0;
    rectangle.setOrigin(userInput.getLocalBounds().width / 2.0f + adjustment, 0);

    // Create the background using purple and UFO images with AI using Bing Designer
    sf::Color colorPurple(35, 35, 70);
    sf::Texture ufoImage1;
    sf::Texture ufoImage2;
    ufoImage1.loadFromFile("../files/images/ufoImage.png");
    ufoImage2.loadFromFile("../files/images/ufoResults.png");

    sf::Sprite ufo;
    ufo.setTexture(ufoImage1);
    ufo.setPosition(width / 2.0f, height / 2.0f - 75);
    ufo.setOrigin(ufo.getLocalBounds().width / 2, ufo.getLocalBounds().height / 2.35);
    ufo.setScale(2, 2);
    ufo.setColor(sf::Color(255, 255, 255, 128));

    bool windowVal = false; // boolean to check if entry page is open or closed
    bool finishedEntry = true;

    // strings to store user's options
    string parameter = ""; // button data
    string name = ""; // specific entry

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                windowVal = false;

            if (event.type == sf::Event::TextEntered) { // collects characters for the specific entry
                if (event.text.unicode >= 32) {
                    name += event.text.unicode;

                    adjustment -= 20; // adjusts the cursor while the user is typing
                    userInput.setOrigin(userInput.getLocalBounds().width / 2.0f, 0);
                    rectangle.setOrigin(userInput.getLocalBounds().width / 2.0f + adjustment, 0);

                }
                // readjust string
                userInput.setString(name);

                // ensure that the user provides an entry
                if (name != "") {
                    finishedEntry = true;
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Backspace) { // deletes characters for the specific entry
                    name.pop_back();
                    adjustment += 20;

                    if (adjustment > userInput.getLocalBounds().width / 2.0f) {
                        adjustment = userInput.getLocalBounds().width / 2.0f;
                    }
                    rectangle.setOrigin(userInput.getLocalBounds().width / 2.0f + adjustment, 0);
                    userInput.setString(name); // readjust string
                }

                // ensure that the user provides an entry
                if (name == "") {
                    finishedEntry = false;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // Check which parameter buttons were clicked and activate it
                for (auto &button: buttons) {
                    if (button.isClicked(mousePos)) {
                        // Deactivate all other buttons for parameters
                        for (auto &otherButton: buttons) {
                            otherButton.setActive(false);
                        }
                        // Activate the clicked button
                        button.setActive(true);
                        parameter = button.label;
                        finishedEntry = false;
                    }
                }
                // check if the submit button is clicked
                if (insertButton.isClicked(mousePos)){
                    selection = make_tuple("insert", "", true);
                    window.close();
                }
                if (removeButton.isClicked(mousePos)){
                    selection = make_tuple("remove", "", true);
                    window.close();
                }
                if (submit.isClicked(mousePos) && finishedEntry == true) {
                    submit.setActive(true);
                    cout << "submitted parameter: " << parameter << "  \nspecific: " << name << "  \n" << submit.label;
                    window.close();
                    windowVal = true; // opens next pages
                    selection = make_tuple(parameter, name, windowVal);
                }
            }
        }

        // Create opening window
        window.clear(colorPurple); // making background color
        window.draw(ufo);          // drawing the elements
        window.draw(welcomeText);
        window.draw(parameterPrompt);
        window.draw(specific);
        window.draw(byPass);
        window.draw(rectangle);
        window.draw(userInput);
        for (const auto &button: buttons) {
            window.draw(button.shape);
            window.draw(button.text);
        }
        window.draw(insertButton.shape);
        window.draw(insertButton.text);
        window.draw(removeButton.shape);
        window.draw(removeButton.text);
        window.draw(submit.shape);
        window.draw(submit.text);

        window.display();
    }

    return selection;

}