#include "inverted.h"

void save_database(hash_t HT[])
{
    char filename[30];

    printf("Enter the filename: ");
    scanf(" %[^\n]", filename);

    if (strstr(filename, ".txt") != NULL) // Check whether file extension is .txt
    {
        FILE *fp = fopen(filename, "w"); // Open file in write mode

        if (fp == NULL) // Check if file opened successfully
        {
            printf("Unable to oepn file\n");
            return;
        }

        for (int i = 0; i <= 26; i++) // Traverse all hash table indexes
        {
            if (HT[i].main_link == NULL) // Skip empty indexes
                continue;

            M_node *Mtemp = HT[i].main_link; // Point to first main node

            while (Mtemp) // Traverse all main nodes
            {
                S_node *Stemp = Mtemp->sub_link; // Point to first sub node

                // Write hash index, file count and word
                fprintf(fp, "#%d;%d;%s;", i, Mtemp->file_count, Mtemp->word);

                while (Stemp) // Traverse all sub nodes
                {
                    // Write filename and word count
                    fprintf(fp, "%s;%d;", Stemp->filename, Stemp->word_count);

                    Stemp = Stemp->sub_link; // Move to next sub node
                }

                fprintf(fp, "#\n"); // End of one database record

                Mtemp = Mtemp->main_link; // Move to next main node
            }
        }

        fclose(fp); // Close the file

        printf("\nINFO: Database is saved\n\n");
    }
}