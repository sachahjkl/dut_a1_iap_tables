# dut_a1_iap_tables

The project aims to program a command interpreter for a data table.
Eight commands must be programmed:


    * three commands for processing a table:
        - creation
        - deletion
        - display of its schema
    * five commands for manipulating data in an existing table:
        - insertion
        - deletion
        - single-criterion selection
        - display of a specified record
        - display of all records

**This project handles four data types:**

    * integers (INT)
    * real numbers (FLOAT)
    * character strings (TEXT) (limited by a MAX size)
    * dates (DATE).

The application must interpret nine commands: eight data table commands and one command to exit the interpreter.
These commands are represented as unaccented character strings in the formats specified in this document.
The separator between the command and the different information fields is the space character.
Commands can be entered through standard input (the keyboard) or by redirecting a text file to standard input.
