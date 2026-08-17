Inverted Search

📌 Project Overview

Inverted Search is a C-based application that builds an inverted index for a collection of .txt files.

Instead of searching every file from the beginning whenever a word is requested, the project creates a database that stores:

The hash-table index associated with a word

The word itself

The number of files containing the word

Each filename in which the word occurs

The number of times the word occurs in each file

This makes word searching more organized and efficient.

🎯 Objectives

The main objectives of this project are:

Read words from multiple text files.

Validate the input files before processing.

Create an inverted-index database using a hash table.

Maintain word information using linked lists.

Display the complete database.

Search for a word and display the files in which it occurs.

Save the generated database to a backup file.

Update the database when a new file is added.

Load/use the saved database for future operations.

🧠 Core Concept

The project uses a hash table + linked-list data structure.

A word is converted into a hash-table index using get_index().

For every hash-table index:

Hash Table
   |
   +---- Main Node
          |
          +---- Word
          +---- File Count
          |
          +---- Sub Node
                 |
                 +---- Filename
                 +---- Word Count
                 |
                 +---- Sub Node
                        |
                        +---- Filename
                        +---- Word Count

Example

Suppose the input files contain:

f1.txt
hi hello anand

f2.txt
Anand how are hi

The database can maintain information such as:

Word: hi
Files: f1.txt, f2.txt
Count:
    f1.txt -> 1
    f2.txt -> 1

The supplied backup database also demonstrates records such as hi appearing in three files and stores the corresponding per-file word counts.

🏗️ Data Structure

The implementation uses three logical levels.

1. Hash Table

The hash table contains entries for indexes 0 through 26.

Each hash-table entry points to the first main node associated with that index.

hash_t HT[27];

2. Main Node

A main node stores information about a unique word.

Conceptually:

Main Node
---------
word
file_count
main_link
sub_link

word → stores the word.

file_count → number of different files containing the word.

main_link → points to the next word at the same hash index.

sub_link → points to file-specific information.

3. Sub Node

A sub node stores information about one file.

Sub Node
--------
filename
word_count
sub_link

filename → file containing the word.

word_count → number of occurrences of the word in that file.

sub_link → points to the next file containing the same word.

⚙️ Database Creation

The database creation function reads every file in the file linked list.

The implementation opens each file in read mode and processes one word at a time using:

fscanf(fp, "%s", word)

The word is converted into a hash-table index using:

index = get_index(word);

If the word does not already exist at that index:

A main node is created.

A sub node is created.

The word is stored in the main node.

The filename is stored in the sub node.

The initial word count is set to 1.

If the word already exists:

The existing main-node list is traversed.

The corresponding sub-node list is checked.

If the same filename is found, its word count is incremented.

If the filename is not found, a new sub node is created.

The file count for that word is incremented.

This logic is implemented in create_database().

📊 Display Database

The display operation traverses all hash-table indexes and prints the stored information in tabular form.

The output contains:

Index
Filecount
word
Filename
Wordcount

Example format:

---------------------------------------------------------------------------
Index          Filecount      word           Filename       Wordcount
---------------------------------------------------------------------------
7              2              hello          f1.txt         1
                                             f3.txt         1
---------------------------------------------------------------------------

Empty hash-table indexes are skipped.

The main-node list and sub-node list are both traversed to display all stored information.

🔎 Search Operation

The search operation accepts a word from the user and searches the inverted database.

For a word that exists, the program reports:

Word <word> is present in <n> file(s)

In file: <filename> <count> time(s)

If the word is not present, the program reports that the word is not found in the database.

Because the database already contains word-to-file mappings, the search does not need to scan every text file again.

💾 Save Database

The project supports saving the generated database into a backup file.

The supplied project contains:

backup.txt

The backup format stores the hash index, file count, word, filenames, and word counts.

Example records include:

#0;1;anand;f1.txt;1;#
#7;3;hi;f1.txt;1;f2.txt;1;f3.txt;1;#
#7;2;hello;f1.txt;1;f3.txt;1;#

This allows the database information to be preserved instead of rebuilding it from the original text files every time.

