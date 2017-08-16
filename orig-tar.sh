#!/bin/sh -e

# called by uscan with '--upstream-version' <version>
DIR=ATLAS
DIRTARGET=atlas-$2
TAR=../atlas_$2.orig.tar.bz2

# add TexDoc to tarball
tar -xf $TAR
mv $DIR $DIRTARGET
git clone https://github.com/math-atlas/math-atlas.git
mv math-atlas/AtlasBase/TexDoc/ $DIRTARGET
rm -rf math-atlas
rm $TAR
tar -caf $TAR -X debian/orig-tar.exclude $DIRTARGET
rm -rf $DIRTARGET
