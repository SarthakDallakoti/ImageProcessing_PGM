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
		printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm");
		return EXIT_NO_ERRORS;
	}
	if (argc != 4)
    {
		printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
	}

    // Check if correct number of arguments were provided
	// Open the input file
	FileInfo *fileValues = initialisationOfReadFileStruct();

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
		if (outputFile == NULL)
		{
			// Terminate with error code
			free(fileValues->imageData);
			printf("ERROR: Output Failed (%s)",argv[3]);
			exit (9);
    	}
		// Write to file the content of input file
		int codewrite = writeToFile(outputFile, fileValues, argv[3]);
		// Check if it has written successfully
		fclose(outputFile);
	    printf("TILED");
		return EXIT_NO_ERRORS;
}
