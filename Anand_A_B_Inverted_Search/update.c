#include "inverted.h"

// Function to update the hash table from a saved database file
int update_database(hash_t HT[], F_node **head)
{
    char filename[50];

    // Read database filename from user
    printf("Enter the filename: ");
    scanf(" %[^\n]", filename);

    // Check whether the file has .txt extension
    if (strstr(filename, ".txt") == NULL)
    {
        printf("INFO: %s => This is not a .txt file\n\n", filename);
        return FAILURE;
    }

    // Open the file in read mode
    FILE *fp = fopen(filename, "r");

    // Check whether file exists
    if (fp == NULL)
    {
        printf("File is not present\n");
        return FAILURE;
    }

    // Check whether the file is empty
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        printf("File is empty\n");
        fclose(fp);
        return FAILURE;
    }

    // Move file pointer back to beginning
    fseek(fp, 0, SEEK_SET);

    // Read first and last characters to validate file format
    char first = fgetc(fp);
    fseek(fp, -2, SEEK_END);
    char last = fgetc(fp);
    rewind(fp);

    // Database file should start and end with '#'
    if ((first != '#' && last != '#'))
    {
        printf("Invalid File\n");
        fclose(fp);
        return FAILURE;
    }

    char word[50], file[50];
    int index, f_count, w_count;

    // Read one main node at a time from the database file
    while (fscanf(fp, "#%d;%d;%[^;];", &index, &f_count, word) == 3)
    {
        // Create a new main node
        M_node *Mnew = malloc(sizeof(M_node));

        if (Mnew == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        strcpy(Mnew->word, word); // Store word
        Mnew->main_link = NULL; // Initialize main link
        Mnew->sub_link = NULL; // Initialize sub link
        Mnew->file_count = f_count; // Store file count

        S_node *temp = NULL;

        // Read all sub nodes (file information)
        for (int i = 0; i < f_count; i++)
        {
            // Read filename and word count
            fscanf(fp, "%[^;];%d;", file, &w_count);

            // Allocate memory for sub node
            S_node *Snew = malloc(sizeof(S_node));

            // Add filename into file list if it doesn't exist
            if (check_duplicates(*head, file) == SUCCESS)
            {
                insert_last(head, file);
            }

            // Remove filename from file linked list
            delete(head, file);

            // Check memory allocation
            if (Snew == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            strcpy(Snew->filename, file); // Store filename
            Snew->word_count = w_count; // Store word count
            Snew->sub_link = NULL; // Initialize sub link

            // Attach first sub node
            if (Mnew->sub_link == NULL)
            {
                Mnew->sub_link = Snew;
            }
            else
            {
                // Link remaining sub nodes
                temp->sub_link = Snew;
            }

            temp = Snew; // Move temp to newly created node
        }

        
        fscanf(fp, "#\n");

        // Insert new main node into hash table
        if (HT[index].main_link == NULL)
        {
            HT[index].main_link = Mnew;
        }
        else
        {
            M_node *Mtemp = HT[index].main_link;

            // Traverse till last main node
            while (Mtemp->main_link != NULL)
                Mtemp = Mtemp->main_link;

            // Attach new main node
            Mtemp->main_link = Mnew;
        }
    }

    fclose(fp); // Close the file

    print_filenames(*head); // Display remaining filenames

    return SUCCESS;
}