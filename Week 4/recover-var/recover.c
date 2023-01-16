#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;

    //check for a filename
    if (argc != 2)
    {
        printf("enter a valid filename\n");
        return 1;
    }

    //open file
    FILE *fin = fopen(argv[1], "r");



    //declare variables
    BYTE buffer[512];  // creating a buffer for a block
    int count = 0;     // to keep track of the number of files for naming
    FILE *fout = NULL;
    char name[10];




    //read file to buffer
    while (fread(&buffer, sizeof(buffer), 1, fin) == 1)
    {
        // if the start of a new pic
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if this isn't the first file
            if (count != 0)
            {
                // close the file
                fclose(fout);
            }

            // open new file
            char filename[9];
            sprintf(filename, "%03i.jpg", count);
            fout = fopen(filename, "w");
            count++;

        }

        if (fout != NULL)
        {
            fwrite(&buffer, 512, 1, fout);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}