/*******************************************************************************
 * vigenere.c
 *
 * Computer Science 50x
 * Rick Warrington
 *
 * Encrypts text using a vigenere cipher which uses a word as the key to
 * encrypt the text.
 *
 * Usage:
 * ./vigenere <keyword>
 * [input]
 *
 ******************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function prototypes
int GetOffset(char character);
char ShiftCharacter(char character, int offset);

int main(int argc, char *argv[]) 
{
    // check command line argument count
    if(argc != 2)
    {
        printf("Usage: ./vigenere <keyword>\n");
        return 1;
    }

    // get key from command line arguments
    string key = argv[1];
    int key_length = strlen(key);

    // check that the key is only alpha characters
    for(int i = 0; i < key_length; i++)
    {
        // reject any non-alpha characters
        if(!isalpha(key[i]))
        {
            printf("Key must be alpha characters only.\n");
            return 1;
        }
    }

    // get user input
    string input = GetString();

    // apply vigenere cipher
    int offset = 0;
    int key_char = 0;  // keep track of which character in the key to use
    for(int i = 0, j = strlen(input); i < j; i++)
    {
        // only opperate on alpha characters and skip everything else
        if(isalpha(input[i]))
        {
            // apply shift
            offset = GetOffset(key[key_char % key_length]);
            input[i] = ShiftCharacter(input[i], offset);
            key_char++;
        }
    }

    // display result
    printf("%s\n", input);

    return 0;
}

/*
 * Calculates the offset of a character from the beginning of the alphabet,
 * where a or A equals 0 and z or Z equals 25.
 * precondition : character is the character which is having its offset found.
 * postcondition: returns an integer which is the number of characters away
 *  from a the input character is. a result of -1 indicates an error.
 */
int GetOffset(char character) 
{
    int offset = -1;

    // calculate the shift correctly for upper and lower case letters
    if(character >= 'a' && character <= 'z')
        offset = (character - 'a') % 26;

    if(character >= 'A' && character <= 'Z')
        offset = (character - 'A') % 26;

    return offset;
}

/*
 * Applies a shift cipher to a single character given a numerical offset of
 * which to shift.
 * precondition : character is the letter to be shifted, and offset is the
 *  amount of shift to be applied to the character.
 * postcondition: returns a new character which is the result of shifting the
 *  input character by offset characters.
 */
char ShiftCharacter(char character, int offset)
{
    char new_char = ' ';

    // apply the shift correctly for upper or lowercase letters
    if(character >= 'a' && character <= 'z')
        new_char = 'a' + (((character - 'a') + offset) % 26);

    if(character >= 'A' && character <= 'Z')
        new_char = 'A' + (((character - 'A') + offset) % 26);

    return new_char;
}
