#######################################################
# preinstall requirements
# 1. install gcc
# 2. install gtk 
# 3. install vte2.9 
#######################################################

CC=gcc

TERMFLAGS=-pthread -I/usr/include/vte-2.91 -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lvte-2.91 -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0


all: heimdallr

heimdallr: ../heimdallr-terminal-emu.c
		${CC} ../heimdallr-terminal-emu.c ${TERMFLAGS} -o heimdallr
		strip heimdallr 


install: heimdallr 
	mkdir -p ~/.heimdallr/ ; cp -rf .. ~/.heimdallr/
	sudo apt update && sudo apt full-upgrade -y
	sudo apt install gcc build-essential libgtk-3-dev libnotify-bin zenity libvte-2.91-dev
	sudo cp heimdallr /usr/bin/
	sudo cp -rf ../xdg/heimdallr.desktop /usr/share/applications
	cp -rf ../xdg/heimdallr.desktop ~/.local/share/applications
	sudo cp -rf ../icon/heimdallr.png /usr/share/icons/hicolor/256x256/apps/
	sudo cp -rf ../icon/heimdallr.png /usr/share/icons/hicolor/256x256/apps/
	sudo cp -rf ../icon/heimdallr.png /usr/share/icons/
	zenity --info --title Heimdallr --text "Heimdallr installed !"

