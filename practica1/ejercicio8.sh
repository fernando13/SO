#!/bin/bash
echo $SHELL
l=0
t=0
for i in $*
do
	l=$(wc -l $i | awk '{print $1}')
	echo $l
	t=$(($t+$l))
done

echo "Total:$t, _args:$#"	