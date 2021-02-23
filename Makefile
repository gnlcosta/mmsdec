all:
	$(CC) -o mmsdec mmsdec.c mms_decode.c

debug:
	$(CC) -DDEBUG_ON=1 -o mmsdec mmsdec.c mms_decode.c

clean:
	rm -f *.o mmsdec *~ *.bin
