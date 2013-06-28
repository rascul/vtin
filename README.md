vtin
====

gtk wrapper for tintin++

THIS IS A WORK IN PROGRESS AND IS NOT FULLY FUNCTIONAL

it currently looks something like this:

[Imgur](http://i.imgur.com/33hfkZl.png?1)

probably needs gtk3 and vte2 devel packages

`tt++` must be somewhere in `$PATH`

it's not fancy and i currently have no plans to make it fancy

compile:
`gcc $(pkg-config --cflags gtk+-3.0) vte-2.90 -o vtin vtin.c $(pkg-config --libs gtk+-3.0 vte-2.90)`

run:
`./vtin &`

