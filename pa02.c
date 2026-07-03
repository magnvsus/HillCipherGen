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

unsigned int getAlpha(char letter);
unsigned int getNumber(char number);
char getAscii(unsigned int index);

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

    //TEST
    //TODO Remove
    // printf("%c= %u\n", 'a', getAlpha('a'));
    // printf("%c= %u\n", 'z', getAlpha('z'));
    // printf("%u= %c\n", 10, getAscii((unsigned int)10));
    // printf("%u= %c\n", 27, getAscii((unsigned int)27));
    // printf("%c= %u\n", '0', getNumber('0'));
    // printf("%c= %u\n", '9', getNumber('9'));

    //kX IN
    //--Read size
    unsigned int size;
    fscanf(kfile, "%u", &size);

    //--Read Matrix
    unsigned int din = 0;
    unsigned int key[size][size];
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fscanf(kfile, "%u", &din);
            key[i][j] = din;
            //TODO REMOVE
            //printf("[%d,%d]=%u\n", i, j, key[i][j]);
        }
    }
    //printf("size: %u", size);

    //pX ENCRYPT
    unsigned int block[size];
    unsigned int calc[size];
    
    char done = 0, cin = 0, count = 0;
    while(!done){
        printf("%d\n", count);

        //--Read file into blocks of size n
        for(int i = 0; i < size; i++)
        {
            ;
            if((cin = fgetc(pfile)) == EOF) 
            {
                done = 1;
                break;
            }
            if(block[i] > 9)
                block[i] = getAlpha(cin);
            else block[i] = getNumber(cin);
        }
        //--Encrypt roots
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                calc[i] += key[i][j]*block[j];
            }
            calc[i] = calc[i]%26;
            printf("\t%d: %u\n", i, calc[i]);
        }
        count++;
    }

    fclose(pfile);
    fclose(kfile);
    return 0;
}

unsigned int getAlpha(char letter)
{   //Returns alphabet index of char (a = 0)
    return (unsigned int)(letter - 'a');
}
unsigned int getNumber(char number)
{
    //Returns correct decimal number from char
    return (int)(number - 22);
}

char getAscii(unsigned int index)
{   //Returns char from alphabet index (a = 0)
    if(index > 25) return ((char)index) + 22;
    return ((char)index) + 'a';
}

/*=============================================================================
| I, Michael Wang (mi993440) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/