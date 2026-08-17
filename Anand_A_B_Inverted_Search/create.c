#include "inverted.h"

void create_database(hash_t *HT, F_node *head)
{
    F_node *Ftemp = head; // Temporary pointer to traverse the file linked list
    int index;

    while (Ftemp) // Traverse all files
    {
        char word[50];

        FILE *fp = fopen(Ftemp->f_name, "r"); // Open file in read mode

        if (fp == NULL) // If file cannot be opened, move to next file
        {
            Ftemp = Ftemp->link;
            continue;
        }

        while (fscanf(fp, "%s", word) == 1) // Read one word at a time
        {
            index = get_index(word); // Get hash index for the word

            if (HT[index].main_link == NULL) // If no main node exists
            {
                M_node *Mnew = malloc(sizeof(M_node)); // Create main node
                S_node *Snew = malloc(sizeof(S_node)); // Create sub node

                HT[index].main_link = Mnew; // Update hash table

                strcpy(Mnew->word, word); // Store word
                Mnew->main_link = NULL;
                Mnew->sub_link = Snew; // Link sub node
                Mnew->file_count = 1; // First file containing this word

                strcpy(Snew->filename, Ftemp->f_name); // Store filename
                Snew->sub_link = NULL;
                Snew->word_count = 1; // First occurrence
            }
            else
            {
                M_node *Mtemp = HT[index].main_link; // Traverse main nodes

                while (Mtemp)
                {
                    if (strcmp(Mtemp->word, word) == 0) // Word already exists
                    {
                        S_node *Stemp = Mtemp->sub_link; // Traverse sub nodes

                        while (Stemp)
                        {
                            if (strcmp(Stemp->filename, Ftemp->f_name) == 0) // Same file found
                            {
                                Stemp->word_count++; // Increment word count
                                break;
                            }

                            if (Stemp->sub_link == NULL) // File not found
                            {
                                S_node *Snew = malloc(sizeof(S_node)); // Create new sub node

                                strcpy(Snew->filename, Ftemp->f_name);
                                Snew->word_count = 1;
                                Snew->sub_link = NULL;

                                Stemp->sub_link = Snew; // Link new sub node
                                Mtemp->file_count++; // Increment file count

                                break;
                            }

                            Stemp = Stemp->sub_link; // Move to next sub node
                        }

                        break; // Word processed
                    }
                    else
                    {
                        if (Mtemp->main_link == NULL) // Word not present in main list
                        {
                            M_node *Mnew = malloc(sizeof(M_node)); // Create new main node
                            S_node *Snew = malloc(sizeof(S_node)); // Create new sub node

                            strcpy(Mnew->word, word);
                            Mnew->file_count = 1;
                            Mnew->sub_link = Snew;
                            Mnew->main_link = NULL;

                            strcpy(Snew->filename, Ftemp->f_name);
                            Snew->word_count = 1;
                            Snew->sub_link = NULL;

                            Mtemp->main_link = Mnew; // Attach new main node

                            break;
                        }
                    }

                    Mtemp = Mtemp->main_link; // Move to next main node
                }
            }
        }

        printf("INFO : Successful : Creation of DATABASE for file: %s\n\n", Ftemp->f_name);

        fclose(fp); // Close current file

        Ftemp = Ftemp->link; // Move to next file
    }
}