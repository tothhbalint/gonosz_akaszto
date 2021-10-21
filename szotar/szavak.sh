#!/bin/sh
#melyik=1 # angol
melyik=2 # magyar
cat szotar.txt | cut -f $melyik -d : | grep -v \" |grep -v \! |grep -v -- - | grep -v , | grep -v \' | grep -v % | egrep -v [0-9] |  tr '?()' '  ' | sed "s/ /\n/g" | sort | uniq 
