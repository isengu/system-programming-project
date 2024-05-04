all: clean compiling linking
	./bin/main txt/giris.dat txt/cikis.dat

clean:
	rm -f obj/*.o bin/main

compiling:
	gcc -I include -I lib/libfdr -c -o obj/utility.o src/utility.c
	gcc -I include -I lib/libfdr -c -o obj/main.o src/main.c
	gcc -I include -I lib/libfdr -c -o obj/converter.o src/converter.c

linking:
	gcc -o bin/main obj/main.o obj/utility.o obj/converter.o lib/libfdr/libfdr.a