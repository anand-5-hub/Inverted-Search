#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS		1
#define FAILURE		0


typedef struct file
{
    char f_name[20];
    struct file *link;
}F_node;

typedef struct Sub
{
    int word_count;
    char filename[20];
    struct Sub *sub_link;
}S_node;

typedef struct Main
{
    char word[25];
    int file_count;
    S_node *sub_link;
    struct Main *main_link;
}M_node;

typedef struct hash
{
    int index;
    M_node *main_link;
}hash_t;


void create_database(hash_t HT[], F_node *head);
void display_database(hash_t HT[]);
void search_database(hash_t HT[]);
void save_database(hash_t HT[]);
int update_database(hash_t[],F_node **head);

int validate_files(int argc, char *argv[], F_node **head);
int insert_last(F_node **head, char *f_name);
int check_duplicates(F_node *head, char *f_name);
int print_filenames(F_node *head);
int get_index(char *word);
void delete(F_node **head, char *fname);

#endif
