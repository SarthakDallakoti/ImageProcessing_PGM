#include <stdio.h>
#include <stdlib.h>
#include "pgmRead.h"

int main(int argc, char **argv){
  // Check if argument number error occured
  if (argc == 1){
			printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm");
			return EXIT_NO_ERRORS;
		}
		if (argc != 3){
			printf("ERROR: Bad Argument Count");
			return EXIT_WRONG_ARG_COUNT;
		}
  // Creates fileInfo struct and sets it to default values
  FileInfo *fileValues1 = initialisationOfReadFileStruct();
  // Open the input file
	FILE *inputFile1 = fopen(argv[1], "r");
	readFile(argv[1],fileValues1, inputFile1);
  // Calculates the size of the file

  // Read the file according to whether the file is in ASCII or binary format
  if (*(fileValues1->magic_Number) == MAGIC_NUMBER_ASCII_PGM){
    readImageData(fileValues1, inputFile1, argv[1]);
    }
  else if (*(fileValues1->magic_Number) == MAGIC_NUMBER_RAW_PGM){
    readImageDataBinary(fileValues1,inputFile1, argv[1]);
    }
  // Read file 2, same everything as above
  FileInfo *fileValues2 = initialisationOfReadFileStruct();
  FILE *inputFile2 = fopen(argv[2], "r");
  readFile(argv[2],fileValues2, inputFile2);
  if (*(fileValues2->magic_Number) == MAGIC_NUMBER_ASCII_PGM)
  {
  readImageData(fileValues2,inputFile2, argv[2]);
  }
  else if (*(fileValues2->magic_Number) == MAGIC_NUMBER_RAW_PGM)
  {
    readImageDataBinary(fileValues2,inputFile2, argv[2]);
    }
  // Check if the two files are logically equivalent
  // Display the result
  compare(fileValues1,fileValues2);
  fclose(inputFile1);
  fclose(inputFile2);
  return 0;
}
