//Library for I/O and Memory Routine
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Header File Used for this Program
#include "pgmRead.h"

FileInfo *initialisationOfReadFileStruct (){
  // Creates and initialises the fileInfo structure to default values
  FileInfo *output = (FileInfo*) malloc (sizeof(FileInfo));
  output->commentLine = NULL;
  output->magic_number[0] = '0';
  output->magic_number[1] = '0';
  output->magic_Number = (unsigned short *) output->magic_number;
  output->width=0;
  output->height=0;
  output->maxGray=255;
  output->imageData=NULL;
  // Return the pointer to this structure
  return output;
}

int readCommentAndCheck(FILE *file, int maxCommentLen, FileInfo *fileValues,char* filename)
{
  //Scans the whitespace
  fscanf(file," ");
  char nextChar = fgetc(file);
  //Initialize comment length
  int commentlength = 0;
  // Check if this is a comment line
  if (nextChar == '#')
  {
    fileValues->commentLine = (char *) malloc(maxCommentLen);
    // Capture the comment
    char *commentString = fgets(fileValues->commentLine, maxCommentLen, file);
    // Check if a comment was successfully read
    if (commentString == NULL)
    {
      //Free the comment line and exit the file
      free(fileValues->commentLine);
      fclose(file);
      exit (2);
    }
    //Length of the comment line
    commentlength = (int)strlen(commentString);
    //If comment line is greater than 128
    if (commentlength > 128){
      //Error message
      printf("ERROR: Bad Comment Line (%s)",filename);
      //Close the file and return the error code
      fclose(file);
      exit(EXIT_NO_ERRORS);
    }
    // correct comment
    free(fileValues->commentLine);
    return 1;
  }
  // Not a comment line
  else
  {
    ungetc(nextChar, file);
    //No error then return 0
    return EXIT_NO_ERRORS;
  }
}

void getMagicNumber (FileInfo *fileValues, FILE *file)
{
  // Modify the fileValues struct magic_number based on data in file
  fileValues->magic_number[0] = getc(file);
  fileValues->magic_number[1] = getc(file);
}

int checkIfInputFileEmpty(FILE *inputFile, char* filename){
  //Check if input file is null
  if (inputFile == NULL)
  {
    //Exit with error message
    printf("ERROR: Bad File Name (%s)",filename);
    exit (EXIT_BAD_INPUT_FILE);
  }
  //No error then exit 0
  return EXIT_NO_ERRORS;
}

int checkIfValidMagicNumber(char* filename, FileInfo *fileValues,FILE *inputFile)
{
  // Check if the magic number is either P2 or P5
  if (*(fileValues->magic_Number) != MAGIC_NUMBER_ASCII_PGM && *(fileValues->magic_Number) != MAGIC_NUMBER_RAW_PGM)
  {
    //Exit with error message
    printf("ERROR: Bad Magic Number (%s)",filename);
    //Close the input file
    fclose(inputFile);
    exit(EXIT_BAD_MAGIC_NUMBER);
  }
  //No error then exit 0
  return EXIT_NO_ERRORS;
}

int checkWidthHeightMaxGrayAreValid(char *filename, FILE *inputFile, FileInfo *fileValues){
  // Check if the values for width, height, maxGray are valid
  int scanCount = fscanf(inputFile, " %u %u %u", &(fileValues->width), &(fileValues->height), &(fileValues->maxGray));
  //Condition to check the height and width of the image
  if 	(
    (scanCount != 3)	|| (fileValues->width < MIN_IMAGE_DIMENSION) 	|| (fileValues->width > MAX_IMAGE_DIMENSION) 	|| (fileValues->height < MIN_IMAGE_DIMENSION) 	||(fileValues->height > MAX_IMAGE_DIMENSION))
    {
      //Exit with the error message
      printf("ERROR: Bad Dimensions (%s)",filename);
      exit(EXIT_BAD_DIMENTION);
    }
    //For Bad Gray Value
  if ((fileValues->maxGray != 255))
  {
    //If gray value is not equal to 255
    //exit with the error message
    printf("ERROR: Bad Max Gray Value (%s)",filename);
    exit(EXIT_BAD_MAX_GRAY_VALUE);
  }
  //No error then return 0
  return EXIT_NO_ERRORS;
}

