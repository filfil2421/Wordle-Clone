/*
Filip Maletic (250866829)
CS 3307A Individual Assignment
October 3, 2023
This file constructs the Wordle Application and contains relevant functions for running and playing the game.
*/

#include "WordleApplication.h"
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

WordleApplication::WordleApplication(const Wt::WEnvironment& env)
    : WApplication(env), targetWord(""), currentGuess(""), attemptsRemaining(6), wonGame(false)
{
    setTitle("Wordle");
    // Creates a container to hold the input elements.
    auto container = root()->addWidget(make_unique<Wt::WContainerWidget>());
    // Adds a message to enter a guess before the empty text box.
    container->addWidget(make_unique<Wt::WText>("Enter guess, 5 letters maximum: "));
    guessInput = container->addWidget(make_unique<Wt::WLineEdit>());
    // Creates a button for the user to be able to submit a guess.
    auto submitButton = container->addWidget(make_unique<Wt::WPushButton>("Submit"));
    // Line break
    container->addWidget(make_unique<Wt::WBreak>());
    // Sets appropriate messages to display current game state to user.
    responseText = root()->addWidget(make_unique<Wt::WText>(""));
    attemptsText = root()->addWidget(make_unique<Wt::WText>("<div style='padding: 10px;'>Attempts left: " + std::to_string(attemptsRemaining) + "</div>"));
    resultText = root()->addWidget(make_unique<Wt::WText>(""));

    submitButton->clicked().connect(this, &WordleApplication::processGuess);
    restartButton = root()->addWidget(make_unique<Wt::WPushButton>("<span style='padding: 10px;'>New Game"));
    restartButton->clicked().connect(this, &WordleApplication::restartGame);
    // This container will display previous guesses as the game goes on.
    savedGuess = root()->addWidget(make_unique<Wt::WContainerWidget>());
    
    startGame();
}

// This function fetches a random 5 letter word from the word.txt file and returns it in uppercase to be used as the target word in the game.
string WordleApplication::getRandomWord(){
    vector<string> words;
    string line;
    ifstream file("words.txt");
    // Stores each word in the file in a string vector.
     while (getline(file, line)) {
        for (char &c : line) {
            c = toupper(c);
        }
        words.push_back(line);
    }
    file.close();
    // Uses timestamp so a new number is always used to select an index below.
    srand((unsigned) time(NULL));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

// This function contains most of the game logic for processing a guess and updating it to display to the user in an informative way. It provides input filtering as well.
void WordleApplication::processGuess() {
    // If game is already over.
    if (wonGame || attemptsRemaining <= 0) {
        return; 
    }
    // Converts guess input text to utf-encoded string so it can be processed correctly.
    currentGuess = guessInput->text().toUTF8();
    // Checks if the user inputs invalid characters (not letters) when submitting guess.
    for (char c : currentGuess) {
        if (!isalpha(static_cast<unsigned char>(c))) {
            responseText->setText("<div style='color: red;'>Your guess must only contain valid letters.</div>");
            return; 
        }
    }
    // Checks if the input word is longer than 5 letters and clears input and displays a message if true.
    if (currentGuess.length() > 5) {
        guessInput->setText("");
        responseText->setText(" Your guess can't be longer than 5 letters. ");
        return;
    }
    // Converts the current guess to uppercase just in case.
    for (char &c : currentGuess) {
        c = toupper(c);
    }
    // Clears input field for the next guess.
    guessInput->setText(""); 

    // This block checks each letter in the current guess word so it can be updated to display the accuracy of a guess compared to the target word.
    string updatedWord = "";
    for (size_t i = 0; i < targetWord.size(); ++i) {
        // Letter is green if it is in the exact position as it is in the target word.
        if (i < currentGuess.size() && currentGuess[i] == targetWord[i]) {
            updatedWord += "<span style='color: green;'>" + std::string(1, targetWord[i]) + "</span>";
        }
        // Letter is red if it is not in the exact position as it is in the target word, but is still found somewhere else in the word.
        else if (targetWord.find(currentGuess[i]) != string::npos) {
            updatedWord += "<span style='color: red;'>" + std::string(1, currentGuess[i]) + "</span>";
        }
        // Letter is grey if it not found in the target word at all.
        else {
            updatedWord += "<span style='color: grey;'>" + std::string(1, currentGuess[i]) + "</span>";
        }
    }
    responseText->setText("<div>" + updatedWord + "</div>");
    // Decrements how many attempts the user has left.
    attemptsRemaining--;
    // If guess matches the target word, the game has been won and an appropriate message is displayed allowing the user to play again.
    if (currentGuess == targetWord) {
        wonGame = true;
        resultText->setText(" You guessed correctly! Play again? ");
        restartButton->setText("Restart");
    }   
    // If the user has run out of guesses it shows the correct answer and allows the user to try a new game.
    else if (attemptsRemaining == 0) {
        resultText->setText(std::string(" You are out of guesses! The correct word was: ") + targetWord + ". Play again? ");
        restartButton->setText("Restart");
    }
    // If the guess is wrong but there's still remaining attempts, it displays the amount of attempts left.
    else {
        resultText->setText(" Incorrect guess: Try again! ");
        attemptsText->setText(" Attempts left: " + std::to_string(attemptsRemaining));
    }
    // Displays each guess as it happens in a bigger font and makes the guesses appear stacked on top of each other.
    Wt::WText* storedGuess = savedGuess->addWidget(std::make_unique<Wt::WText>("<div style='margin-bottom: 5px; font-size: 20px; padding: 5px;'>" + updatedWord + "</div>"));
}

// This function is used to start a game and sets all game elements to the beginning stage of the game.
void WordleApplication::startGame() {
    targetWord = getRandomWord();
    wonGame = false;
    attemptsRemaining = 6;
    currentGuess = "";

    // Clears text displayed to player when starting a new game.
    guessInput->setText("");
    responseText->setText("");
    attemptsText->setText(" Attempts left: " + std::to_string(attemptsRemaining));
    resultText->setText("");
    restartButton->setText("New Game");
    savedGuess->clear();
}

// This function is used when a user wants to quit and start a new game at any point during play.
void WordleApplication::restartGame() {
    startGame();
    restartButton->setText("New Game");
}
