CC = gcc
WINDRES = windres
CFLAGS = -l shell32 -l user32 -mwindows

all: install.exe uninstall.exe

install.exe: install.c installer_res.o
	$(CC) install.c installer_res.o -o install.exe $(CFLAGS)

uninstall.exe: uninstall.c
	$(CC) uninstall.c -o uninstall.exe $(CFLAGS)

installer_res.o: installer.rc resource.h
	$(WINDRES) installer.rc -o installer_res.o

clean:
	rm -f *.o *.exe
