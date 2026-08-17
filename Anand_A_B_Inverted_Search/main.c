/*
    Title       : Inverted Search
    Name        : Anand Arabhanvi
    ID          : int26001_128
    Date        : 23/07/2026
    Description :   The Inverted Search project creates an efficient word-based indexing
                    system for multiple text files. It reads the input files provided through
                    command-line arguments, validates them, and builds an inverted index using
                    a hash table and linked lists. Each unique word is stored along with the
                    list of files in which it appears and the number of occurrences in each
                    file. The project supports creating, displaying, searching, saving, and
                    updating the database through a menu-driven interface, enabling fast word
                    lookup without scanning all files repeatedly.
    */

#include "inverted.h"

int main(int argc, char *argv[])
{
    F_node *head = NULL; // Head pointer for file linked list
    hash_t HT[27]; // Hash table with 27 indexes

    for (int i = 0; i < 27; i++) // Initialize hash table
    {
        HT[i].index = i;
        HT[i].main_link = NULL;
    }

    // Validate input files
    if (validate_files(argc, argv, &head))
    {
        printf("INFO : Validation successful\n\n");
        printf("\n");
    }
    else
    {
        printf("Insufficient arguments\n\n");
        printf("Arguments: ./a.out <filename.txt>....\n");
        return 1;
    }

    print_filenames(head); // Display validated filenames

    if (head == NULL) // Check if file list is empty
    {
        printf("INFO : files are not there\n");
        printf("Create database is not possible\n-NULL\n");
        return -1;
    }

    int d_flag = 0, u_flag = 0; // Flags to avoid repeated operations
    int option;

    do
    {
        // Display menu
        printf("Select your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : ");

        scanf("%d", &option); // Read user choice

        switch (option)
        {
            case 1:
                if (d_flag != 0) // Check whether database is already created
                {
                    printf("INFO: Database is already is created\n\n");
                    break;
                }

                create_database(HT, head); // Create database
                d_flag = 1; // Set database created flag
                break;

            case 2:
                display_database(HT); // Display database
                break;

            case 3:
                save_database(HT); // Save database into file
                break;

            case 4:
                search_database(HT); // Search a word
                break;

            case 5:
                if (u_flag != 0) // Check whether database is already updated
                {
                    printf("INFO : Database is already updated\n\n");
                    break;
                }

                if (update_database(HT, &head)) // Update database from saved file
                {
                    printf("INFO : Database updated successfully\n\n");
                }
                else
                {
                    printf("INFO : Database is not updated\n\n");
                }

                u_flag = 1; // Set update flag
                break;

            case 6:
                break; // Exit program

            default:
                printf("INFO : Please enter the valid option\n");
        }

    } while (option != 6); // Repeat until user selects Exit

    return 0; 
}