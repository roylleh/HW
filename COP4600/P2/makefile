patch:
	tar -xf Manual-NewFiles.tar -C /
	tar -xf Patch-Report-TestFiles.tar

	diff -ru / patch/ | grep -v ^O > /Project2.patch
	rm -rf patch

	patch -p0 < /Project2.patch
	rm /Project2.patch

	make install -C /usr/src/releasetools
	make dependall install -C /usr/src/include
	make dependall install -C /usr/src/lib

test:
	clang -Wall pr2testV1.c -o pr2testV1
	clang -Wall pr2testV2.c -o pr2testV2
