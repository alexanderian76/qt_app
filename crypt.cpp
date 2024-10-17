#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crypt.h"
#include <QDebug>

unsigned long stringLength(char *str)
{
    unsigned long length = 0;
    while (*str != '\0')
    {
        str++;
        length++;
    }
    return length;
}

void encryptC(char *str, char *code, char* resStr)
{
    unsigned long codeLength = stringLength(code);

    char *tmpStr = (char *)malloc(4 * sizeof(char));
   // char *resStr = (char *)malloc(stringLength(str) * 3 * sizeof(char));

    for (unsigned long i = 0; i < stringLength(str); i++)
    {

        str[i] += (int)code[i % codeLength];

        if ((int)str[i] < 0)
        {
            snprintf(tmpStr, 4 * sizeof(char), "%d", abs((int)str[i]) + 128);
        }
        else
        {
            if ((int)str[i] == 0)
            {
                snprintf(tmpStr, 4 * sizeof(char), "000");
            }
            else if ((int)str[i] < 10)
            {
                snprintf(tmpStr, 4 * sizeof(char), "00%d", (int)str[i]);
            }
            else if ((int)str[i] < 100)
            {
                snprintf(tmpStr, 4 * sizeof(char), "0%d", (int)str[i]);
            }
            else
            {
                snprintf(tmpStr, 4 * sizeof(char), "%d", (int)str[i]);
            }
        }
        for (unsigned long j = i * 3; j < i * 3 + 3; j++)
        {
            resStr[j] = tmpStr[j - 3 * i];
        }
    }

    free(tmpStr);
 //   free(str);
    //return resStr;
}

void decryptC(char *str, char *code, char* resStr)
{
    unsigned long codeLength = stringLength(code);
    char *tmpStr = (char *)malloc(3 * sizeof(char));
   // char *resStr = (char *)malloc(stringLength(str) / 3 * sizeof(char));
    char *tmpInt = (char *)malloc(3 * sizeof(char));

    for (unsigned long i = 0; i <= stringLength(str); i++)
    {
        tmpStr[i % 3] = str[i];
        if (i % 3 == 2)
        {

            for (int j = 0; j < 3; j++)
            {
                tmpInt[j] = (tmpStr[j]);
            }

            if (atoi(tmpInt) > 128)
            {
                resStr[(i + 1) / 3 - 1] = -(atoi(tmpInt) - 128) - code[((i + 1) / 3 - 1) % codeLength];
            }
            else
            {
                resStr[(i + 1) / 3 - 1] = atoi(tmpInt) - code[((i + 1) / 3 - 1) % codeLength];
            }

        }
    }

    free(tmpInt);
    free(tmpStr);
    //free(str);
 //   return resStr;
}
