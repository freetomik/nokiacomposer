#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <vector>
#include <array>
#include <map>

//C++11 initialization of a map
const std::map<char, double> freqTable {
  {'c', 130.8127826503},
  {'d', 146.8323839587},
  {'e', 164.8137784564},
  {'f', 174.6141157165},
  {'g', 195.9977179909},
  {'a', 220.0000000000},
  {'b', 246.9416506281},
  {'h', 246.9416506281}
};

// C++11 strongly typed enum
enum class octaveEnum { 
  SMALL_OCTAVE,
  ONE_LINE_OCTAVE,
  TWO_LINE_OCTAVE,
  THREE_LINE_OCTAVE
};

/* MelodyObject
 *  high level entity over Notes and Rests
*/
class MelodyObject {};

/* NoteDuration
 *  duration part of note
*/
class NoteDuration
{
private:
  unsigned short value;  //1, 2, 4, 8, 16, 32(, ...)
  bool dot;
  
  double duration;    //in ms, depended on Composition tempo

public:
  NoteDuration(unsigned short v, bool d);

  unsigned short getValue();
  bool hasDot();

  ~NoteDuration(){}
};

/* NotePitch
 *  pitch part of note
*/
class NotePitch
{
private:
  bool sharp;
  char note;
  octaveEnum octave;

  double pitch;     //in Hz

  bool isNote(char c);

public:
  NotePitch(bool s, char n, octaveEnum o);

  bool getSharp();
  char getNote();
  octaveEnum getOctave();
  double getPitch();

  ~NotePitch(){}
};

/* Note
 *
*/
class Note : public MelodyObject
{
private:
  NoteDuration duration;
  NotePitch pitch;
  std::string word;

public:
  Note(unsigned short v,
       bool d,
       bool s,
       char n,
       octaveEnum o,
       std::string w):
    duration(v, d),
    pitch(s, n, o),
    word(w)
  {}

  std::string getWord();

  ~Note(){}
};

class Rest : public MelodyObject
{
private:
  NoteDuration duration;

public:
  Rest(unsigned short v,
       bool d):
    duration(v, d)
  {}
  ~Rest(){}
};

class Track
{
private:
  std::vector<MelodyObject> melody;
  
public:
  Track();
  ~Track();
};

class Composition
{
private:
  int BPM;
  std::vector<Track> tracks;

public:
  Composition(){}
  ~Composition(){}
};

#endif
