/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 20, 2017
 * Filename:        testme.c
 *
 * Overview:
 * This is a random tester.
 ************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int mode = 1;

char inputChar()
{
    int i;
    char c;
    static char charset1[] = " !#\"$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    static char charset2[] = " !#\"$%&'()*+,-./:;<=>?@[]^_`ax{|}~";
    static char charset3[] = " ()[]ax{}";

    if (mode == 0)
    {
        i = rand() % (int)(sizeof(charset1) - 1);
        c = charset1[i];
    }
    else if (mode == 1)
    {
        i = rand() % (int)(sizeof(charset2) - 1);
        c = charset2[i];
    }
    else
    {
        i = rand() % (int)(sizeof(charset3) - 1);
        c = charset3[i];
    }

    return c;
}

char *inputString()
{
    int i, len;
    char c;
    static char charset1[] = " !#\"$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    static char charset2[] = "abcdefghijklmnopqrstuvwxyz";
    static char charset3[] = "rest";
    len = 6;
    char cstring[len];
    char *p;

	if (mode == 0)
    {
        for (i = 0; i < len-1; i++)
        {
            int j = rand() % (int)(sizeof(charset1) - 1);
            c = charset1[j];
            cstring[i] = c;
        }
    }
    else if (mode == 1)
    {
        for (i = 0; i < len-1; i++)
        {
            int j = rand() % (int)(sizeof(charset2) - 1);
            c = charset2[j];
            cstring[i] = c;
        }
    }
    else
    {
        for (i = 0; i < len-1; i++)
        {
            int j = rand() % (int)(sizeof(charset3) - 1);
            c = charset3[j];
            cstring[i] = c;
        }
    }

    cstring[5] = '\0';
    p = &cstring[0];
    return p;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
