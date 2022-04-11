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

char* substring(char s[], int start_index, int end_index) {
    int len = string_length(s);
    char* o = s; 
    if(start_index < 1 || end_index > len) return NULL;

    for (int i = start_index -1 ; i < end_index; i++)
    {
        o[i] = s[i];
    }
    o[end_index] = '\0';
    return o;
}

void append(char s[], char n)
{
    int len = string_length(s);
    if(len >= MAX_BUFFER_LEN)
        return;
    s[len] = n;
    s[len+1] = '\0';
}



