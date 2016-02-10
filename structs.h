#ifndef STRUCTS_H
#define STRUCTS_H

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

const std::array<char, 6> durationChars = {'1','2','3','4','6','8'};
const std::array<char, 3> octaveChars = {'1','2','3'};

// C++11 strongly typed enum
enum class octaveEnum { 
  SMALL_OCTAVE,
  ONE_LINE_OCTAVE,
  TWO_LINE_OCTAVE,
  THREE_LINE_OCTAVE
};

const std::map<char, octaveEnum> octaveTable {
  {'1', octaveEnum::ONE_LINE_OCTAVE},
  {'2', octaveEnum::TWO_LINE_OCTAVE},
  {'3', octaveEnum::THREE_LINE_OCTAVE}
};

bool isNote(char c);
bool isDuration(unsigned short c);
bool isOctave(char c);

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
  bool dot = false;
  
  double duration;    //in ms, depended on Composition tempo

public:
  NoteDuration();

  void setValue(unsigned short v);
  void setDot();

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

public:
  NotePitch();

  void setSharp();
  void setNote(char n);
  void setOctave(octaveEnum o);
  void setPitch(double p);

  bool hasSharp();
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
public:
  NoteDuration duration;
  NotePitch pitch;

  Note():
    duration(),
    pitch()
  {}

  std::string toString();

  ~Note(){}
};

class Rest : public MelodyObject
{
public:
  NoteDuration duration;

  Rest():
    duration()
  {}
  ~Rest(){}
};

class Track
{
public:
  //TODO: change to:
  // std::vector<MelodyObject> melody;
  
  std::vector<Note> melody;
  
  Track(){}
  ~Track(){}
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