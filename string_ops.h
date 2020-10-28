#ifndef STRING_OPS
#define STRING_OPS

#include <stdlib.h>
#include <stdio.h>

/**
 * Will fill a string with \0 null terminators
 * @param char *string string to modify
 */ 
void str_zero(char *string){
    char *cpy = string;
    while(*cpy != '\0'){
        *cpy = '\0';
        cpy++;
    }
}

/**
 * Copies a string from source to destionation
 * @param const char *source The source string
 * @param char *dest The destination string
 */ 
void str_cpy(const char *source, char* dest){
    char *cpy = (char *)source;
    char *cpy_dest = dest;
    while(*cpy != '\0'){
        *cpy_dest = *cpy;
        cpy++;
        cpy_dest++;
    }
    *cpy_dest = '\0';
}

/**
 * Determines the length of the string leading up to the '\0' terminator
 * If no terminator is found behaviour is undefined but will likely lead to SEGV
 * @param const char *string The string to check
 * @return int length of string NOT including null terminator
 */ 
int str_len(const char *string){
    int len = 0;
    char *cpy = (char *)string;
    while(*cpy != '\0'){
        len++;
        cpy++;
    }
    return len;
}

/**
 * Returns the distance to the specified character from the defined initial position
 * @param const char *string The string to observe
 * @param char to The character to find
 * @param int start The inital position
 * @returns int The length to the occurance of the specified char
 */ 
int str_len_to(const char *string, char to, int start){
    int len = str_len(string);
    int dist = 0;
    char *cpy = (char *)string;
    // move to pos
    while(dist < start){
        cpy++;
        dist++;
    }
    dist = 0;
    // start search
    while(*cpy != to && dist < len){
        dist++;
        cpy++;
    }
    return dist;
}

/**
 * Counts the occurances of the specified token
 * @param const char *string The string to check
 * @param char token The token to count
 */ 
int count_tokens(const char *string, char token){
    int i = 0;
    int len = str_len(string);
    int count = 0;
    char *cpy = (char *)string;
    while(*cpy != '\0' && i <= len){
        if(*cpy == token) count++;
        i++;
        cpy++;
    }
    return count;
}
/**
 *  Returns a pointer to a heap-held array of split values
 * @param const char *string the strinf to split
 * @param char delimiter the delimiter to split the string by 
 */
char **str_split(const char *string, char delimiter, int *elements){
    // get the size of the array we'll need
    int sections = count_tokens(string, delimiter) + 1;
    *elements = sections;
    // allocate space for our string pointers
    char **splits = malloc(sections * sizeof(char *));
    // copy our initial position pointer for return
    char *cpy = (char *)string;

    int t_idx = 0, s_idx = 0;
    char temp[512] = {'\0'}; // assume we wont have a section longer than 512
    while(*cpy != '\0'){
        if(*cpy == delimiter){
            t_idx++;
            temp[t_idx] = '\0';
            splits[s_idx] = malloc(sizeof(char) * str_len(temp) + 1);
            str_cpy(temp, splits[s_idx]);
            str_zero(temp);
            t_idx = 0;
            s_idx++;
            cpy++;
        }else{
            temp[t_idx] = *cpy;
            t_idx++;
            cpy++;
        }
    }
    // copy in last section
    t_idx++;
    temp[t_idx] = '\0';
    splits[s_idx] = malloc(sizeof(char) * str_len(temp) + 1);
    str_cpy(temp, splits[s_idx]);
    return splits;
}

/**
 * Frees up a double pointered, heap allocated object
 * @param char **split The pointer to an array of strings
 * @param int elements The number of elements to iterate over
 */ 
void free_split(char **split, int elements){
    int i;
    for(i=0; i < elements; i++){
        free(split[i]);
    }
    free(split);
}
#endif