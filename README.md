This repo contains the FW for the various Mikrolysreklamen

\<Major.Minor.Patch\>

## v0.0.1
- Initial FW, runs from local memory. Limited implemented effects.


The SD-card must be formatted in FATFS, when formatting from windows choose "FAT32"
The SDcard must contain a file named playlist.txt (Case sensitive?), this file must contain the name of a .pgm file on each line, without the file ending, the file must be terminated by a newline '\n'
File names is only supported in the 8.3 format. 1-8 character file name file name must not contain '.' and 3 character file ending (pgm)
Using FATFS: http://elm-chan.org/fsw/ff/00index_e.html