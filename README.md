**charybdis** (ch /cuh/ for short) is a basic password management and generation system for Linux.

## Usage

```
Usage: ch [OPTION...] [MODE] [ENTRY]

  -C, --config=PATH          Use specified config. Default value is
                             '$XDG_CONFIG_HOME/chrc'
  -p, --pass=PASS            Write specified password directly
  -v, --vault=PATH           Manipulate specified vault. Default value is
                             '$HOME/.vault.chv'
  -l, --length=LEN           (write mode only) Generate password with specified
                             length. Default value is 8
  -s, --set=SET              (write mode only) Generate password using symbols
                             part of specified set
      --verbose              Explain what is being done
  -c, --copy                 (wayland only) Copy password to clipboard
  -e, --echo                 Echo password to stdin
  -?, --help                 Give this help list
      --usage                Give a short usage message
      --version              Print program version
```

[MODE] can be one of four values:
* write (append new entry with the name [ENTRY] to vault)
* read (extract password associated with [ENTRY] from vault)
* delete (remove [ENTRY] from vault)

## Building

To build, run `make`.
To install, run `sudo make install`.
To remove, run `sudo make remove`.

## TODO

* implement a ch_edit() function as a macro for ch_delete() followed by ch_write()
* implement file en- and decryption
* add a mode for vault manipulation
* add runtime configuration capabilities
* refactor code
