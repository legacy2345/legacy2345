Updating the FastNoise Sources
==============================

The sources contained in this directory ar third-party source developed and
maintained by Jordan Peck at https://github.com/Auburns/FastNoise and used in
this project under an MIT license.

To update these sources, from the top-level project directory of a fresh git
clone (the directory with the configure.ac file), issue the following commands.

    git submodule init
    git submodule update
    cp 3rd_party/fastnoise/FastNoise.h legacy/3rd_party/FastNoise
    cp 3rd_party/fastnoise/FastNoise.cpp legacy/3rd_party/FastNoise

and that's it.  Maybe some day I'll add a patch to suppress the compile-time
warnings that issue from these sources.
