#include <iostream> //std::cin, std::cout
#include <fstream>  //std::ifstream
#include <string>
#include <map>
#include <memory>
#include <ao/ao.h>  //audio library

#include "structs.h"
#include "input.h"

using namespace std;

int main(int argc, char **argv)
{
  int BPM;
  Track track;
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << " input_file" << endl;
    return 1;
  }

  ifstream sourceFile(argv[1]);

  int s = scan(sourceFile, track, BPM);
  sourceFile.close();
  if(s) {
    std::cout << "Error with reading file on char" << s << endl;
    //TODO: print last successfully scanned note
    // return s;
  }

  for(auto &note : track.melody) {
    cout << note.toString();
  }

  // cout << BPM << endl;
  // cout << s << endl;
  cout << endl;
  return 0;
}
