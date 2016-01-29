#include <cmath>    //for sharp pitch computation

#include "structs.h"

using namespace std;

NoteDuration::NoteDuration()
  : value(1),
    dot(false),
    duration(0)
{}

void NoteDuration::setValue(char v) {
  if(isDuration(v))
    value = v - '0';  //char to number conversion
  // else
  //   throw exception;
}
void NoteDuration::setDot() {
  dot = true;
}

unsigned short NoteDuration::getValue() {
  return value;
}
bool NoteDuration::hasDot() {
  return dot;
}


NotePitch::NotePitch()
//initialization list:
  : sharp(false),
    note('c'),
    octave(octaveEnum::SMALL_OCTAVE),
    pitch(130.8127826503)
//constructor body:
{}

void NotePitch::setSharp() {
  sharp = true;
}
void NotePitch::setNote(char n) {
  if(isNote(n))
    note = n;
  // else
  //   throw exception;
}
void NotePitch::setOctave(octaveEnum o) {
  octave = o;
}

bool NotePitch::hasSharp() {
  return sharp;
}
char NotePitch::getNote() {
  return note;
}
octaveEnum NotePitch::getOctave() {
  return octave;
}
double NotePitch::getPitch() {
  pitch = freqTable.at(note);
  //FIXME: maybe not correct pitches
  if(octave == octaveEnum::SMALL_OCTAVE) pitch /= 2;
  else if(octave == octaveEnum::ONE_LINE_OCTAVE) pitch *= 2;
  else if(octave == octaveEnum::TWO_LINE_OCTAVE) pitch *= 4;
  else if(octave == octaveEnum::THREE_LINE_OCTAVE) pitch *= 8;
  if(sharp) pitch *= pow(2, 1/12.0);
  return pitch;
}


string Note::print() {
  string noteString = "";
  noteString.push_back(duration.getValue() + '0');
  if(duration.hasDot()) noteString.push_back('.');
  if(pitch.hasSharp()) noteString.push_back('#');
  noteString.push_back(pitch.getNote());
  switch(pitch.getOctave()) {
    case octaveEnum::SMALL_OCTAVE:
      break;
    case octaveEnum::ONE_LINE_OCTAVE:
      noteString.push_back('1');
      break;
    case octaveEnum::TWO_LINE_OCTAVE:
      noteString.push_back('2');
      break;
    case octaveEnum::THREE_LINE_OCTAVE:
      noteString.push_back('3');
      break;
  }
  return noteString;
}

bool isNote(char c) {
  //FIXME: use std::find in freqTable
  return (c >= 'a' and c <= 'h');
}

bool isDuration(char c) {
  //FIXME: use std::find in durationChars
  unsigned short i = c - '0';
  return (i == 1 or
          i == 2 or
          i == 3 or
          i == 4 or
          i == 6 or
          i == 8
          );
}

bool isOctave(char c) {
  //FIXME: use std::find in octaveChars
  unsigned short i = c - '0';
  return (i == 1 or
          i == 2 or
          i == 3
          );
}
