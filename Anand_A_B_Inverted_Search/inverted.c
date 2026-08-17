#include "inverted.h"

/* Function definitions */

int validate_files(int argc, char *argv[], F_node **head)
{
    if (argc >= 2) // Check if at least one filename is given
    {
        for (int i = 1; i < argc; i++) // Traverse all command line arguments
        {
            if (strstr(argv[i], ".txt")) // Check whether file extension is .txt
            {
                FILE *fp = fopen(argv[i] , "r"); // Open file in read mode
                if (fp == NULL)
                {
                    printf("INFO :  %s => File not found\n",argv[i]);
                }
                else
                {
                    fseek(fp , 0, SEEK_END); // Move to end of file
                    int size = ftell(fp); // Get file size
                    rewind(fp); // Move file pointer to beginning

                    if (size != 0) // Check whether file is empty
                    {
                        if ((check_duplicates(*head, argv[i]))) // Check whether filename already exists
                        {
                            insert_last(head, argv[i]); // Insert filename into linked list
                            printf("INFO: Successfull: inserting file name %s into file linked list\n\n", argv[i]);
                        }
                        else
                        {
                            printf("INFO: %s => This file is repeated, so it will not store into the sll\n\n", argv[i]);
                        }
                    }
                    else
                    {
                        printf("INFO: %s => This file is empty\n\n",argv[i]);
                    }

                    fclose(fp); // Close the file
                }
            }
            else
            {
                printf("INFO: %s => This file has not a .txt file\n\n",argv[i]);
            }
        }

        return SUCCESS;
    }
    else
    {
        return FAILURE; // No input files given
    }
}

int check_duplicates(F_node *head, char *f_name)
{
    if (head == NULL) // Linked list is empty
        return SUCCESS;

    F_node *temp = head; // Start from first node

    while (temp != NULL) // Traverse linked list
    {
        if (strcmp(temp->f_name, f_name) == 0) // Compare filenames
        {
            return FAILURE; // Duplicate found
        }

        temp = temp->link; // Move to next node
    }

    return SUCCESS; // No duplicate found
}

int insert_last(F_node **head, char *f_name)
{
    F_node *new = malloc(sizeof(F_node)); // Allocate memory for new node

    if (new == NULL)
        return FAILURE;

    strcpy(new->f_name, f_name); // Copy filename
    new->link = NULL; // New node points to NULL

    if (*head == NULL) // If list is empty
    {
        *head = new; // Make new node as head
        return SUCCESS;
    }

    F_node *temp = *head; // Start from head

    while (temp->link != NULL) // Traverse till last node
    {
        temp = temp->link;
    }

    temp->link = new; // Insert node at end

    return SUCCESS;
}

int print_filenames(F_node *head)
{
    if (head == NULL) // Check if list is empty
        return FAILURE;

    F_node *temp = head; // Start from head

    printf("head ->");

    while (temp != NULL) // Traverse linked list
    {
        printf("%s -> ", temp->f_name);
        temp = temp->link; // Move to next node
    }

    printf("NULL\n");
    printf("\n");

    return SUCCESS;
}

int get_index(char *word)
{
    if (word[0] >= 'a' && word[0] <= 'z') // Lowercase alphabet
    {
        return (word[0] - 'a');
    }
    else if (word[0] >= 'A' && word[0] <= 'Z') // Uppercase alphabet
    {
        return (word[0] - 'A');
    }
    else
    {
        return 26; // Non-alphabet character
    }
}

void delete(F_node **head, char *fname)
{
    F_node *temp = *head; // Start from head
    F_node *prev = NULL; // Previous node pointer

    while (temp) // Traverse linked list
    {
        if (strcmp(fname, temp->f_name) == 0) // Filename found
        {
            if (prev == NULL) // Deleting first node
            {
                *head = temp->link;
            }
            else // Deleting middle or last node
            {
                prev->link = temp->link;
            }

            free(temp); // Free deleted node
            return;
        }

        prev = temp; // Move previous pointer
        temp = temp->link; // Move current pointer
    }
}