#include <cmath>    //for sharp pitch computation

#include "structs.h"

using namespace std;

NoteDuration::NoteDuration(unsigned short v, bool d)
  : value(v),
    dot(d),
    duration(0)
{
  //TODO: compute duration
}

unsigned short NoteDuration::getValue() {
  return value;
}
bool NoteDuration::hasDot() {
  return dot;
}


NotePitch::NotePitch(bool s, char n, octaveEnum o)
//initialization list:
  : sharp(s),
    note(n),
    octave(o)
//constructor body:
{
  if(isNote(note)) {
    pitch = freqTable.at(note);
    if(octave == octaveEnum::SMALL_OCTAVE) pitch /= 2;
    else if(octave == octaveEnum::ONE_LINE_OCTAVE) pitch *= 2;
    else if(octave == octaveEnum::TWO_LINE_OCTAVE) pitch *= 4;
    else if(octave == octaveEnum::THREE_LINE_OCTAVE) pitch *= 8;
    if(sharp) pitch *= pow(2, 1/12.0);
  }
}

bool NotePitch::getSharp() {
  return sharp;
}
char NotePitch::getNote() {
  return note;
}
octaveEnum NotePitch::getOctave() {
  return octave;
}
double NotePitch::getPitch() {
  return pitch;
}
bool NotePitch::isNote(char c) {
  return (c >= 'a' and c <= 'h');
}

string Note::getWord() {
  return this->word;
}