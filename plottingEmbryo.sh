#!/bin/sh

rm ./*.gif

LISTA="ls ./*.dot"
for i in $LISTA 
do
echo $i
circo -Tgif -o $i.gif $i
done
#gifsicle --delay=30 *.gif > devel.gif

