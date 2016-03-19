# Nokia Composer
converter of Nokia Composer melodies format to MIDI<br>
_hobby project for fun and learning C++_

## Nokia melody format
Regular expression for note/rest is [`(1|2|4|8|16|32)([.]?([#]?[a-g][1-3]?|[-]))`](http://regexr.com/3d1v7).<br>
Finite state machine is shown in fsm/nc_fsm_simple.svg.<br>
This program reads on first line tempo in BPM as number, as shown in example.txt.<br>

## Current project progress
* complete parsing of input
* saving notes to memory

## Build & Usage (Linux)
```
$ make
$ ./nokiacomposer example.txt
```

## TODO
* fix saving notes/rests to memory
* write parsed melody to MIDI file using [midifile](https://github.com/craigsapp/midifile)
