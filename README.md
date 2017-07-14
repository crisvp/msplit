# msplit

A small utility to parse files containing multi-word strings.

## Installation

All you need is a C compiler and GNU make. Tested on MacOS, but should run on anything.

Edit the Makefile if you need to and then just run `make install`.

## Example

```
msplit -f /var/log/apache.log | cut -d\" -f6 | head -2
GET /SRID/FUNX/RBX/JSON HTTP/1.1
GET /SRID/FUNX/RBX/JSON HTTP/1.1
```

## To do

* Make matchsplit() not destroy its input.
* Stick matchsplit() in a library.
* Don't require a -f, just use extra arguments.
* Write man-pages, I guess.

## Credits

`msplit` project by Cris van Pelt <cris.vanpelt@gmail.com>
`matchsplit()` code "borrowed" from Wessel Dankers.

## License

Distributed under the terms of the MILF General Software License.
