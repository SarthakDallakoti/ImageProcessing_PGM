#include <stdio.h>
#include <stdlib.h>
#include "pgmRead.h"
#include "pgmWrite.h"

int main(int argc, char **argv)
{
	// Check if provided parameters are correct
	if (argc == 1){
		printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm");
		return EXIT_NO_ERRORS;
		}
	if (argc != 3)
	{
		printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
	}
	// Check if correct number of arguments were provided
	// Open the input file
	FileInfo *fileValues = initialisationOfReadFileStruct();

	FILE *inputFile = fopen(argv[1], "r");
	// Read to file and check whether it has read successfully
	readFile(argv[1],fileValues, inputFile);

	unsigned short *magic_Number = (unsigned short *) fileValues->magic_Number;
	// Read image data based on the magicNumber
	if (*magic_Number == MAGIC_NUMBER_ASCII_PGM)
	{
		readImageData(fileValues, inputFile, argv[1]);
	}
	else if (*magic_Number == MAGIC_NUMBER_RAW_PGM)
	{
		readImageDataBinary(fileValues,inputFile, argv[1]);
	}
		// Check if successfully written imageData
	fclose(inputFile);
		// Open output file
	FILE *outputFile = fopen(argv[2], "w");
	if (outputFile == NULL)
	{
		// Terminate with error code
		free(fileValues->imageData);
		printf("ERROR: Output Failed (%s)",argv[2]);
		exit (9);
    }
	if (*magic_Number == MAGIC_NUMBER_ASCII_PGM)
	{
		// Write to file the content of input file
		writeToFile(outputFile, fileValues, argv[2]);
	}
	else if (*magic_Number == MAGIC_NUMBER_RAW_PGM)
	{
		writeASCIIDataInBinary(outputFile, fileValues, argv[2]);
	}
	fclose(outputFile);
	
	printf("ECHOED");
	
	return EXIT_NO_ERRORS;
}
