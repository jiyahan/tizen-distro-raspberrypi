DESCRIPTION = "Package Manager API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-appfw-package-manager-dev


#PROVIDES by capi-appfw-package-manager


RDEPENDS = ""
#RDEPENDS of capi-appfw-package-manager-dev (capi-appfw-${PN}-dev)
RDEPENDS_capi-appfw-${PN}-dev += "capi-appfw-package-manager"


DEPENDS = ""
#DEPENDS of capi-appfw-package-manager
DEPENDS_append_class-native = " cmake-native"
DEPENDS_append_class-target = " cmake-native"
DEPENDS += "slp-pkgmgr"
DEPENDS += "aul"
DEPENDS += "pkgmgr-info"
DEPENDS += "ail"
DEPENDS += "dlog"
DEPENDS += "vconf"
DEPENDS += "common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-appfw-package-manager.manifest .
 
 
 
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
 
 MAJORVER=`echo 0.0.29 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.0.29 -DMAJORVER=${MAJORVER}
 
 make 
 
 
 
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
PACKAGES += " capi-appfw-package-manager-dev "
PACKAGES += " capi-appfw-package-manager "

capi-appfw-package-manager-dev_files = ""
capi-appfw-package-manager-dev_files += "capi-appfw-package-manager.manifest"
capi-appfw-package-manager-dev_files += "${prefix}/include/appfw/package_manager.h"
capi-appfw-package-manager-dev_files += "${prefix}/include/appfw/package_info.h"
capi-appfw-package-manager-dev_files += "${prefix}/lib/libcapi-appfw-package-manager.so"
capi-appfw-package-manager-dev_files += "${prefix}/lib/pkgconfig/*.pc"

capi-appfw-package-manager_files = ""
capi-appfw-package-manager_files += "capi-appfw-package-manager.manifest"
capi-appfw-package-manager_files += "${prefix}/lib/libcapi-appfw-package-manager.so.*"
capi-appfw-package-manager_files += "${prefix}/bin/pkgmgr_tool"

FILES_capi-appfw-${PN}-dev = "${capi-appfw-package-manager-dev_files}"
FILES_capi-appfw-${PN} = "${capi-appfw-package-manager_files}"

PKG_capi-appfw-package-manager-dev= "capi-appfw-package-manager-dev"
PKG_capi-appfw-package-manager= "capi-appfw-package-manager"

require package-manager-extraconf.inc
