# CS220 - Spellcheck

## 1. Introduction
Spellcheck is a tool which, given a text, will search for misspelled words and will suggest alternative spellings.

## 2. Compilation Information
### Setup
For the API setup, please refer to [Redis and Hiredis installation](https://github.com/cmsc22000-project-2018/api). 

### Compilation
To use spellcheck, run `make` in the root directory.

### Testing
Testing has been conducted with the [Criterion](http://criterion.readthedocs.io/en/master/intro.html) testing framework and [ShellTestRunner](https://github.com/simonmichael/shelltestrunner).

## 3. Usage
### 1. Interactive Mode Description
If spellcheck is run without a file, it directs the user to the following screen:

```
Please load a file to begin. Additionally, select an output mode and/or choose dictionary before running the program.

[f] [/path/file.txt]       : Input text file
[d] [/path/dictionary.txt] : Input custom dictionary file
[m] [number]               : Mode [1 - Quiet, 2 - Verbose, 3 - Interactive]
[c]                        : Enable/Disable color
[h]                        : Help
[q]                        : Quit program

spellcheck >
```

For each detected error, the interactive mode produces:
(1) An indication of the location of the error
```
Line: 1:
I have a splling checker
            ^^^^^^^
```
(2) Generated suggestions, and options to delete the word, input an alternative word, or skip for users

```
Possible replacements for word splling are:

[1] : selling
[2] : spelling
[3] : billing
[4] : calling
[d] : Delete
[i] : Input
[s] : Skip
```

Interactive Mode continues this process until the end of the file. When finished, interactive mode moves onto the saving file page:

```
Spellcheck complete.

[p] : Print all modifications
[s] : Save to existing file
[c] : Save to custom file
[r] : Re-edit file
[q] : Quit program
```

The user can then view changes, then either save corrections to the original file, or save to a file of choice.


### 2. Quiet Mode Description
The user can activate quiet mode through the command line directly. The user runs:

```
$ ./spellcheck [~/path/file.txt] -q [options] 
```

Alternatively, the user can also activate quiet mode through the main directory. To do this, simply input:
```
$ ./spellcheck
```

Note that the default mode is interactive, and that a file input will direct the user immediately to interactive mode.

Running  quiet mode edits the given text file by replacing every identified misspelled word with the closest possible correction. The corrections are saved to the same file by default.

Additionally, several flags can be utilized to customize the quiet mode process through the command line. These are:

```
-q                   : Quiet mode - The program does not print any statements regarding the replacement process.
-s [~path/file.txt]  : Saves the edited version to a new text file instead of modifying the original file.
```

### 3. Verbose Mode Description
The user can activate batch mode through the command line directly. The user runs:

```
$ ./spellcheck [~/path/file.txt] - [options] 
```

If user chooses to utilize the verbose mode, spellcheck produces a list of detected errors, and up to 4 corresponding suggested corrections.

```
LINE:CHAR       WORD            SUGGESTIONS
1:9             spellig         spelling, selling, spell
1:17            chequer         cheque, cheaper, checker, chester
2:3             cme             came, ce, cm, cms
3:11            markes          makes, marked, marker, markers
3:25            revie           review, device, devil, eve
4:0             Misstakes       Mistakes, Mistake
5:19            typpe           type, tape, types
6:19            asy             amy, any, as, ash
7:0             Wether          Weather, Whether, Better, Bother
8:12            straigh         straight, strain, strange
8:20            waay            away, way
Successfully replaced every misspelled word and saved the modifications
```
