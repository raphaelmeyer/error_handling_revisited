all: install

install: remark/remark.js

remark/remark.js: _build/remark/out/remark.js
	install _build/remark/out/remark.js remark/remark.js

_build/remark/out/remark.js: _build/remark/src/remark.js
	cd _build/remark && node make

_build/remark/src/remark.js: _build/remark
	cd _build/remark && npm install
	cd _build/remark && npm audit fix
	touch _build/remark/src/remark.js

_build/remark: _build
	cd _build && git clone https://github.com/gnab/remark.git

_build:
	mkdir _build
