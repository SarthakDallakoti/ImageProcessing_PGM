#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pgmRead.h"
#include "pgmWrite.h"

int main(int argc, char **argv)
{
    int codemagic;
    if (argc == 1)
    {
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+");
		return EXIT_NO_ERRORS;
	}
	else if (argc < 6 && argc != 1)
  	{
		// Print error message and return appropriate error code
		printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
  	}
	  //Initilization of structures
	FileInfo *fileValues = initialisationOfReadFileStruct();
	int argument = 3;
	int c = 0;
	while(argument<(argc+1)){
		FILE *inputFile = fopen(argv[argument], "r");
		readFile(argv[1],fileValues, inputFile);
		c++;
		argument = 3*c +3;
	}

    // Check if correct number of arguments were provided
	// Open the input file

	FILE *inputFile = fopen(argv[1], "r");
	// Read to file and check whether it has read successfully
	int coderead = readFile(argv[1],fileValues, inputFile);
	if (coderead!=0)
		{
            if (argc == 1){
			printf("./pgmReduce inputImage.pgm reduction_factor outputImage.pgm");
			return EXIT_NO_ERRORS;
		}
			// If not, terminate with error code
			return coderead;
		}
		long nImageBytes = fileValues->width * fileValues->height * sizeof(unsigned char);
		// Read image data based on the magicNumber
		if (*(fileValues->magic_Number) == MAGIC_NUMBER_ASCII_PGM)
		{
		    readImageData(fileValues, inputFile, argv[1]);
		}
		else if (*(fileValues->magic_Number) == MAGIC_NUMBER_RAW_PGM)
		{
			readImageDataBinary(fileValues,inputFile, argv[1]);
		}
		// Check if successfully written imageData
		fclose(inputFile);
        // Open output file
        FILE *outputFile = fopen(argv[3], "w");
		// Write to file the content of input file
		writeToFile(outputFile, fileValues, argv[2]);
		if (outputFile == NULL)
		{
			// Terminate with error code
			free(fileValues->imageData);
			printf("ERROR: Output Failed (%s)",argv[2]);
			exit (9);
    	}
		// Check if it has written successfully
		fclose(outputFile);
		printf("TILED");
		return EXIT_NO_ERRORS;
}
