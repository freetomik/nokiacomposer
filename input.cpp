#include "input.h"

using namespace std;

//scans input file and fills up track with notes
//return 0 if success, otherwise returns number of wrong char
int scan(ifstream &sourceFile, Track &track, int &BPM) {
  int i = 0;
  char c = 0;
  State state = START;

  sourceFile >> BPM;

  Note* note = new Note();
  Rest* rest = new Rest();

  while(1) {
    sourceFile.get(c);
    printf("%c", c);
    if(sourceFile.eof()) return 0;
    switch(state) {
      case START:
        if(isDurationChar(c)) {
          if(c == '1') state = _1;
          else if(c == '3') state = _3;
          else {  //2,4,8
            state = DURATION;
            note->duration.setValue((unsigned short)c);
          }
          break;
        }
        else if(isspace(c)) {
          while(sourceFile.get(c)) {
            i++;
            if(!isspace(c)) break;
            if(sourceFile.eof()) return 0;
            printf(" ");
          }
          if(sourceFile.eof()) return 0;
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
          note->duration.setValue(16);
        }
        else if(c == '.') {
          state = DOT;
          note->duration.setDot();
        }
        else if(c == '#') {
          state = SHARP;
          note->pitch.setSharp();
        }
        else if(isNote(c)) {
          state = NOTE;
          note->pitch.setNote(c);
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
          note->duration.setValue(32);
          break;
        }
        else {
          return i;
        }
      case DURATION:
        if(c == '.') {
          state = DOT;
          note->duration.setDot();
        }
        else if(c == '#') {
          state = SHARP;
          note->pitch.setSharp();
        }
        else if(isNote(c)) {
          state = NOTE;
          note->pitch.setNote(c);
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
          note->pitch.setSharp();
        }
        else if(isNote(c)) {
          state = NOTE;
          note->pitch.setNote(c);
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
          note->pitch.setNote(c);
        }
        else {
          return i;
        }
        break;
      case REST:
        state = START;
        sourceFile.unget();
        i--;
        rest->duration = note->duration;
        track.melody.push_back(rest);
        delete rest;
        rest = new Rest();
        break;
      case NOTE:
        if(isOctaveChar(c)) {
          state = OCTAVE;
          note->pitch.setOctave(octaveTable.at(c));
          break;
        }
        state = START;
        sourceFile.unget();
        i--;
        track.melody.push_back(note);
        delete note;
        note = new Note();
        break;
      case OCTAVE:
        printf("oct.\n");
        state = START;
        sourceFile.unget();
        i--;
        track.melody.push_back(note);
        delete note;
        note = new Note();
        break;
    }
    i++;
  }
  delete rest;
  delete note;

  return true;
}