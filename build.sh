#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra -ggdb -O3"
INCLUDES="-I./raylib-5.0_linux_amd64/include/"
LIBS="-L./raylib-5.0_linux_amd64/lib/ -l:libraylib.a -lm"

cc $CFLAGS -o counter                    counter.c                    $INCLUDES $LIBS
cc $CFLAGS -o psychophysicists_electrode psychophysicists_electrode.c $INCLUDES $LIBS
cc $CFLAGS -o game_of_life               game_of_life.c               $INCLUDES $LIBS

