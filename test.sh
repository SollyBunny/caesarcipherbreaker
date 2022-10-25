echo -e "\x1b[31mBuilding word hash table\x1b[0m"
make build-encode
echo -e "\x1b[31mHashing all words\x1b[0m"
make run-encode
echo -e "\x1b[31mBuilding deciphering thing\x1b[0m"
make build-decipher
echo -e "\x1b[31mPlayground time\x1b[0m"
while true; do
	read -p "> " str
	./decipher "$str"
done
