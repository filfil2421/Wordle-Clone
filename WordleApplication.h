/*
Filip Maletic (250866829)
CS 3307A Individual Assignment
October 3, 2023
This header file outlines the structure and interface of the wordle application. It provides the constructor as well as private and public sections and defines member variables and functions.
*/

#ifndef WORDLE_APPLICATION_H
#define WORDLE_APPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <iostream>
#include <vector>
#include <string>

class WordleApplication : public Wt::WApplication {
public:
    WordleApplication(const Wt::WEnvironment& env);

private:
    // These are the neccessary private member variables and functions for game state and user interface.
    std::string getRandomWord();
    std::string targetWord;
    std::string currentGuess;
    int attemptsRemaining;
    bool wonGame;

    Wt::WLineEdit* guessInput;
    Wt::WText* responseText;
    Wt::WText* attemptsText;
    Wt::WText* resultText;

    Wt::WPushButton* submitButton; 
    Wt::WPushButton* restartButton; 
    Wt::WContainerWidget* savedGuess; 

    void startGame();
    void processGuess();
    void restartGame();
};

#endif 
