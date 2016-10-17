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
  Track t;

  ifstream sourceFile(argv[1]);

  int s = scan(sourceFile, t, BPM);
  sourceFile.close();
  if(s) {
    printf("Error with reading file on char %d.\n", s);
    //TODO: print last successfully scanned note
    // return s;
  }

  for(vector<std::shared_ptr<MelodyObject>>::iterator n = t.melody.begin(); n != t.melody.end(); ++n) {
    cout << (*n)->toString() << ' ';
  }

  // cout << BPM << endl;
  // cout << s << endl;
  cout << endl;
  return 0;
}
