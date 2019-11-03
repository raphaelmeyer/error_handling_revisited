# Slides

* `C` window clone
* `P` presentation mode

## Printing

docker run --rm -t -v `pwd`:/slides -v ~/<...>/error_handling_revisited:/home/user astefanutti/decktape /home/user/slides/slides.html slides.pdf
qdpf --pages slides.pdf 1-3,5,7-23,45,... -- slides.pdf handout.pdf
