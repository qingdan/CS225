#!/usr/bin/env bash
allimgs="outHalf.png
outCopy.png
outRotated.png
outPruned.png
outEtc.png"

make -q
if [ $? -ne 0 ]
then
	make all
	if [ $? -ne 0 ]
	then
		exit -1
	fi
fi

./mp5 > mp5.out
diff mp5.out soln_mp5.out

for image in $allimgs
do
	diff $image soln_$image
done

