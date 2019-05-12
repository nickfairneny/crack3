#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "md5.h"

const int PASS_LEN=50;        // Maximum any password can be
const int HASH_LEN=33;        // Length of MD5 hash strings
int size;


// Stucture to hold both a plaintext password and a hash.
struct entry 
{
    // TODO: FILL THIS IN
    char password[50];
    char hash[33];
    
};

int file_length(char *filename)
{
	struct stat info;
	if (stat(filename, &info) == -1) return -1;
	else return info.st_size;
	
}

// TODO
// Read in the dictionary file and return an array of structs.
// Each entry should contain both the hash and the dictionary
// word.
struct entry *read_dictionary(char *filename, int *size)
{
    int filelength = file_length(filename);
    
    FILE *c = fopen(filename, "r");
    if(!c)
    {
        printf("Can't open %s for reading", filename);
    }

    char *contents = malloc(filelength);
    fread(contents, 1, filelength, c);
    fclose(c);
    
    int lines = 0;
    
    for (int i = 0; i < filelength; i++)
    {
        if (contents[i] == '\n') 
        {
            contents[i] = '\0';
            lines++;
        }
    }
    
    struct entry *cc = malloc(lines * sizeof(struct entry));
    
    for (int i = 0; i < filelength; i++)
    {
        if (contents[i] == '\0')
        {
            strcpy(cc[0].password, &contents[0]);
            cc[0].password = strlen(cc[0], password);
            char *nextcc = &contents[i] + 1;
            //cc[lines].password = nextcc;
        }
    }
    
    *size = lines;
    return cc;
}

int comp(const void *a, const void *b)
    {
        
        struct entry *ca = (struct entry *)a;    
        struct entry *cb = (struct entry *)b; 
        return strcmp((*ca).password, (*cb).password);
        
    }

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }
    
    int dictlen = file_length(argv[1]);
    // TODO: Read the dictionary file into an array of entry structures
    struct entry *dict = read_dictionary(argv[1], &dictlen);
    
    // TODO: Sort the hashed dictionary using qsort.
    // You will need to provide a comparison function.
    
    qsort(dict, size, sizeof(struct entry), comp);

    // TODO
    // Open the hash file for reading.
    FILE *h = fopen(argv[2], "r");
    if(!h)
    {
        printf("Can't open %s for reading", argv[2]);
    }

    // TODO
    // For each hash, search for it in the dictionary using
    // binary search.
    // If you find it, get the corresponding plaintext dictionary word.
    // Print out both the hash and word.
    // Need only one loop. (Yay!)

    int dlen;
    struct entry *chars = read_dictionary("hashes.txt", &dlen);
    char target[50];
    
    for (int i = 0; i < sizeof(dict); i++)
    {
        strcpy(target, chars[i].hash);
        
        struct entry *found = bsearch(target, h, dlen, sizeof(struct entry), comp);
        
        if (found == NULL)
        {
            printf("Not found\n");
        }
        else
        {
            printf("Found %s %s\n", found->password, found->hash);
        }
}
    
    
}
