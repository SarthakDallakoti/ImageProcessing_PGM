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
      //Condition if only 1 argument is provided
		printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm");
		return EXIT_NO_ERRORS;
	}
    if (argc == 2 || argc == 3)
    {
      //If there is bad argument count
        printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
    }
    //To convert reduction Factor into integer
    char scaling_factor [40];
    strcpy(scaling_factor,argv[2]);
    int z = atoi (scaling_factor);
    if (z < 0)
    {
      //Checking if it is a negative sacling factor
        printf("ERROR: Miscellaneous (Negative Scaling Factor)");
        return EXIT_MISCELLANEOUS;
    }
    for (int i =0; scaling_factor[i]!= '\0'; i++)
    {
      //Checking if it is a non numeric value
        if (isdigit(scaling_factor[i]) == 0){
            printf("ERROR: Miscellaneous (Non-Numeric Value)");
            return EXIT_MISCELLANEOUS;
        }
    }
    //Checking for bad argument count
	if (argc != 4)
    {
		printf("ERROR: Bad Argument Count");
		return EXIT_WRONG_ARG_COUNT;
	}

    // Check if correct number of arguments were provided
	// Open the input file
	FileInfo *fileValues1 = initialisationOfReadFileStruct();
  FileInfo *fileValues2 = initialisationOfReadFileStruct();

	FILE *inputFile = fopen(argv[1], "r");
	// Read to file and check whether it has read successfully
	int coderead = readFile(argv[1],fileValues1, inputFile);
	if (coderead!=0)
		{
            if (argc == 1){
			printf("./pgmReduce inputImage.pgm reduction_factor outputImage.pgm");
			return EXIT_NO_ERRORS;
		}
			// If not, terminate with error code
			return coderead;
		}
		long nImageBytes = fileValues1->width * fileValues1->height * sizeof(unsigned char);
		// Read image data based on the magicNumber
		if (*(fileValues1->magic_Number) == MAGIC_NUMBER_ASCII_PGM)
		{
      //If ASCII value then read ASCII imageData
		    codemagic = readImageData(fileValues1,inputFile, argv[1]);
		}
		else if (*(fileValues1->magic_Number) == MAGIC_NUMBER_RAW_PGM)
		{
      //If Binary Magic Number
			codemagic = readImageDataBinary(fileValues1, inputFile, argv[1]);
		}
		// Check if successfully written imageData
		if (codemagic !=0)
		{
			return codemagic;
		}
    //CAll the reduce function to reduce the file size
    Reduce(fileValues1,fileValues2,z);
    // Open output file
    FILE *outputFile = fopen(argv[3], "w");
		// Write to file the content of input file
		if (outputFile == NULL)
		{
			// Terminate with error code
			free(fileValues1->imageData);
			printf("ERROR: Output Failed (%s)",argv[3]);
			exit (9);
    }
    //For ASCII image
    if (*(fileValues1->magic_Number) == MAGIC_NUMBER_ASCII_PGM)
		{
      //Magic number P2
		    fprintf(outputFile, "P2\n%d %d\n%d\n", fileValues2->width, fileValues2->height, fileValues2->maxGray);
		}
    //For Binary Image
		else if (*(fileValues1->magic_Number) == MAGIC_NUMBER_RAW_PGM)
		{
      //Magic number P5
			fprintf(outputFile, "P5\n%d %d\n%d\n", fileValues2->width, fileValues2->height, fileValues2->maxGray);
		}
		writeToFile(outputFile, fileValues2, argv[3]);
		// Check if it has written successfully
    //fclose(inputFile);
		fclose(outputFile);
		printf("REDUCED");
    //Return no errors
		return EXIT_NO_ERRORS;
}
