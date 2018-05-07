# CS220 - Spellcheck

## 1. Introduction
Spellcheck is a tool which, given a text, will search for misspelled words and will suggest alternative spellings.

## 2. Compilation Information
Right now we have a lot of Makefiles. We should finalize compilation by editing those - or at least indicate shared libraries here

## 3. Interactive Mode Description
If spellcheck is run without a file, it directs the user to the following screen:

```
$ ./spellcheck
------- Welcome to Spellcheck! -------
Please load a file into spellcheck to begin. Additionally, select mode and choose dictionary.

h                            : help
r [~/path/file.txt]          : read a file into spellcheck
d [~/path/dictionary.txt]    : read dictionary file into spellcheck
q                            : quit program

spellcheck >
```

The interactive mode produces:
(1) An indication of the location of the error

```
Line 32:
and then the fox jomped over the fens
                 ^^^^^^
Edit the specified misspelling? [y/n] 
(You can press [r] to return to the home interface)
spellcheck >
```

If the user chooses to skip the detected misspelling (by typing [n]), spellcheck moves onto the next error.

(2) If the user chooses to edit the misspelling, possible alternative spellings follow.

```
Suggestions: [1] jumped, [2] jammed, [3] dumped

Type chosen correction (Type number to pick a suggestion, or type a different word):
spellcheck >
```

(3) If the user types a replacement not provided in the suggestions list, spellcheck provides a confirmation window:

```
You have typed: johmaped

Are you sure this is the right correction? [y/n]
spellcheck >
```

Interactive Mode continues this process until the end of the file. When finished, interactive mode moves onto the saving file page:

```
File editing successful!
w                     : save file with corrections;
s [~path/name.txt]    : save corrections to new file
r                     : return to program's home screen
q                     : quit program
```

## 4. Batch Mode Description
The user can activate batch mode through the command line directly. The user runs:

```
$ ./spellcheck [~/path/file.txt] [-flag] 
```

Running batch mode edits the given text file through replacing every identified misspelled word with the best possible correction. The corrections are saved to the same file by default.

Furthermore, several flags can be utilized to customize the batch mode process through the command line. These are:

```
-q                     : Quiet mode - The program does not print any statements regarding the replacement process.
-v                     : Verbose mode - The program gives a more detailed summary of the replacement process.
-s [~path/file.txt]  : Saves the edited version to a new text file instead of modifying the original file.
```

If user chooses to utilize the verbose mode, spellcheck produces this list after the program finishes running. The first word on the suggestions list will be the replacement.

```
WORD          LOCATION          REPLACEMENT
jomped        32:18             jumped
fens          32:34             fence
...           ...               ...

Successfully replaced every misspelled word and saved the modifications
```