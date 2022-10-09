# ImageProcessing_PGM
This repository contains set of programs that manipulates PGM file in a number of ways. 

FYI: This project was submitted to University of Leeds

This file contains information regarding how to run the program.

1. To make executables: Open terminal in the directory where all the .c files are and type make.
2. After that you can type ./testscript.sh to see all the test and their output.
   If you would like to test a particular test then the you need to use following command:

   ./pgmEcho inputImage.pgm outputImage.pgm

   ./pgmComp inputImage.pgm inputImage.pgm

   ./pgma2b inputImage.pgm outputImage.pgm

   ./pgmb2a inputImage.pgm outputImage.pgm

   ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm

   ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm

   ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+

3. You can file useful pgm Images in following directory: assignment_1/pgmImages

4. You can also delete the .o file by using make clean command.
