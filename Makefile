dbc2dbf: blast-dbf.c blast.c blast.h
	cc -o dbc2dbf blast.c blast-dbf.c

test: dbc2dbf
	./dbc2dbf < ABOAC1909.dbc | cmp - ABOAC1909.dbf

clean:
	rm -f dbc2dbf*.o
