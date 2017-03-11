all:
	$(CC) -o mmsdec mmsdev.c mms_decode.c

clean:
	rm -f *.o mmsdec *~ *.bin
