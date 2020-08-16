/*
 * minimalistic shell
 * lisenced under bsd clause 2
 *
 *
 * */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 64

char **split(char *line) {
  int buff = BUFFER;
  char **tokens = malloc(buff * sizeof(char*));
  char *token;
  if (tokens == NULL) {
    printf("mish: allocation error\n");
    exit(1);
  }
  int i = 0;
  token = strtok(line, " "); 
  while (token != NULL) { 
      tokens[i] = token;
      i++;
      token = strtok(NULL, " ");

  } 
  tokens[i] = NULL;
  return tokens;
}

void command(char **arguments){
  if(! strcmp(arguments[0], "cd")){
    printf("%s", arguments[0]);
    if(!arguments[1]){

      chdir("~");
    }else{
          printf("%s", arguments[1]);

      if(!chdir(arguments[1])){
      }
      else{
      	printf("error occured");
      }
    }
  }
}
void prompt() {
  char input[CHAR_MAX];
  char identify[4];
  char **arguments;
  char cwd[CHAR_MAX];
  if (!(getcwd(cwd, sizeof(cwd)) != NULL)) {
    perror("getcwd() error");
  }
  uid_t user = getuid();
  if (user == 0) {
    strcpy(identify, "#");
  } else {
    strcpy(identify, "$");
  }
  printf("[%s]%s ", cwd, identify);
  fgets(input, sizeof(input), stdin);
  arguments = split(input);
  command(arguments);
  free(arguments);
  prompt();
}

int main(int argc, char *argv[]) {
  printf("welcome to minimalistic shell ! \n");
  prompt();
}