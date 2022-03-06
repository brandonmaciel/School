GCC version 4.2.1

To compile my source code use the following line:  gcc scanner.c -o scanner

To run the executable use: ./scanner <automata_file.txt> <program_file.txt>
    here automata_file and program_file can be replaced with a file in the format specified in the project description.
    I have included the example from the project description as automata.txt, and have also included
    a program example that follows that automata as program.txt.

run example (this is based on Mac) : gcc scanner.c -o scanner && ./scanner automata.txt program.txt 

Program that will yield an error: gcc scanner.c -o scanner && ./scanner automata.txt program_error.txt