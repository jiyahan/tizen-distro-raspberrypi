require Modello-Phone.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/profile/ivi/Modello_Phone;tag=d64bb84178f6a3cc17f12eca3504f079162f0283;nobranch=1"

BBCLASSEXTEND += " native "

