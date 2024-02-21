/*
Filip Maletic (250866829)
CS 3307A Individual Assignment
October 3, 2023
This file contains the main function which sets up the WT application by creating an instance of the WordleApplication class.
*/

#include <Wt/WApplication.h>
#include "WordleApplication.h"

// The function returns a newly instantiated application object.
int main(int argc, char **argv){
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
    return std::make_unique<WordleApplication>(env);
  });
}