int readFile(char* filename, FileInfo *fileValues, FILE *inputFile){
  // Check if file supplied is empty
  checkIfInputFileEmpty(inputFile, filename);

  // Fetches the magic number from file
  getMagicNumber(fileValues, inputFile);

  // Check if magicNumber in file is valid
  checkIfValidMagicNumber(filename, fileValues,inputFile);

  // Check if comment line in file is valid
  readCommentAndCheck(inputFile, MAX_COMMENT_LINE_LENGTH, fileValues, filename);

  // Scan for whitespace to remove it
  fscanf(inputFile, " ");

  // Get width, height, maxGray from file
  // Check if the values from file are valid for pgm formatting
  checkWidthHeightMaxGrayAreValid(filename,inputFile,fileValues);
  //No error then return 0
  return EXIT_NO_ERRORS;
}

int readImageData(FileInfo *fileValues,FILE *inputFile, char* filename)
{
  //Variable to count image data
  int r = 0;
  //Counts the file dimensions
  long nImageBytes = fileValues->width * fileValues->height * sizeof(unsigned char);
  // Allocate memory on the heap for imageData
  fileValues->imageData = (unsigned char **) malloc(nImageBytes);
  // Check if malloc function worked
   if (fileValues->imageData == NULL)
  {
    //Exit program with error message
    printf("ERROR: Image Malloc Failed");
    //Free the image Data
    free(fileValues->imageData);
    //Close the file
    fclose(inputFile);
    exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
  }
  for (int i = 0; i < fileValues-> height ; i++){
		fileValues->imageData[i] = (unsigned char *) malloc(fileValues->width * sizeof(unsigned char));
		if (fileValues->imageData[i] == NULL)
		{
			// malloc failed
			// free up memory
			free(fileValues->imageData);
			/* close file pointer*/
			fclose(inputFile);
			/* print an error message */
			printf("ERROR: Image Malloc Failed\n");
			/* return error code */
			exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
		}
	}
  // For each value in file, read it, check it and write its pointer into imageData if valid
  for(int i =0; i< fileValues-> height; i++){
    for(int j =0; j < fileValues-> width; j++){
      int grayValue = -1;
      // Retrieve the value for grayValue from file
      int scanCount = fscanf(inputFile, " %u", &grayValue);
      // Check if values in file are valid
      if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255) || (grayValue>fileValues->maxGray))
      {
        printf("ERROR: Bad Data (%s)",filename);
        free(fileValues->imageData);
        fclose(inputFile);
        exit(EXIT_BAD_DATA);
      }
      // Assign a pointer to imageData, pointing to grayValue
      fileValues->imageData[i][j] = (unsigned char) grayValue;
      r = r + 1;
      }
    }
    //Variable to check the the value
    int checkval;
    //Check for extra white space
    int extradata = fscanf(inputFile,"%u",&checkval);
    //Check too little data
    if (r < nImageBytes){
      //Exit with the error message
      printf("ERROR: Bad Data (%s)",filename);
      //Free the imageData
      free(fileValues->imageData);
      //Close the input File
      fclose(inputFile);
      exit(EXIT_BAD_DATA);
    }
    //Check for too much data
    else if(extradata >0){
      //Exit with error message
      printf("ERROR: Bad Data (%s)",filename);
      //Free the imageData
      free(fileValues->imageData);
      //Close the input File
      fclose(inputFile);
      exit(EXIT_BAD_DATA);
    }
  //No error then return 0
  return EXIT_NO_ERRORS;
}