🔄 Update Database

The project also provides an Update Database operation.

The update operation accepts a filename and adds its word information to the existing database.

The project validates the file before updating.

Conditions represented by the program include:

File is not present

File is empty

File is not a .txt file

Invalid file

Database successfully updated

Database already updated

📋 Menu

The executable contains the following menu:

1. Create Database
2. Display Database
3. Save Database
4. Search
5. Update Database
6. Exit

Menu Flow

              START
                |
                v
       Validate input files
                |
                v
          Display Menu
                |
        +-------+-------+
        |       |       |
        v       v       v
      Create  Display  Save
        |       |       |
        +-------+-------+
                |
             Search
                |
             Update
                |
              Exit

📁 Project Structure

The executable strings indicate the project is organized around functions/modules such as:

Inverted Search/
│
├── create.c       # Creates the inverted database
├── display.c      # Displays the database
├── search.c       # Searches for a word
├── update.c       # Updates the database
├── save.c         # Saves database information
├── inverted.h     # Data structures and function declarations
├── main.c         # Program entry point/menu
│
├── f1.txt         # Sample input text file
├── f2.txt         # Sample input text file
├── backup.txt     # Saved database
│
└── a.out          # Compiled executable

search.c, update.c, save.c, main.c, and inverted.h were not included among the uploaded source files, but their corresponding functions/strings are present in the supplied executable.

🧪 Sample Input Files

f1.txt

hi hello anand

f2.txt

Anand how are hi

The supplied database backup also references f3.txt.

🛠️ Technologies Used

Language: C

Data Structures:

Hash Table

Singly Linked Lists

File Handling:

fopen()

fclose()

fscanf()

File reading/writing

Dynamic Memory:

malloc()

free() where applicable

String Handling:

strcpy()

strcmp()

strstr()

Compiler: GCC

▶️ Compilation

If all project source files are available in the same directory, compile them using:

gcc *.c

Or explicitly:

gcc main.c create.c display.c search.c update.c save.c -o inverted_search

Run the program using:

./inverted_search

For the supplied executable:

./a.out

🚀 How to Use

Step 1: Provide text files

Keep the input .txt files in the project directory.

Example:

f1.txt
f2.txt
f3.txt

Step 2: Start the program

./inverted_search f1.txt f2.txt f3.txt

The program validates the files and stores valid filenames in its file list.

Step 3: Create the database

Select:

1. Create Database

The program reads the words from each file and constructs the inverted index.

Step 4: Display the database

Select:

2. Display Database

This prints the hash index, word, file count, filename, and word count.

Step 5: Save the database

Select:

3. Save Database

The database is saved to the backup file.

Step 6: Search

Select:

4. Search

Enter a word to find the files containing it and its occurrence count.

Step 7: Update

Select:

5. Update Database

Enter a new .txt filename to add its contents to the existing database.

Step 8: Exit

Select:

6. Exit

💡 Example Search

If the database contains:

hi -> f1.txt -> 1
hi -> f2.txt -> 1
hi -> f3.txt -> 1

Searching for:

hi

produces information equivalent to:

Word hi is present in 3 file(s)

In file: f1.txt 1 time(s)
In file: f2.txt 1 time(s)
In file: f3.txt 1 time(s)

🔑 Key Learning Outcomes

This project provides practical experience with:

Hash tables

Linked lists

Nested linked-list structures

Dynamic memory allocation

File handling in C

Command-line arguments

String manipulation

Database-like indexing

Searching and updating data structures

Saving structured data to a file

Modular C programming

⚠️ Notes

Input files are expected to be text files.

The project checks for file availability and .txt extension validity.

The current create_database() implementation reads words using %s, so punctuation/case normalization is not shown in the supplied implementation.

The supplied sample f2.txt contains Anand with an uppercase A, while f1.txt contains anand in lowercase; the supplied implementation compares words using strcmp(), so these are treated as different strings.

The database display traverses hash indexes from 0 through 26.

👨‍💻 Author

Anand Arabhanvi

C Programming Project — Inverted Search
