vtin
====

gtk wrapper for [tintin++](http://tintin.sourceforge.net) ([http://tintin.sourceforge.net]())

(tintin++ is a mud client for unix related operating systems)

it currently looks something like this:

![Imgur](http://i.imgur.com/LFYm5ZX.png)

probably needs gtk3 and vte2 devel packages

`tt++` must be somewhere in `$PATH`

it's not fancy and i currently have no plans to make it fancy

compile:
`gcc $(pkg-config --cflags gtk+-3.0 vte-2.90) -o vtin vtin.c $(pkg-config --libs gtk+-3.0 vte-2.90)`

run:
`./vtin &`

