#!/bin/bash
make pgmEcho
make pgmComp
make pgma2b
make pgmb2a
make pgmReduce
make pgmTile
make pgmAssemble

#pgmEcho read and write: Test 1:
echo -e "\n"
echo "Test: FOR pgmEcho:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for Wrong Argument:"
./pgmEcho slice0a.pgm

echo -e "\n"
echo "Test2: Testing for Bad filename:"
./pgmEcho slicea.pgm out.pgm

echo -e "\n"
echo "Test3: Testing for Bad Magic Number:"
./pgmEcho slice0amagicnumber.pgm out.pgm

echo -e "\n"
echo "Test4: Testing for Bad Dimension(-1):"
./pgmEcho slice0abaddimension.pgm out.pgm

echo -e "\n"
echo "Test5: Testing for Bad Dimension(65536):"
./pgmEcho slice0abaddimensiona.pgm out.pgm

echo -e "\n"
echo "Test6: Testing for Bad Max Gray Value:"
./pgmEcho slice0abadgray.pgm out.pgm

echo -e "\n"
echo "Test7: Testing For Large Comment:"
./pgmEcho slice0acomment.pgm out.pgm

echo -e "\n"
echo "Test8: Testing For Too Much Data:"
./pgmEcho muchdata.pgm out.pgm

echo -e "\n"
echo "Test9: Testing For Too Little Data:"
./pgmEcho littledata.pgm out.pgm

echo -e "\n"
echo "Test10: Testing For Failed in Malloc:"
./pgmEcho mallocfailed.pgm out.pgm

echo -e "\n"
echo "Test11: Testing no Paramaters:"
./pgmEcho

echo -e "\n"
echo "Test12: Testing for Non-Writeable Files:"
./pgmEcho slice0a.pgm slice0aoutput.pgm

echo -e "\n"
echo "Test13: Testing For Identical ASCII File:"
./pgmEcho slice0a.pgm out.pgm
rm out.pgm

echo -e "\n"
echo "Test14: Testing For Identical Binary File:"
./pgmEcho binary.pgm bout.pgm
rm bout.pgm

echo -e "\n"
echo "**********************************"
echo -e "\n"


echo -e "\n"
echo "Test: FOR pgmComp:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for Wrong Argument:"
./pgmComp slice0a.pgm

echo -e "\n"
echo "Test2: Testing for Bad filename:"
./pgmComp slicea.pgm out.pgm

echo -e "\n"
echo "Test3: Testing for Bad Magic Number:"
./pgmComp slice0amagicnumber.pgm out.pgm

echo -e "\n"
echo "Test4: Testing for Bad Dimension(-1):"
./pgmComp slice0abaddimension.pgm out.pgm

echo -e "\n"
echo "Test5: Testing for Bad Dimension(65536):"
./pgmComp slice0abaddimensiona.pgm out.pgm

echo -e "\n"
echo "Test6: Testing for Bad Max Gray Value:"
./pgmComp slice0abadgray.pgm out.pgm

echo -e "\n"
echo "Test7: Testing For Large Comment:"
./pgmComp slice0acomment.pgm out.pgm

echo -e "\n"
echo "Test8: Testing For Too Much Data:"
./pgmComp muchdata.pgm out.pgm

echo -e "\n"
echo "Test9: Testing For Too Little Data:"
./pgmComp littledata.pgm out.pgm

echo -e "\n"
echo "Test10: Testing For Failed in Malloc:"
./pgmComp mallocfailed.pgm out.pgm

echo -e "\n"
echo "Test11: Testing no Paramaters:"
./pgmComp slice0a.pgm slice0aoutput.pgm

echo -e "\n"
echo "Test12: Testing For Identical ASCII File:"
./pgmComp slice0a.pgm out.pgm

echo -e "\n"
echo "Test13: Testing For Identical Binary File:"
./pgmComp binary.pgm bout.pgm

echo -e "\n"
echo "Test14: Testing For Different ASCII File:"
./pgmComp binary.pgm different.pgm

echo -e "\n"
echo "Test15: Testing For Identical ASCII-Binary File:"
./pgmComp slice0a.pgm binary.pgm

