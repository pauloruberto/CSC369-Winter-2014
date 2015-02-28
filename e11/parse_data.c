#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {
  	FILE *fp;
  	char buff[255];
  	char addresses

  	fp = fopen("tr-heaploop.ref", "r");
  	if (fp == NULL) {
		perror("file reading");
		exit(1);
  	}

  	char *token;

  	while(fgets(buff, 255, fp) != NULL) {
  		token = strtok(buff, ","); //the memory address


  		printf("%s\n", buff);
  	}



	return 0;
}