#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

unsigned long get_file_size(const char *path)
{
        unsigned long filesize = -1;
        struct stat statbuff;
        if(stat(path, &statbuff) < 0){
                return filesize;
        }else{
                filesize = statbuff.st_size;
        }
        return filesize;
}


int main(int argc,char** argv)
{
	
	FILE *fp1;
	FILE *fp2;
	int fd;

	int readLines = 0;
        int bytesBeforeDelLine = 0;
	int bytesBeforeDelNextLine = 0;
        char readChar;	

	//int read_off;
	//int write_off;
	
	char *readBuf;
	size_t sizeToRead = 0;
	size_t numReaded = 0;
	size_t numWritten = 0;
	int loopTime = 0;
	unsigned long fileSize = 0;

	off_t truncSize = 0;
	if(argc != 3)
	{
		fprintf(stderr,"Usage...");
		exit(0);
	}
	
	//open for read
	fp1 = fopen(argv[1],"r");
	if(fp1 == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	
	//open for write
	fp2 = fopen(argv[1],"r+");
	if(fp2 == NULL)
        {
                perror("fopen()");
		fclose(fp1);
                exit(1);
        }
	
	readLines = 0;
	//get the byte number before the input line number(argv[2])
	while((readChar = getc(fp1)) != EOF )
        {
                //touch the desired line
                if(readLines == (atoi(argv[2])-1))
                {
                        fprintf(stdout,"the total read bytes before line %d is %d\n",atoi(argv[2]),bytesBeforeDelLine);
			break;
                }

                //read the new line
                if(readChar == '\n')
                        readLines++;

                bytesBeforeDelLine++;
        }
	
	fseek(fp1,0,SEEK_SET);
	readLines = 0;
	//get the byte number before the line next to input line number(argv[2])
        while((readChar = getc(fp1)) != EOF )
        {
                //touch the desired line
                if(readLines == atoi(argv[2]))
                {
                        fprintf(stdout,"the total read bytes before line %d is %d\n",atoi(argv[2])+1,bytesBeforeDelNextLine);
                        break;
                }

                //read the new line
                if(readChar == '\n')
                        readLines++;

                bytesBeforeDelNextLine++;
        }
	fseek(fp1,0,SEEK_SET);

	//set the start read position
	if(fseek(fp1,bytesBeforeDelNextLine,SEEK_SET) < 0)
	{
		perror("fseek()");
		fclose(fp1);
		fclose(fp2);
		exit(1);
	}
	
	//set the start write position
	if(fseek(fp2,bytesBeforeDelLine,SEEK_SET) < 0)
	{
		perror("fseek()");
		fclose(fp1);
                fclose(fp2);
		exit(1);
	}
	
	fileSize = get_file_size(argv[1]);
	fprintf(stdout,"file size is %ld\n",fileSize);	
	sizeToRead = get_file_size(argv[1]) - bytesBeforeDelNextLine;
	fprintf(stdout,"sizeToRead is %ld\n",sizeToRead);

	//allocate memory for readBuf
	if((readBuf = malloc(sizeToRead+1)) ==  NULL)
	{
		perror("malloc()");
		fclose(fp1);
		fclose(fp2);
		exit(1);
	}

	//read from line argv[1]+1 to write 
	//to the line startfrom line argv[1]
	while((numReaded = fread(readBuf, sizeToRead, 1, fp1)) > 0)
	{
		fprintf(stdout,"sizeReaded: %ld\n",numReaded*sizeToRead);
		printf("readBuf:\n%s",readBuf);
		if((numWritten = fwrite(readBuf, numReaded*sizeToRead, 1, fp2)) < 0)
		{
			perror("fwrite()");
			break;
		}
		fprintf(stdout,"sizeWritten: %ld\n",numWritten*numReaded*sizeToRead);
		loopTime++;
		printf("while loop %d times\n",loopTime);
	}

	free(readBuf);
	
	fd = fileno(fp2);
	
	truncSize = bytesBeforeDelLine + (fileSize - bytesBeforeDelNextLine);
	//ftruncate the file
	if((ftruncate(fd, truncSize)) < 0)
	{
		perror("ftruncate()");
		fclose(fp1);
		fclose(fp2);
		exit(0);
	}

	printf("the file size after truncate is: %ld\n",bytesBeforeDelLine + (fileSize - bytesBeforeDelNextLine));
	fclose(fp1);
        fclose(fp2);
	exit(0);
}




















