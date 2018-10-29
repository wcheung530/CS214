all: scannerCSVsorter

scannerCSVsorter: scannerCSVsorter.c
	gcc -o scannerCSVsorter scannerCSVsorter.c
clean:
	rm -r scannerCSVsorter
