## Readline with Configurable Mode Strings ##

This is a patched version of readline 6.3 that adds support for custom prompt mode indicators.

For more details on the motivation and usage see the corresponding bash repo at https://github.com/calid/bash

## Stop ##

This branch is setup to build and install a standalone version of libreadline. If all you care about are snazzy bash prompts, you're probably better off just following the install instructions for the patched version of bash linked above.

The upside of installing readline as a standalone library is _other_ programs besides bash that use readline (gdb, python, rlwrap, etc) will also display custom mode indicators.

In the case of bash, just make sure the version you have installed was configured to dynamically link to libreadline. You can check this with:

    $ ldd /bin/bash
        linux-vdso.so.1 (0x00007fffad745000)
        libreadline.so.6 => /usr/local/lib/libreadline.so.6 (0x00007f8ed7373000)
        libncursesw.so.6 => /usr/lib/libncursesw.so.6 (0x00007f8ed7106000)
        libdl.so.2 => /usr/lib/libdl.so.2 (0x00007f8ed6f02000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007f8ed6b5e000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f8ed75b9000)

If you don't see libreadline.so in the output, then your bash was built to use the embedded version of readline.  You'll need to build and install a version that dynamically links to the system libreadline.

## Install ##

    $ git clone https://github.com/calid/readline.git -b modestrs --recurse-submodules
    $ cd readline
    $ ./configure
    $ make SHLIB_LIBS=-lncurses
    $ sudo make install
    $ sudo ldconfig # if appropriate

Now follow the instructions at https://github.com/calid/bash to enable and configure your custom mode strings, restart bash or whatever readline program you're using, and enjoy!

