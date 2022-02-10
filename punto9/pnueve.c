#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* getString(){
 char message[100] = "Hello World!";
 return message;
}
int main(int argc, char* argv[]){
 printf("String: %s\n", getString());
}