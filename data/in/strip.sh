#! /bin/bash

fps=10

function strip_video() {
    path=$1
    if [ -d "$path" ]; then
        if [ "${path##*/}" == "done" ]; then
            echo "Skipping $path"
            return
        fi

        for i in $path/*; do
            strip_video $i
        done
    else
        file=${path##*/}
        basename=${file%.*}

        # get the last directory in the path
        type=$(basename $(dirname "$path"))

        if [ ! -d "./images/raw/$type" ]; then
            echo "Creating directory images/raw/$type"
            mkdir -p ./images/raw/$type
        fi

        echo "Stripping $path to ./images/raw/$type/${basename}_%d.jpg"
        ffmpeg -loglevel info -i $path -vf "fps=$fps" -pix_fmt yuvj420p ./images/raw/$type/${basename}_%d.jpg
    fi


}

if [ -z "$1" ]; then
    input=./videos/raw
else
    input=$@
fi

strip_video $input