echo -e "\n"
echo "**********************************"
echo -e "\n"

echo -e "\n"
echo "Test: FOR pgma2b:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for Wrong Argument:"
./pgma2b slice0a.pgm

echo -e "\n"
echo "Test2: Testing for Bad filename:"
./pgma2b slicea.pgm out.pgm

echo -e "\n"
echo "Test3: Testing for Bad Magic Number:"
./pgma2b slice0amagicnumber.pgm out.pgm

echo -e "\n"
echo "Test4: Testing for Bad Dimension(-1):"
./pgma2b slice0abaddimension.pgm out.pgm

echo -e "\n"
echo "Test5: Testing for Bad Dimension(65536):"
./pgma2b slice0abaddimensiona.pgm out.pgm

echo -e "\n"
echo "Test6: Testing for Bad Max Gray Value:"
./pgma2b slice0abadgray.pgm out.pgm

echo -e "\n"
echo "Test7: Testing For Large Comment:"
./pgma2b slice0acomment.pgm out.pgm

echo -e "\n"
echo "Test8: Testing For Too Much Data:"
./pgma2b muchdata.pgm out.pgm

echo -e "\n"
echo "Test9: Testing For Too Little Data:"
./pgma2b littledata.pgm out.pgm

echo -e "\n"
echo "Test10: Testing For Failed in Malloc:"
./pgma2b mallocfailed.pgm out.pgm

echo -e "\n"
echo "Test11: Testing no Paramaters:"
./pgma2b

echo -e "\n"
echo "Test13: Testing for Non-Writeable Files:"
./pgmEcho slice0a.pgm slice0aoutput.pgm

echo -e "\n"
echo "Test14: Testing With Binary File:"
./pgma2b binary.pgm out.pgm

echo -e "\n"
echo "Test15: Testing If it converts ASCII to Binary:"
./pgma2b slice0a.pgm slicebinary.pgm
rm slicebinary.pgm

echo -e "\n"
echo "**********************************"
echo -e "\n"

echo -e "\n"
echo "Test: FOR pgmb2a:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for Wrong Argument:"
./pgmb2a slice0a.pgm

echo -e "\n"
echo "Test2: Testing for Bad filename:"
./pgmb2a slicea.pgm out.pgm

echo -e "\n"
echo "Test3: Testing for Bad Magic Number:"
./pgmb2a slice0amagicnumber.pgm out.pgm

echo -e "\n"
echo "Test4: Testing for Bad Dimension(-1):"
./pgmb2a slice0abaddimension.pgm out.pgm

echo -e "\n"
echo "Test5: Testing for Bad Dimension(65536):"
./pgmb2a slice0abaddimensiona.pgm out.pgm

echo -e "\n"
echo "Test6: Testing for Bad Max Gray Value:"
./pgmb2a slice0abadgray.pgm out.pgm

echo -e "\n"
echo "Test7: Testing For Large Comment:"
./pgmb2a slice0acomment.pgm out.pgm

echo -e "\n"
echo "Test8: Testing For Too Much Data:"
./pgmb2a muchdata.pgm out.pgm

echo -e "\n"
echo "Test9: Testing For Too Little Data:"
./pgmb2a littledata.pgm out.pgm

echo -e "\n"
echo "Test10: Testing For Failed in Malloc:"
./pgmb2a mallocfailed.pgm out.pgm

echo -e "\n"
echo "Test11: Testing no Paramaters:"
./pgmb2a

echo -e "\n"
echo "Test12: Testing for Non-Writeable Files:"
./pgmEcho binary.pgm slice0aoutput.pgm

echo -e "\n"
echo "Test12: Testing With ASCII File:"
./pgmb2a slice0a.pgm out.pgm

echo -e "\n"
echo "Test13: Testing If it converts Binary to ASCII:"
./pgmb2a binary.pgm ascii.pgm
rm ascii.pgm

echo -e "\n"
echo "**********************************"
echo -e "\n"

echo -e "\n"
echo "Test: FOR pgmReduce:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for 1 Wrong Argument:"
./pgmReduce slice0a.pgm

