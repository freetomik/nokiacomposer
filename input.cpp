#include "input.h"

using namespace std;

//scans input file and fills up track with notes
//return 0 if success, otherwise returns number of wrong char
int scan(ifstream &sourceFile, Track &track, int &BPM) {
  int i = 0;
  char c = 0;
  State state = START;

  sourceFile >> BPM;

  MelodyObject mo;
  Note note;
  Rest rest;

  while(1) {
    sourceFile.get(c);
    printf("%d\n", c);
    if(sourceFile.eof()) return 0;
    switch(state) {
      case START:
        if(isDuration(c-'0')) {
          if(c == '1') state = _1;
          else if(c == '3') state = _3;
          else {  //2,4,8
            state = DURATION;
            note.duration.setValue(c-'0');
          }
          break;
        }
        else if(isspace(c)) {
          while(sourceFile.get(c)) {
            i++;
            if(!isspace(c)) break;
            if(sourceFile.eof()) return 0;
            printf("><");
          }
          sourceFile.unget();
          i--;
          state = START;
          break;
        }
        else {
          return i;
        }
      case _1:
        if(c == '6') {
          state = DURATION;
          note.duration.setValue(16);
        }
        else if(c == '.') {
          state = DOT;
          note.duration.setDot();
        }
        else if(c == '#') {
          state = SHARP;
          note.pitch.setSharp();
        }
        else if(isNote(c)) {
          state = NOTE;
          note.pitch.setNote(c);
        }
        else if(c == '-') {
          state = REST;
        }
        else {
          return i;
        }
        break;
      case _3:
        if(c == '2') {
          state = DURATION;
          note.duration.setValue(32);
          break;
        }
        else {
          return i;
        }
      case DURATION:
        if(c == '.') {
          state = DOT;
          note.duration.setDot();
        }
        else if(c == '#') {
          state = SHARP;
          note.pitch.setSharp();
        }
        else if(isNote(c)) {
          state = NOTE;
          note.pitch.setNote(c);
        }
        else if(c == '-') {
          state = REST;
        }
        else {
          return i;
        }
        break;
      case DOT:
        if(c == '#') {
          state = SHARP;
          note.pitch.setSharp();
        }
        else if(isNote(c)) {
          state = NOTE;
          note.pitch.setNote(c);
        }
        else if(c == '-') {
          state = REST;
        }
        else {
          return i;
        }
        break;
      case SHARP:
        if(isNote(c)) {
          state = NOTE;
          note.pitch.setNote(c);
        }
        else {
          return i;
        }
        break;
      case REST:
        state = START;
        sourceFile.unget();
        i--;
        rest.duration = note.duration;
        mo = rest;
        // track.melody.push_back(rest);
        (&rest)->~Rest();
//http://stackoverflow.com/questions/1124634/call-destructor-and-then-constructor-resetting-an-object
        new (&rest) Rest();
        break;
      case NOTE:
        if(isOctave(c)) {
          state = OCTAVE;
          note.pitch.setOctave(octaveTable.at(c));
          break;
        }
        state = START;
        sourceFile.unget();
        i--;
        mo = note;
        track.melody.push_back(note);
        (&note)->~Note();
        new (&note) Note();
        break;
      case OCTAVE:
        printf("oct.\n");
        state = START;
        sourceFile.unget();
        i--;
        mo = note;
        track.melody.push_back(note);
        (&note)->~Note();
        new (&note) Note();
        break;
    }
    i++;
  }
  (&rest)->~Rest();
  (&note)->~Note();

  return true;
}