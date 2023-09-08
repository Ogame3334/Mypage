#!/bin/bash

cd /root/mypage
 
DIR="build"
 
if [ ! -d $DIR ];then
  mkdir $DIR
fi

cd $DIR
cmake ..
make
./mypage