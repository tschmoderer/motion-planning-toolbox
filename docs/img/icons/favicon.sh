#!/bin/bash

name=rocket
names=($name $name-white $name-bw)
sizes=(16 32 64 128 256 512)

for n in ${names[@]}; do
    svg=$n.svg
    res=
    
    for i in ${sizes[@]}; do
        folder=$i"x"$i
        mkdir -p $folder
        res+=" $folder/$n.png"
        inkscape $svg -o "$folder/$n.png" -w $i -h $i 
    done

    convert $res $n.ico
    identify $n.ico
done
