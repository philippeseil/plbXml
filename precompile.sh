#!/bin/sh

INITIALIZER=taskFactoryInitializer2D.hh
HEADER=taskFactoryAggregateHeader2D.hh

HDR_TMP=hdr.txt
SRC_TMP=src.txt
TMP=tmp.txt

rm -f $HEADER $INITIALIZER $HDR_TMP $SRC_TMP > /dev/null 2> /dev/null;

ls *.h | tr '\n' ' ' > hdr.txt
ls *.cpp | tr '\n' ' ' > src.txt

for file in $(ls *.h);
do
    grep "#ifdef TASK_LIST" $file > /dev/null
    sig=$?

    if [ $sig -ne 0 ] 
    then
	continue
    fi
    cpp -DTASK_LIST < $file > $TMP
    grep insertInList $TMP >> $INITIALIZER
    echo "#include \""$file"\"" >> $HEADER
done;

rm $TMP > /dev/null 2> /dev/null