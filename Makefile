teste: teste.c
	gcc $(CFLAGS) teste.c -o teste `pkg-config --cflags --libs gtk+-2.0` -lwiringPi
clean:
	rm *.o teste
