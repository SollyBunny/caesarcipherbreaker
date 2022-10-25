
test:
	echo -e "\x1b[31mBuilding word hash table\x1b[0m"
	make build-encode
	echo -e "\x1b[31mHashing all words\x1b[0m"
	make run-encode
	echo -e "\x1b[31mBuilding deciphering thing\x1b[0m"
	make build-decipher
	echo -e "\x1b[31mPlayground time\x1b[0m"
	sh -c 'while true; do read -p "> " s; ./decipher "$$s"; done'

build-encode:
	gcc encode.c -o encode -O3

run-encode:
	./encode

build-decipher:
	gcc decipher.c -o decipher -O3

run-decipher:
	./decipher "QEB NRFZH YOLTK CLU GRJMP LSBO QEB IXWV ALD"
