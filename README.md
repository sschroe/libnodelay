# libnodelay

A small wrapper library to force TCP_NODELAY on all new sockets. It is intended for use with LD_PRELOAD
on Linux and wraps the `socket` and `setsockopt` calls to enforce TCP_NODELAY being set for all TCP sockets.


## Compiling

To compile libnodelay simply run `make` inside the repository. This will build **libnodelay.so** for your host
system.

Additionally the make targets **32** and **64** are available to specifically build the library for either 32bit
or 64bit. The binary file in this case will be either **libnodelay32.so** or **libnodelay64.so** depending on the
chosen target.


## Usage

To use libnodelay add it to the LD_PRELOAD environment variable. The suggested way is to simply
export it and run your application afterwards.

```bash
export LD_PRELOAD=/path/to/libnodelay/libnodelay.so
./application
```

You may also add the 32bit and 64bit library in parallel which comes in handy when dealing with a mix of 32bit
and 64bit executables such as when using wine.

```bash
export LD_PRELOAD=/path/to/libnodelay/libnodelay32.so:/path/to/libnodelay/libnodelay64.so
./application
```

In this case you may see errors such as the following. These can be safely ignored and are merely an information
that for example the 32bit library could not be used for an 64bit application. However in that case the 64bit
library will have been loaded instead.

```bash
ERROR: ld.so: object '/path/to/libnodelay/libnodelay64.so' from LD_PRELOAD cannot be preloaded (wrong ELF class: ELFCLASS64): ignored.
ERROR: ld.so: object '/path/to/libnodelay/libnodelay32.so' from LD_PRELOAD cannot be preloaded (wrong ELF class: ELFCLASS32): ignored.
```

## Testing

A small test executable is provided and can be compiled with `make test`. When run this executable will print whether
TCP_NODELAY is set or not after creating a TCP socket.

Example:

```bash
./test
TCP_NODELAY is NOT set.

LD_PRELOAD=./libnodelay.so ./test
TCP_NODELAY is set.
```


## Contributing

You are welcome to contribute to this project, simply open a pull request with your changes and they will be considered.


## License

This project is licensed under the **GPL-3.0-or-later** License, see the [LICENSE.md](LICENSE.md) file for details
