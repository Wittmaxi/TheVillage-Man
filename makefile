all:
	sudo g++ ./src/manpage.cpp -o /var/www/cgi-bin/manpage.cgi -lwcp
	sudo cp ./src/style.css /var/www/html/style.css
