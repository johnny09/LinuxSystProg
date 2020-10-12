/*
 * get the byte number before the spcified line
 */
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	FILE *fp;
	int readLines = 0;
	int readBytes = 0;
	char readChar;
	if(argc != 3)
	{
		fprintf(stderr,"Usage...\n");	
		exit(1);
	}

	//open the file with readonly mode
	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		perror("fpoen()");
		exit(1);
	}

	while((readChar = getc(fp)) != EOF )
	{
		readChar = getc(fp);
		
		//touch the desired line
                if(readLines == (atoi(argv[2])-1))
                {
			fprintf(stdout,"the total read bytes before line %s is %d\n",argv[2],readBytes);
			fclose(fp);
			exit(0);
                }

		//read the new line
		if(readChar == '\n')
			readLines++;
		
		readBytes++;
	}

	fclose(fp);
	exit(0);

}

















