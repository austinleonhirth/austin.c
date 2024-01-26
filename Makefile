# Default
austin: *.c
	gcc -o austin austin.c

# Put into bin
update:
	sudo rm -f /bin/austin
	sudo cp austin /bin/austin