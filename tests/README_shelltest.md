# CLI Testing
The spellcheck team is testing the command line inputs using the ShelltestRunner program.

The program takes in input, expected output, expected stderr, and expected stdout.
It is important to note that the program is very precise in the sense that it even counts all the white spaces in between the lines. Therefore, it is really important to make sure all the white spaces are included in the expected outcomes, otherwise the tests fail.

## How to download the program

Instructions on downloading the program and its further use can be found in the following link: https://github.com/simonmichael/shelltestrunner

For our purposes, the information that I outlined below should be enough. You can download the program by downloading stack(https://haskell-lang.org/get-started) first, and then you need to run the following in your terminal:

stack install shelltestrunner-1.9


## How to generate a test file
The test fails need to have .test extendion. You can generate a test file with the command "vim [testname].test"


## How to run the tests
Command for running the batch tests:
shelltest tests/cli_batch.test

NOTE: If the terminal says "shelltest:not found", you may need to run the following in your terminal:
export PATH=$PATH:/Users/[your user name]/.local/bin

-----------------------------------------------------------
## Useful flags for debugging purposes
Some flags that make it easier to spot the differences are as follows:

-d only shows the differences between the expected and the actual, and ignores the parts that actually match.

-p shows all the expected and actual output including all the whitespaces, indicated with a "\n"
NOTE: you should not write \n while writing the expected outputs. The program automatically translates whitespaces into \n. You should write the output as if you are writing it into the terminal.

-a shows all output without shortening it.

Recommended flags to run the test
shelltest -p tests/cli_batch.test
shelltest -p -a tests/cli_batch.test
shelltest -a -p -d tests/cli_batch.test
