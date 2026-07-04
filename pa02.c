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
<<<<<<< Updated upstream
| Due Date: TODO
=======
| Due Date: 2026.07.07
>>>>>>> Stashed changes
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns alphabet index of char ('a' = 0)
static inline unsigned int toIndex(char in){ return (unsigned int)(in - 'a'); }
//Returns char from alphabet index ('a' = 0)
static inline char toAscii(unsigned int index){ return ((char)index) + 'a'; }

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

    //-- Get size of file
    // Send cursor to end, then ftell
    fseek(pfile, 0, SEEK_END);
    unsigned int fileSize = (unsigned int)ftell(pfile);
    
    // Return cursor to start
    fseek(pfile, 0, SEEK_SET);
    char input[fileSize+1], output[fileSize+1];
    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));

    //kX IN
    //--Read size
    unsigned int size;
    fscanf(kfile, "%u", &size);

    //--Read Matrix
    unsigned int din = 0;
    unsigned int key[size][size];
    printf("\nKey matrix:\n");
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fscanf(kfile, "%u", &din);
            key[i][j] = din;
            printf("\t%u", din);
        }
        printf("\n");
    }

    //pX ENCRYPT
    unsigned int block[size];
    memset(block, 0, sizeof(block)); 
    unsigned int calc[size];
    memset(calc, 0, sizeof(calc)); 
    
    //Read and Encrypt Loop
    char  cin = 0;
    unsigned int done = 0, incount = 0, outcount = 0, padcount = 0, padding = 0;
    while(!done){
        //--File read loop
        for(int i = 0; i < size; i++)
        {   // -Read char
            cin = fgetc(pfile);
<<<<<<< Updated upstream
=======
            
>>>>>>> Stashed changes
            // -End of file condition
            if(cin == EOF) 
            {   // -Check if last block was filled. Difference is padding count.
                padding = size - padcount;
<<<<<<< Updated upstream
                done = 1;
=======
                if(padding == size) padding = 0;
                done = 1;
                break;
>>>>>>> Stashed changes
            }   // -Valid char condition
            else if((cin >= 'a' && cin <= 'z') || (cin >= 'A' && cin <= 'Z'))
            {   // -Convert uppercase to lowercase
                if(cin < 'a') cin += 32;    
                block[i] = toIndex(cin);
                input[incount++] = cin;
                padcount++;
            }   // -Invalid char condition
            else 
            {
                i--;
            }
        }
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
        //--Padding addition loop
        for(int i = 0; i < padding; i++)
        {   // -Add padding using padding var
            block[size - padding + i] = toIndex('x');
            input[incount++] = 'x';
        }   
        padcount = 0;

        //--Encryption loop
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
                calc[i] += (key[i][j]*block[j]);
            output[outcount++] = toAscii(calc[i]%26);
            memset(calc, 0, sizeof(calc)); 
        }
    }
    
    input[incount] = '\0';
    output[outcount] = '\0';

    //--Output P and C (80 char max/line)
    unsigned int pcount = 0;
    printf("\nPlaintext:\n");
    for(int i = 0; i < incount; i++)
    {
        if(pcount == 80)
        {
            printf("\n");
            pcount = 0;
        }
        printf("%c", input[i]);
        pcount++;
    }
    printf("\n\nCiphertext:\n");
    pcount = 0;
    for(int i = 0; i < incount; i++)
    {
        if(pcount == 80)
        {
            printf("\n");
            pcount = 0;
        }
        printf("%c", output[i]);
        pcount++;
    }
    printf("\n");

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