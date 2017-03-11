all:
	$(CC) -o mmsdec mmsdec.c mms_decode.c

clean:
	rm -f *.o mmsdec *~ *.bin
