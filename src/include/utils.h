#ifndef UTILS_H
#define UTILS_H
#define MAX_BUFFER_LEN 256
#define NULL 0

unsigned int string_length(char s[]);
int compare_string(char s1[], char s2[]);
char* substring(char s[], int start_index, int end_index);
void append(char s[], char n);

#endif
