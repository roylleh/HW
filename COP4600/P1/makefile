patch:
	tar -xf Manual-NewFiles.tar -C /
	tar -xf Patch-Report-TestFiles.tar

	diff -ru / patch/ | grep -v ^O > /Project1.patch
	rm -rf patch

	patch -p0 < /Project1.patch
	rm /Project1.patch

	make install -C /usr/src/releasetools
	make dependall install -C /usr/src/include
	make dependall install -C /usr/src/lib

test:
	clang -Wall gettag.c -o gettag
	clang -Wall settag.c -o settag
	clang -Wall p1_test.c -o p1_test
	clang -Wall p1test.c -o p1test
