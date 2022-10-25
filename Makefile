
build-encode:
	gcc encode.c -o encode -O3
	./encode

build-decipher:
	gcc decipher.c -o decipher -O3
	./decipher "QEB NRFZH YOLTK CLU GRJMP LSBO QEB IXWV ALD"
