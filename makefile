all:
	sudo g++ ./src/manpage.cpp -o /var/www/cgi-bin/manpage.cgi -lwcp
	sudo cp ./src/style.css /var/www/html/style.css
	sudo chown -R apache:apache /var/www/cgi-bin

docker:
	g++ ./src/manpage.cpp -o /var/www/cgi-bin/manpage.cgi -lwcp
	cp ./src/style.css /var/www/html/style.css
	chown -R apache:apache /var/www/cgi-bin