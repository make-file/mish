#include "prototype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    set alias in file
*/
void alias_set(char *name, char *command)
{
    FILE *fp;
    char *inp ;

    // filename for storing aliases
    char *filename = strcat(getenv("HOME"), "/.mish_alias");

    // open file for storing aliases
    fp = fopen(filename, "a+");

    // check if file opens with success
    if(fp != NULL)
    {
        sprintf(inp, "%s \t %s ", name, command);
        fputs(inp, fp);
    }

}


/*
    check if is alias is created
*/
char *alias_check(char *input){
    
    FILE *fp;
    char c;
    char *name;
    char *command;

    // filename for storing aliases
    char *filename = strcat(getenv("HOME"), "/.mish_alias");

    // open the file storig aliases
    fp = fopen(filename, "r");

    // get file size
    fseek(fp, 0, SEEK_END);
    long int textSize = ftell(fp);

    // close the file and reopen it to start from begining
    fclose(fp);
    fp = fopen(filename, "r");

    // file text will be stored in this string.
    // so allocate enough bytes for it.
    char* text = malloc(textSize*sizeof(char));

    int i=0;
    if(fp == NULL) {
        perror("Error in opening file");
    } do {
        c = fgetc(fp);
        if( feof(fp) ) {
            break ;
        }
        text[i] = c;
        i++;
    } while(1);

    i = 0;
    // seprate it by \n
    char* line = strtok(text, "\n");
    
    while (line != NULL)
    {
        // seprate by tabs
        char *token = strtok(line, "\t");
        while(token != NULL){
            if(i == 0){
                // assigning name
                name = token;
            }else if(i == 1){
                // command ti run
                command = token;
            }
            else{
                break;
            }
            token = strtok(NULL, "\t");
        }
        // check if it is alias
        if(! strcmp(input, name))
            return command;
        else {
            continue;
        } 
    }
    // if it is not alias
    return input;

}