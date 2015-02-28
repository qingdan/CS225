#!/usr/bin/env bash
allpngs="
images/gradientColorPickerTest.png
images/gridColorPickerTest.png
images/solidColorPickerTest.png
images/pacManDFS.png
images/pacManBFS.png
frames"

make all -q
if [ "$?" -ne 0 ]; then
	make all
	if [ "$?" -ne 0 ]; then
		exit -1
	fi
fi

rm -rf images
rm -rf frames

echo "diff output (none means no differences between your output and solution):"

./testStackQueue > testStackQueue.out
diff testStackQueue.out soln_testStackQueue.out
./testFills all > testFills.out
diff testFills.out soln_testFills.out

for image in $allpngs
do
	diff -r $image soln_$image | grep -v '\.svn'
done