int readImageDataBinary(FileInfo *fileValues,FILE *inputFile, char* filename)
{
  //Variable to count image data
  int r = 0;
  // Allocate memory on the heap for imageData
  fileValues->imageData = (unsigned char **) malloc(fileValues -> height * sizeof(unsigned char **));
  //Reads the binary file
  fgetc(inputFile);
  // Check if malloc function worked
  if (fileValues->imageData == NULL)
  {
    //Exit with an error messgae
    printf("ERROR: Image Malloc Failed\n");
    //Free the image data
    free(fileValues->imageData);
    //Close the inputfile
    fclose(inputFile);
    exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
  }
  for(int i =0; i < fileValues -> height; i++){
    fileValues-> imageData[i] = (unsigned char *) malloc(fileValues -> width * sizeof(unsigned char));
    if (fileValues -> imageData[i] == NULL){
      //free the memory
      free(fileValues -> imageData);
      //close the inputfile
      fclose(inputFile);
      //print the error message
      printf("ERROR: Image Malloc Failed");
      //return error code
      exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
    }
  }
  for (int i =0; i< fileValues -> height; i++){
    for(int j =0; j< fileValues -> width; j++){
      //Stores the number of pixels read
      r = fread(&fileValues->imageData[i][j], sizeof(const char), 1, inputFile);
      if (r == 0){
        //Exits with the error message
        printf("ERROR: Bad Data (%s)",filename);
        //Free the imageData
        free(fileValues->imageData);
        //Close the inputfile
        fclose(inputFile);
        exit(EXIT_BAD_DATA);
      }
    }
  }
  //Variable to check the the value
  unsigned int checkval;
  //Check for extra white space
  int extradata = fscanf(inputFile,"%u",&checkval);
    //Check for too much data
  if(extradata >0){
    printf("ERROR: Bad Data (%s)",filename);
    free(fileValues->imageData);
    fclose(inputFile);
    exit(EXIT_BAD_DATA);
  }
  //No error then return 0
  return EXIT_NO_ERRORS;
}

int compare(FileInfo *fileValues1,FileInfo *fileValues2)
{
  if  (fileValues1->width != fileValues2->width || fileValues1->height != fileValues2->height || fileValues1->maxGray != fileValues2->maxGray){
			//conditions are not met and the files are distinct
			//print message
			printf("DIFFERENT");
			//return the code for successful comparison
			exit(0);
		}
		else{
			// the conditions are met and the files have identical structure
			//now to test if the pixel values are identical

			//create integer to count the number of identical pixels
			int identicalPixles = 0;

			//create integer to hold the product of dimensions
			long dimensions = fileValues1->width * fileValues1->height * sizeof(unsigned char);
			for(int i = 0; i < fileValues1 -> height ; i++){
				for(int j = 0; j < fileValues1 -> width ; j++){
					if (fileValues1->imageData[i][j] == fileValues2->imageData[i][j]){
						//the pixels are identical
						//add 1 to the variable
						identicalPixles++;
					}
				}
			}
    if (identicalPixles == dimensions){
      printf("IDENTICAL");
      exit(EXIT_NO_ERRORS);
    }
    else{
      printf("DIFFERENT");
      exit(EXIT_NO_ERRORS);
    }
  }
  return EXIT_NO_ERRORS;
}
int Reduce(FileInfo *fileValues1,FileInfo *fileValues2,  int reductionFactor)
{
  fileValues2-> width =(fileValues1->width/reductionFactor);
  fileValues2-> height =(fileValues1->height/reductionFactor);
  fileValues2-> maxGray =fileValues1->maxGray;

  //Allocatng memory
  fileValues2-> imageData =(unsigned char**) malloc(fileValues2->height * fileValues2->width * sizeof(unsigned char*));

  //If memory not allocated
  if(fileValues2 ->imageData == NULL){
    //Free memory
    free(fileValues1->imageData);
    //Print error message and exit the file
    printf("ERROR: Image Malloc Failed");
    exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
  }

  for(int vertical =0; vertical< fileValues1->height;vertical++){
    fileValues2->imageData[vertical] =(unsigned char *) malloc(fileValues2->width * sizeof(unsigned char));

    //IF memory not allocated properly
    if(fileValues2->imageData[vertical] == NULL){
      //Free memory
      free(fileValues1->imageData);
      free(fileValues2->imageData);

      //Print error mesage and exit wih return code
      printf("ERROR: Image Malloc Failed");
      exit(EXIT_BAD_IMAGE_MALLOC_FAILED);
    }
  }
  //Save the data in new Image
  int newVertical =0 ;
  int newHorizontal =0;
  for(int vertical =0; vertical< fileValues1->height;vertical++){
    //if wertical is correct
    if((vertical% reductionFactor) ==0){
      for(int horizontal =0; horizontal< fileValues1->width;horizontal++){
        //if pixels are correct
        if((horizontal%reductionFactor)==0){
          //Copy pixel into new structure
          fileValues2->imageData[newVertical][newHorizontal] = fileValues1 ->imageData[vertical][horizontal];

          //Move to next pixel
          newHorizontal++;
        }
      }
      //Move to new row
      newVertical++;
      newHorizontal =0;
    }
  }
  //free(fileValues1->imageData);
  return EXIT_NO_ERRORS;
}
