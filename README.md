charybdis (ch /cuh/ for short) is a basic password management and generation system for Linux.

## Usage

TBA

## Building

To build, run `make`.
To install, run `sudo make install`.
To remove, run `sudo make remove`

## TODO

* break up ch_file() into separate file manipulation functions
* implement a ch_find() function to set an fseek() offset at entry line in vault and use it in ch_read() and ch_delete() functions
* implement a ch_edit() function as a macro for ch_delete() followed by ch_write()
* implement file en- and decryption
* add a mode for vault manipulation
* add runtime configuration capabilities
* refactor code
