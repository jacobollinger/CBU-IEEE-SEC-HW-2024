#!/bin/bash

video_dir=$1
output_dir=$video_dir/split_videos

chunk_duration=6

mkdir -p $output_dir

for video in $video_dir/*.mp4; do
    video_name=$(basename $video)
    video_name=${video_name%.*}
    ffmpeg -i $video -c copy -map 0 -segment_time $chunk_duration -f segment -reset_timestamps 1 $output_dir/$video_name-%03d.mp4
done
