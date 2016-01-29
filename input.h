#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "structs.h"

enum State {
  START,
  _1,
  _3,
  DURATION,
  DOT,
  SHARP,
  REST,
  NOTE,
  OCTAVE
};

int scan(std::ifstream &sourceFile, Track &track, int &BPM);

#endif