echo -e "\n"
echo "Test2: Testing for 2 Wrong Argument:"
./pgmReduce slice0a.pgm 3

echo -e "\n"
echo "Test3: Testing for non-numeric Scaling Factor:"
./pgmReduce slice0a.pgm abc out.pgm

echo -e "\n"
echo "Test4: Testing for Negative Scaling Factor:"
./pgmReduce slice0a.pgm -1 out.pgm

echo -e "\n"
echo "Test5: Testing for Bad filename:"
./pgmReduce slicea.pgm 3 out.pgm

echo -e "\n"
echo "Test6: Testing for Bad Magic Number:"
./pgmReduce slice0amagicnumber.pgm 3 out.pgm

echo -e "\n"
echo "Test7: Testing for Bad Dimension(-1):"
./pgmReduce slice0abaddimension.pgm 3 out.pgm

echo -e "\n"
echo "Test8: Testing for Bad Dimension(65536):"
./pgmReduce slice0abaddimensiona.pgm 3 out.pgm

echo -e "\n"
echo "Test9: Testing for Bad Max Gray Value:"
./pgmReduce slice0abadgray.pgm 3 out.pgm

echo -e "\n"
echo "Test10: Testing For Large Comment:"
./pgmReduce slice0acomment.pgm 3 out.pgm

echo -e "\n"
echo "Test11: Testing For Too Much Data:"
./pgmReduce muchdata.pgm 3 out.pgm

echo -e "\n"
echo "Test12: Testing For Too Little Data:"
./pgmReduce littledata.pgm 3 out.pgm

echo -e "\n"
echo "Test13: Testing For Failed in Malloc:"
./pgmReduce mallocfailed.pgm 3 out.pgm

echo -e "\n"
echo "Test14: Testing no Paramaters:"
./pgmReduce

echo -e "\n"
echo "Test15: Testing for Non-Writeable Files:"
./pgmReduce slice0a.pgm 3 slice0aoutput.pgm

echo -e "\n"
echo "Test16: Testing for Downsampling:"
./pgmReduce reduce.pgm 3 reduceout.pgm
rm reduceout.pgm

echo -e "\n"
echo "**********************************"
echo -e "\n"

echo -e "\n"
echo "Test: FOR pgmTile:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for Wrong Argument:"
./pgmTile slice0a.pgm

echo -e "\n"
echo "Test2: Testing for Bad filename:"
./pgmTile slicea.pgm out.pgm

echo -e "\n"
echo "Test3: Testing for Bad Magic Number:"
./pgmTile slice0amagicnumber.pgm out.pgm

echo -e "\n"
echo "Test4: Testing for Bad Dimension(-1):"
./pgmTile slice0abaddimension.pgm out.pgm

echo -e "\n"
echo "Test5: Testing for Bad Dimension(65536):"
./pgmTile slice0abaddimensiona.pgm out.pgm

echo -e "\n"
echo "Test6: Testing for Bad Max Gray Value:"
./pgmTile slice0abadgray.pgm out.pgm

echo -e "\n"
echo "Test7: Testing For Large Comment:"
./pgmTile slice0acomment.pgm out.pgm

echo -e "\n"
echo "Test8: Testing For Too Much Data:"
./pgmTile muchdata.pgm out.pgm

echo -e "\n"
echo "Test9: Testing For Too Little Data:"
./pgmTile littledata.pgm out.pgm

echo -e "\n"
echo "Test10: Testing For Failed in Malloc:"
./pgmTile mallocfailed.pgm out.pgm

echo -e "\n"
echo "Test11: Testing no Paramaters:"
./pgmTile

echo -e "\n"
echo "**********************************"
echo -e "\n"

echo -e "\n"
echo "Test: FOR pgmAssemble:"
echo "**********************************"

echo -e "\n"
echo "Test1: Testing for Wrong Argument:"
./pgmAssemble slice0a.pgm


echo -e "\n"
echo "Test2: Testing for No Arguments:"
./pgmAssemble slice0a.pgm

echo -e "\n"
echo "**************TERMINATED********************"
echo -e "\n"
