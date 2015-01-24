#!/bin/sh -e

# called by uscan with '--upstream-version' <version> <file>
DIR=ATLAS
DIRTARGET=atlas-$2
TAR=../atlas_$2.orig.tar.bz2

# clean up the upstream tarball
tar jxvf $3
mv $DIR $DIRTARGET
# Before
#  cvs -d:pserver:anonymous@math-atlas.cvs.sourceforge.net:/cvsroot/math-atlas login 
cvs -z3 -d:pserver:anonymous@math-atlas.cvs.sourceforge.net:/cvsroot/math-atlas co -P AtlasBase/TexDoc
mv AtlasBase/TexDoc/ $DIRTARGET
rm -rf AtlasBase
tar -j -c -f $TAR -X debian/orig-tar.exclude $DIRTARGET
rm -rf $DIRTARGET

exit 0
