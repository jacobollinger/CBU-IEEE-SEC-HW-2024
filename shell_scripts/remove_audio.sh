#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Invalid number of arguments"
    exit 1
fi

for file in "$1"/*.{mp4,MP4,mov,MOV}; do
    mkdir -p "$1"/output

    # remove the audio from the video file
    ffmpeg -i "$file" -c copy -an "$1"/output/"${file##*/}"
done
