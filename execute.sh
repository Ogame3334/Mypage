#!/bin/bash

cd /root/mypage
 
DIR="build"
 
if [ -d $DIR ];then
  rm -rf $DIR
fi

mkdir $DIR

cd $DIR
cmake ..
make
./mypage