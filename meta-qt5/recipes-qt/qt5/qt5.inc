# Copyright (C) 2012 O.S. Systems Software LTDA.

inherit qmake5_base

# Qt5 is dependent on icu for localization
ICU = "icu "
ICU_powerpc = "pango"

DEPENDS += "virtual/libgl freetype jpeg libpng zlib openssl glib-2.0 ${ICU}"

require qt5_arch.inc

QT_MODULE ?= "${BPN}"

QT_DISTRO_FLAGS ?= "-no-accessibility -no-sm"
QT_DISTRO_FLAGS_linuxstdbase = "-sm"

# Some can be used only for certain QT_MODULEs, so define them here, 
# but add them to QT_CONFIG_FLAGS e.g. in qtbase.inc
QT_SQL_DRIVER_FLAGS ?= "-no-sql-ibase -no-sql-mysql -no-sql-psql -no-sql-odbc -plugin-sql-sqlite"
QT_GLFLAGS ?= ""
QT_XML ?= "-xmlpatterns"
QT_WEBKIT ?= "-webkit"
QT_PHONON ?= "-phonon"
QT_DBUS ?= "-qdbus"
QT_MULTIMEDIA ?= "${@base_contains('DISTRO_FEATURES', 'pulseaudio', '-pulseaudio', '-no-pulseaudio', d)}"
QT_MODULE_FLAGS ?= ""
QT_NAS ?= "-no-nas-sound"
QT_NIS ?= "-no-nis"
QT_CUPS ?= "-no-cups"
QT_STL ?= "-stl"
QT_SYSTEM_LIBS ?= "-system-libjpeg -system-libpng -system-zlib"
QT_TESTS ?= "-nomake tests"
QT_EXAMPLES ?= "-nomake examples"
QT_DEMOS ?= "-nomake demos"

QT_CONFIG_FLAGS += " \
  -release \
  -reduce-relocations \
  -shared \
  -silent \
  -glib \
  -no-pch \
  -no-rpath \
  -pkg-config \
  ${QT_SYSTEM_LIBS} \
  ${QT_NIS} \
  ${QT_CUPS} \
  ${QT_SQL_DRIVER_FLAGS} \
  ${QT_DISTRO_FLAGS} \
  ${QT_MODULE_FLAGS} \
  ${QT_GLFLAGS} \
  ${QT_TESTS} \
  ${QT_EXAMPLES} \
  ${QT_DEMOS} \
"

do_configure() {
#    set_arch
    set_endian

    if [ ! -e bin/qmake ]; then
        ln -sf ${OE_QMAKE_QMAKE} bin/qmake
    fi

    if [ ! -e mkspecs/${TARGET_OS}-oe-g++ ]; then
        ln -sf linux-g++ mkspecs/${TARGET_OS}-oe-g++
    fi

    # replace common files with our version
    cp -f ${WORKDIR}/g++.conf mkspecs/common/g++-unix.conf
    cp -f ${WORKDIR}/linux.conf mkspecs/common/linux.conf

    # Avoid problems with the linkers, since we want the linker to be g++
    unset LD
}

do_compile() {

    unset CFLAGS CXXFLAGS AR

    oe_runmake ${EXTRA_ENV}
}

do_install() {
    oe_runmake install INSTALL_ROOT=${D}
}

PACKAGES =. "${PN}-tools ${PN}-plugins ${PN}-plugins-dbg "
FILES_${PN}-tools = "${bindir}/*"
FILES_${PN}-plugins = "${libdir}/${QT_DIR_NAME}/plugins/*/*${SOLIBSDEV}"
FILES_${PN}-plugins-dbg = "${libdir}/${QT_DIR_NAME}/plugins/*/.debug/*"

FILES_${PN}-dev += " \
        ${libdir}/cmake/* \
        ${libdir}/*.prl \
        ${includedir}/qt5/* \
        ${datadir}/qt5/* \
"