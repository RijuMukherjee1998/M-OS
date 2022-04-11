#include "../include/utils.h"

unsigned int string_length(char s[])
{
    int l = 0;
    while (s[l] != '\0')
    {
        l++;
    }
    return l;
}

int compare_string(char s1[], char s2[]) {
    int i;
    int l1 = string_length(s1);
    int l2 = string_length(s2);
    if(l1 == l2)
    {
        for (int i = 0; i < l1; i++)
        {
            if(s1[i] != s2[i]) return -999;
        }
    }
    else 
    {
        return l1 - l2;
    }
    return 0; 
}

void append(char s[], char n)
{
    int len = string_length(s);
    if(len >= MAX_BUFFER_LEN)
        return;
    s[len] = n;
    s[len+1] = '\0';
}

