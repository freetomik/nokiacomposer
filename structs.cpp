#include <cmath>    //for sharp pitch computation
#include <memory>

#include "structs.h"

using namespace std;

NoteDuration::NoteDuration()
  : value(1),
    dot(false),
    duration(0)
{}

void NoteDuration::setValue(unsigned short v) {
  if(isDuration(v))
    value = v;
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


string Note::toString() {
  string noteString = "";
  noteString += std::to_string(duration.getValue());
  if(duration.hasDot()) noteString += '.';
  if(pitch.hasSharp()) noteString += '#';
  noteString += pitch.getNote();
  switch(pitch.getOctave()) {
    case octaveEnum::SMALL_OCTAVE:
      break;
    case octaveEnum::ONE_LINE_OCTAVE:
      noteString += '1';
      break;
    case octaveEnum::TWO_LINE_OCTAVE:
      noteString += '2';
      break;
    case octaveEnum::THREE_LINE_OCTAVE:
      noteString += '3';
      break;
  }
  return noteString;
}

string Rest::toString() {
  string restString = "";
  restString += std::to_string(duration.getValue());
  if(duration.hasDot()) restString += '.';
  restString += '-';
  return restString;
}

bool isNote(char c) {
  //FIXME: use std::find in freqTable
  return (c >= 'a' and c <= 'h');
}

bool isDuration(unsigned short s) {
  //FIXME: use std::find in durations
  return (s == 1 or
          s == 2 or
          s == 4 or
          s == 8 or
          s == 16 or
          s == 32
          );
}

bool isDurationChar(char c) {
  //FIXME: use std::find in durationChars
  return (c == '1' or
          c == '2' or
          c == '3' or
          c == '4' or
          c == '6' or
          c == '8'
          );
}

bool isOctaveChar(char c) {
  //FIXME: use std::find in octaveChars
  return (c == '1' or
          c == '2' or
          c == '3'
          );
}
