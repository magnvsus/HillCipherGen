/*============================================================================
| Assignment: pa02 - Encrypting a plaintext file using the Hill cipher
| Author: Michael Wang
| Language: c
| To Compile: gcc -o pa02 pa02.c
| To Execute: c -> ./pa02 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is the plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
| Class: CIS3360 - Security in Computing - Summer 2026
| Instructor: McAlpin
| Due Date: TODO
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //-- Check if valid number of arguments is given.
    if (argc != 3) {
        fprintf(stderr, "Invalid args: pa02.c <keytext file> <plaintext file>");
        return 1;
    }

    //-- Open file from argv 1   
    FILE* kfile = fopen(argv[1], "r");
    FILE* pfile = fopen(argv[2], "r"); 
    if (kfile == NULL) {
        fprintf(stderr, "Invalid keytext filename.");
        return 1;
    }
    if (pfile == NULL)
    {
        fprintf(stderr, "Invalid plaintext filename.");
        return 1;
    }

    

    //kX IN
    //--Read size
    unsigned int size;
    fscanf(kfile, "%u", &size);

    unsigned int in = 0;
    unsigned int key[size][size];
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fscanf(kfile, "%u", &in);
            key[i][j] = in;
            printf("[%d,%d]=%u\n", i, j, key[i][j]);
        }
    }
    //printf("size: %u", size);


    fclose(pfile);
    fclose(kfile);
    return 0;
}

/*=============================================================================
| I, Michael Wang (mi993440) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/