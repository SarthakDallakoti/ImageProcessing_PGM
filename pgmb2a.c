#include <stdio.h>
#include <stdlib.h>
#include "pgmRead.h"
#include "pgmWrite.h"

int main(int argc, char **argv)
{
   // Check if argument number error occured
  if (argc == 1){
			printf("Usage: ./pgmb2a inputImage.pgm outputImage.pgm");
			return EXIT_NO_ERRORS;
		}
		if (argc != 3){
			printf("ERROR: Bad Argument Count");
			return EXIT_WRONG_ARG_COUNT;
		}
  // initialises fileInfo struct with default values
  FileInfo *fileValues = initialisationOfReadFileStruct();
  // Read a input file
	FILE *inputFile = fopen(argv[1], "rb");
	int code = readFile(argv[1],fileValues, inputFile);
  // Check if successfully read
	if (code!=0){
		return code;}
  // Check if magicNumber indicates the input file is a ASCII file
  // and switch the magicNumber to binary
  unsigned short *magic_Number = (unsigned short *) fileValues->magic_Number;
  if(*magic_Number != MAGIC_NUMBER_RAW_PGM){
    printf("ERROR: Bad Magic Number (%s)\n",argv[1]);
    exit(3);
  }
  else
  {
    *magic_Number = MAGIC_NUMBER_ASCII_PGM;
  }
  //Read the image data
  code = readImageDataBinary(fileValues, inputFile, argv[1]);
  // Check if written successfully to file
	if (code !=0){
		return code;}
  //Check the length of the comment line
  readCommentAndCheck(inputFile, MAX_COMMENT_LINE_LENGTH, fileValues, argv[1]);
  // Open the output file
  FILE *outputFile = fopen(argv[2], "w");
  if (outputFile == NULL)
	{
		// Terminate with error code
		free(fileValues->imageData);
		printf("ERROR: Output Failed (%s)",argv[2]);
		exit (9);
    }
  // Write the ASCII header in ASCII to output file
  code = writeToFile(outputFile, fileValues, argv[2]);
  // Check if successfully written
  if (code!=0){
    return code;}
    printf("CONVERTED");
  fclose(outputFile);
  return 0;
}
