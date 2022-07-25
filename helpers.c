#include <ctype.h>
#include <stdlib.h>

/** Generate a random alphanumeric symbol
 * -------------------------------------
 * Arguments:
 * - void
 * 
 * Procedure:
 * - Generate random alphanumeric symbol based on the ASCII table
 * 
 * Return:
 * - char: randomic alphanumeric character
 * */
char randomAlphaNum(void)
{
    char c;
    do
    {
        c = '0' + rand() % ('z' - '0');
    } while (!isalnum(c));
    return c;
}

/** Generate a random string of alphanumeric symbols
 * ------------------------------------------------
 * Arguments:
 * - dest: char*: the destination buffer to the string
 * - length: int: the size of the string to generate
 * 
 * Procedure:
 * - Fill in the buffer 'dest' with random alphanumeric characters.
 * 
 * Return:
 * - void
 * */
void randomString(char *dest, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        dest[i] = randomAlphaNum();
    }
    dest[i] = '\0';
}

