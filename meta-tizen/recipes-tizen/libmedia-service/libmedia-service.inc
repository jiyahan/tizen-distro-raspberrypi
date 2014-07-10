DESCRIPTION = "Media information service library for multimedia applications"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache License, Version 2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libmedia-service-dev


#PROVIDES by libmedia-service


RDEPENDS = ""
#RDEPENDS of libmedia-service-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libmedia-service"

#RDEPENDS of libmedia-service (${PN})
RDEPENDS_${PN} += "eglibc"


DEPENDS = ""
#DEPENDS of libmedia-service
DEPENDS += "libmm-fileinfo"
DEPENDS += "libmedia-thumbnail"
DEPENDS_append_class-native = " cmake-native"
DEPENDS_append_class-target = " cmake-native"
DEPENDS += "drm-client"
DEPENDS += "tizen-platform-config"
DEPENDS += "libmm-common"
DEPENDS += "aul"
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "libexif"
DEPENDS += "media-server"
DEPENDS += "sqlite3"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q 
 cp ${S}/packaging/libmedia-service.manifest .
 
 
 
}
do_patch_append() {
    bb.build.exec_func('do_prep', d)
}

do_configure() {
}

do_compile() {
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 CFLAGS="-O2 -g -m64 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables" ; export CFLAGS ;
 CXXFLAGS="${CXXFLAGS:--O2 -g -m64 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables}" ; export CXXFLAGS ;
 FFLAGS="${FFLAGS:--O2 -g -m64 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -I%_fmoddir}" ; export FFLAGS ;
 LD_AS_NEEDED=1; export LD_AS_NEEDED ;
 
 
   cmake \
         -DCMAKE_VERBOSE_MAKEFILE=ON \
         -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
         -DCMAKE_INSTALL_LIBDIR:PATH=${prefix}/lib \
         -DINCLUDE_INSTALL_DIR:PATH=${prefix}/include \
         -DLIB_INSTALL_DIR:PATH=${prefix}/lib \
         -DSYSCONF_INSTALL_DIR:PATH=${sysconfdir} \
         -DSHARE_INSTALL_PREFIX:PATH=${prefix}/share \
         -DCMAKE_SKIP_RPATH:BOOL=ON \
         -DBUILD_SHARED_LIBS:BOOL=ON \
         ${EXTRA_OECMAKE} . 
 make -j16
 
 
 
}

do_install() {
 echo export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 #License
 mkdir -p ${D}/${prefix}/share/license
 cp -rf ${WORKDIR}/libmedia-service-0.2.43/LICENSE ${D}/${prefix}/share/license/libmedia-service
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x\$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libmedia-service-dev "
PACKAGES += " libmedia-service "

libmedia-service-dev_files = ""
libmedia-service-dev_files += "libmedia-service.manifest"
libmedia-service-dev_files += "${prefix}/lib/pkgconfig/libmedia-service.pc"
libmedia-service-dev_files += "${prefix}/include/media-service/*.h"

libmedia-service_files = ""
libmedia-service_files += "libmedia-service.manifest"
libmedia-service_files += "${prefix}/lib/libmedia-service.so"
libmedia-service_files += "${prefix}/lib/libmedia-service.so.1"
libmedia-service_files += "${prefix}/lib/libmedia-service.so.1.0.0"
libmedia-service_files += "${prefix}/lib/libmedia-svc-hash.so"
libmedia-service_files += "${prefix}/lib/libmedia-svc-hash.so.1"
libmedia-service_files += "${prefix}/lib/libmedia-svc-hash.so.1.0.0"
libmedia-service_files += "${prefix}/lib/libmedia-content-plugin.so"
libmedia-service_files += "${prefix}/lib/libmedia-content-plugin.so.1"
libmedia-service_files += "${prefix}/lib/libmedia-content-plugin.so.1.0.0"
libmedia-service_files += "${prefix}/share/license/libmedia-service"

FILES_${PN}-dev = "${libmedia-service-dev_files}"
FILES_${PN} = "${libmedia-service_files}"

PKG_libmedia-service-dev= "libmedia-service-dev"
PKG_libmedia-service= "libmedia-service"

require libmedia-service-extraconf.inc
