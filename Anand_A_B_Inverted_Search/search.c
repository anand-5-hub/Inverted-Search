#include "inverted.h"

void search_database(hash_t HT[])
{
    char word[20];

    printf("Enter the word to search: ");
    scanf(" %[^\n]", word);

    int index = get_index(word); // Get hash index of the word

    M_node *Mtemp = HT[index].main_link; // Point to first main node

    printf("----------------------------------------------------------------------------------\n");

    while (Mtemp) // Traverse main node list
    {
        if (strcmp(Mtemp->word, word) == 0) // Check whether word matches
        {
            printf("Word %s is present in %d file(s)\n", Mtemp->word, Mtemp->file_count);

            S_node *Stemp = Mtemp->sub_link; // Point to first sub node

            while (Stemp) // Traverse all sub nodes
            {
                printf("In file: %s %d time(s)\n", Stemp->filename, Stemp->word_count);

                Stemp = Stemp->sub_link; // Move to next sub node
            }

            printf("----------------------------------------------------------------------------------\n\n");

            return; 
        }

        Mtemp = Mtemp->main_link; // Move to next main node
    }

    
    printf("INFO : word '%s' is not found in database.\n", word);
    printf("----------------------------------------------------------------------------------\n\n");
}