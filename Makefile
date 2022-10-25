
test:
	./test.sh

build-encode:
	gcc encode.c -o encode -O3

run-encode:
	./encode

build-decipher:
	gcc decipher.c -o decipher -O3

run-decipher:
	./decipher "QEB NRFZH YOLTK CLU GRJMP LSBO QEB IXWV ALD"
