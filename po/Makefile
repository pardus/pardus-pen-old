build:
	msgfmt --output-file=tr.mo tr.po
pot:
	xgettext --keyword=_ --language=C --add-comments --sort-output -o pardus-pen.pot ../*.cpp

install:
	mkdir -p $(DESTDIR)/usr/share/locale/tr/LC_MESSAGES/ || true
	install tr.mo $(DESTDIR)/usr/share/locale/tr/LC_MESSAGES/pardus-pen.mo