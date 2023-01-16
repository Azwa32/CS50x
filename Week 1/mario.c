#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // Requests pyramid height
    int h = get_int("Height: ");

    // Pyramid return values

    // Pyramid 1 step
    if (h == 1)
    {
        printf("#  #\n");
    }
    // Pyramid 2 step
    else if (h == 2)
    {
        printf(" #  #\n##  ##\n");
    }
    // Pyramid 3 step
    else if (h == 3)
    {
        printf("  #  #\n ##  ##\n###  ###\n");
    }
    // Pyramid 4 step
    else if (h == 4)
    {
        printf("   #  #\n  ##  ##\n ###  ###\n####  ####\n");
    }
    // Pyramid 5 step
    else if (h == 5)
    {
        printf("    #  #\n   ##  ##\n  ###  ###\n ####  ####\n#####  #####\n");
    }
    // Pyramid 6 step
    else if (h == 6)
    {
        printf("     #  #\n    ##  ##\n   ###  ###\n  ####  ####\n #####  #####\n######  ######\n");
    }
    // Pyramid 7 step
    else if (h == 7)
    {
        printf("      #  #\n     ##  ##\n    ###  ###\n   ####  ####\n  #####  #####\n ######  ######\n#######  #######\n");
    }
    // Pyramid 8 step
    else if (h == 8)
    {
        printf("       #  #\n      ##  ##\n     ###  ###\n    ####  ####\n   #####  #####\n  ######  ######\n #######  #######\n########  ########\n");
    }
    //for other value run program again
    else
    {
        main();
    }
}