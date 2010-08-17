require rsync.inc

PR = "r1"

SRC_URI += "file://acinclude.m4"

EXTRA_OECONF += "--disable-xattr-support --disable-acl-support"

# rsync 3.0 uses configure.sh instead of configure, and
# makefile checks the existence of configure.sh
do_configure_prepend () {
	rm -f configure configure.sh
	cp -f ${WORKDIR}/acinclude.m4 ${S}/
}

do_configure_append () {
	cp -f configure configure.sh
}
