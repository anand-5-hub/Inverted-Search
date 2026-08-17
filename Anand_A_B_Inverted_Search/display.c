#include "inverted.h"

void display_database(hash_t HT[])
{
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-15s%-15s%-15s%-15s%-15s\n", "Index", "Filecount", "word", "Filename", "Wordcount"); 
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i <= 26; i++) // Traverse all hash table indexes
    {
        if (HT[i].main_link == NULL) // Skip empty indexes
            continue;

        M_node *Mtemp = HT[i].main_link; // Point to first main node

        while (Mtemp) // Traverse all main nodes
        {
            S_node *Stemp = Mtemp->sub_link; // Point to first sub node

            
            printf("%-15d%-15d%-15s%-15s%-15d\n",
                   i, Mtemp->file_count, Mtemp->word,
                   Stemp->filename, Stemp->word_count);

            Stemp = Stemp->sub_link; // Move to next sub node

            while (Stemp) // Print remaining sub nodes
            {
                printf("%-45s%-15s%-15d\n",
                       " ", Stemp->filename, Stemp->word_count);

                Stemp = Stemp->sub_link; // Move to next sub node
            }

            Mtemp = Mtemp->main_link; // Move to next main node
        }
    }

    printf("-----------------------------------------------------------------------------------\n\n"); 
}