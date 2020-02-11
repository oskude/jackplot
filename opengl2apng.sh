#!/usr/bin/bash

app="$1"
trace="${app}.trace"
video="${app}.apng"

if [[ -z "$app" ]]
then
	cat <<-'EOP'
		capture opengl app to video file
		arguments: <path_to_app>
	EOP
	exit 1
fi

set +x
apitrace trace "$app"
apitrace dump-images -o - "$trace" | \
ffmpeg -y -r 60 -f image2pipe -vcodec ppm -i pipe: -plays 1 "$video"
