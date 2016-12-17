dnl $Id$
dnl config.m4 for extension cinvan

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(cinvan, for cinvan support,
dnl Make sure that the comment is aligned:
dnl [  --with-cinvan             Include cinvan support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(cinvan, whether to enable cinvan support,
dnl Make sure that the comment is aligned:
dnl [  --enable-cinvan           Enable cinvan support])

if test "$PHP_CINVAN" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-cinvan -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/cinvan.h"  # you most likely want to change this
  dnl if test -r $PHP_CINVAN/$SEARCH_FOR; then # path given as parameter
  dnl   CINVAN_DIR=$PHP_CINVAN
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for cinvan files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CINVAN_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CINVAN_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the cinvan distribution])
  dnl fi

  dnl # --with-cinvan -> add include path
  dnl PHP_ADD_INCLUDE($CINVAN_DIR/include)

  dnl # --with-cinvan -> check for lib and symbol presence
  dnl LIBNAME=cinvan # you may want to change this
  dnl LIBSYMBOL=cinvan # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CINVAN_DIR/lib, CINVAN_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CINVANLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong cinvan lib version or lib not found])
  dnl ],[
  dnl   -L$CINVAN_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CINVAN_SHARED_LIBADD)

  PHP_NEW_EXTENSION(cinvan, cinvan.c, $ext_shared)
fi
