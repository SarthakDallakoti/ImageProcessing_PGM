#include "pgmWrite.h"
#include <stdlib.h>
#include <stdio.h>

int writeToFile(FILE *outputFile, FileInfo *fileValues, char* outputFileName)
{
  long nImageBytes = fileValues->width * fileValues->height * sizeof(unsigned char);
  //Check if file is empty
  int isBinary=0;
  size_t nBytesWritten;
  // Write the ASCII header based on magicNumber
  if (*(fileValues->magic_Number) == MAGIC_NUMBER_ASCII_PGM)
  {
    nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", fileValues->width, fileValues->height, fileValues->maxGray);
    isBinary=1;
  }
  else if (*(fileValues->magic_Number) == MAGIC_NUMBER_RAW_PGM)
  {
    nBytesWritten = fprintf(outputFile, "P5\n%d %d\n%d", fileValues->width, fileValues->height, fileValues->maxGray);
    isBinary=2;
  }
  // Check if the file is in binary and was able to write the header, and write to it the imageData if yes
  if (isBinary==2 && nBytesWritten >= 0)
  {
    fwrite(fileValues->imageData, sizeof(unsigned char), fileValues->width * fileValues->height, outputFile);
    exit(EXIT_NO_ERRORS);
  }
  else if (isBinary==2)
  {
    // File in binary but wasn't able to write header
    exit(EXIT_BAD_DATA);
  }
  // Check if was able to write the header
  if (nBytesWritten < 0)
  {
    // Terminate thr program if not with error code
    free(fileValues->imageData);
    exit(EXIT_BAD_DIMENTION);
  }
  // Write in ASCII to outputFile
  for(int i =0; i< fileValues -> height; i++){
    for (int j=0; j < fileValues -> width; j++){
      nBytesWritten = fprintf(outputFile, "%d%c", fileValues -> imageData[i][j], ' ');
      // Check if it was possible to write into file
      if (nBytesWritten < 0)
      {
        // If not, terminate with error code
        //Free the Image Data
        free(fileValues->imageData);
        printf("ERROR: Output Failed (%s)",outputFileName);
        exit (EXIT_OUTPUT_FAILED);
      }
    }
  }
    // Successfully written all to output file
    return EXIT_NO_ERRORS;
}

int writeASCIIDataInBinary(FILE *outputFile, FileInfo *fileValues, char* outputFileName){
  // write magic number, size & gray value
  size_t nBytesWritten = fprintf(outputFile, "P5\n%d %d\n%d\n", fileValues->width, fileValues->height, fileValues->maxGray);

  // check that dimensions wrote correctly
  if (nBytesWritten < 0)
    {
      // dimensional write failed
      // free memory
      free(fileValues->imageData);

      // print an error message
      printf("ERROR: Output Failed (%s)", outputFileName);

      // return an error code
      return (EXIT_OUTPUT_FAILED);
    }
    for (int i =0; i < fileValues -> height; i++){
      for(int j=0; j < fileValues -> width; j++){
        //used to store the number of pixels written into the file
        nBytesWritten = fwrite(&fileValues->imageData[i][j],sizeof(unsigned char),1, outputFile);
      }
    }
    // at this point, we are done and can exit with a success code
  return EXIT_NO_ERRORS;
}

int writeASCIIPropertyONLY(FILE *outputFile, FileInfo *fileValues, char* outputFileName)
{
  long nImageBytes = fileValues->width * fileValues->height * sizeof(unsigned char);
  // Write to file the ASCII header only based on the magic number
  if (*(fileValues->magic_Number) == MAGIC_NUMBER_ASCII_PGM){
    fprintf(outputFile, "P2\n%d %d\n%d\n", fileValues->width, fileValues->height, fileValues->maxGray);
  }
  else if (*(fileValues->magic_Number) == MAGIC_NUMBER_RAW_PGM){
    fprintf(outputFile, "P5\n%d %d\n%d\n", fileValues->width, fileValues->height, fileValues->maxGray);
  }
  return EXIT_NO_ERRORS;
}
