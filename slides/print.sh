#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
output_dir="${script_dir}/_handout"

mkdir -p "${output_dir}"

sed -e "s/fonts\\/NotoColorEmoji\\/NotoColorEmoji.ttf/fonts\\/OpenMoji\\/OpenMoji-Black.ttf/g" \
    -e "/disableIncrementalSlides/s/false/true/g" \
    "${script_dir}/slides.html" > "${script_dir}/handout.html"

size="1024x576"

docker run --rm -t -v "${output_dir}":/slides -v "${script_dir}":/home/user/slides astefanutti/decktape --size "${size}" /home/user/slides/handout.html handout.pdf
