#!/bin/sh

INITIALIZER=taskFactoryInitializer2D.hh
HEADER=taskFactoryAggregateHeader2D.hh

SRC_TMP=src.txt
TMP=tmp.txt

rm -f $HEADER $INITIALIZER $SRC_TMP > /dev/null 2> /dev/null;

ls *.cpp | grep -v plbXml.cpp | tr '\n' ' ' > $SRC_TMP


for file in $(ls *.h);
do
    grep "#ifdef TASK_LIST" $file > /dev/null
    sig=$?

    if [ $sig -ne 0 ] 
    then
	continue
    fi
    cpp -DTASK_LIST < $file > $TMP
    grep addToTaskMap $TMP | tee -a $INITIALIZER
    echo "#include \""$file"\"" >> $HEADER
done;

rm $TMP > /dev/null 2> /dev/null