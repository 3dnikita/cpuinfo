CPU Summary Info and Clock Frequency Detection Utility
======================================================

The code was originally written for Windows using Borland C++ Builder back in 2006, mostly as a proof of a concept.

Then it was ported to GCC on FreeBSD in 2011 just for fun.

It's never been intended to replace the /proc/cpuinfo. In fact, I didn't even know about it back then :)

Also, the method of measuring the clock frequency implemented here is virtually useless nowadays, when CPU has a lot of cores,
each of which dynamically changes its clock speed to lower the power consumption.

But it may still be useful as a minimal working demonstration of cross-platform reading of low-level CPU information.

By cross-platform I mean OS portability, because obviously, this will work only on x86-compatible hardware, as it mostly relies on `rdtsc` and `cpuid` assembler instructions.

If interested, you may read more on the history of this utility [in my blog](https://3dnikita.com/blog/2020/04/19/cpuinfo/)

To download pre-compiled binaries, go to the [Releases page](https://github.com/3dnikita/cpuinfo/releases)


Table of contents
-----------------
 * [System Requirements](#system-requirements)
 * [Build](#build)
     - [*nix](#nix)
       * [Requirements](#requirements)
       * [Instructions](#instructions)
     - [Windows](#windows)
       * [32 Bit](#32-bit)
       * [64 Bit (Recommended)](#64-bit-recommended)
 * [Usage](#usage)


System Requirements
-------------------

 - i586-compatible CPU (x86 or x86_64)
 - POSIX-compatible OS (GNU/Linux, BSD, Mac OS X etc.) or MS Windows

To be honest, I tested this only on AMD and Intel processors,
so can't guarantee anything for Cyrix, Transmeta or VIA :)

Build
-----

#### *nix

##### Requirements

 * GNU C++ compiler (GCC) version 4.5 or higher
 * GNU Make (optional)

##### Instructions

    git clone https://github.com/3dnikita/cpuinfo.git
    cd cpuinfo
    make

As long as there is only one source file, alternatively, you may just compile it directly:

    g++ main.cpp -o cpuinfo


#### Windows

##### 32 Bit

  * Download [MinGW](http://www.mingw.org/)
  * Install GCC and GNU Make using its installation manager
  * Build the project:

        SET PATH=%PATH%;M:\mingw\bin\
        mingw32-make

    in case you're using plain `cmd.exe` interpreter

    OR

        export PATH=$PATH:/m/mingw/bin/
        mingw32-make

    if you're using Git Bash, MSYS, cygwin etc.

    (replace `M:\mingw` or `/m/mingw/` with your MinGW's installation folder path)

##### 64 Bit (Recommended)

  * Download MinGW-w64 build e.g. https://sourceforge.net/projects/mingw-w64/
  * Install GCC and GNU Make using its installation wizard
  * Build the project:

        SET PATH=%PATH%;M:\mingw64\bin\
        mingw32-make

    in case you're using plain `cmd.exe` interpreter

    OR

        export PATH=$PATH:/m/mingw64/bin/
        mingw32-make

    if you're using Git Bash, MSYS, cygwin etc.

    (replace `M:\mingw64` or `/m/mingw64/` with your MinGW-w64's installation folder path)

Usage
-----

No installation needed, just run executable:

- *nix:

      cpuinfo

- Windows 64 bit:

      cpuinfo64.exe

- Windows 32 bit:

      cpuinfo.exe

On start, the utility shows the CPU identification information, such as
brand name, model, stepping, base frequency, etc.

Every time you hit the "Enter" ("Return") key, *cpuinfo* counts the number of cycles that CPU performs during one second
and shows the measured clock speed in MHz.

To exit, type "q" and press "Enter".