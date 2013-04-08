#!/bin/bash
#
#c000:6917 outl(0x80001020, 0x0cf8)
#c000:6920 inw(0x0cfc) = 0x1801

grep '^c000:' $1 | sed \
    's/.*out\(.\)(\(.*\), *\(.*\))/W\1 \2 \3/' | \
    sed 's/.*in\(.\)(\(.*\)) *= *\(.*\)/R\1 \3 \2/'  \
    > $2
