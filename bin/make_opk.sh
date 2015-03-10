#!/bin/sh

rm -f fba.opk

mksquashfs skin fbasdl.dge default.gcw0.desktop ../readme.txt fba.opk -all-root -no-xattrs -noappend -no-exports
