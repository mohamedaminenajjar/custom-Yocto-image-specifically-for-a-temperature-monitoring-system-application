SUMMARY = "recipe that utilizes systemd to launch an mqtt application in boot"
DEESCRIPTION = "Runs sysd-mqtt.sh script using a systemd service"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://sysd-mqtt.sh \
           file://sysd-mqtt.service "

inherit systemd

#S = "${WORKDIR}/souces-unpack"

RDEPENDS:${PN}  = "bash"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "sysd-mqtt.service"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/sysd-mqtt.sh ${D}${bindir}
    
#    systemd_unitdir = /lib/systemd/
#    sysconfdir = /etc

    install -d ${D}/${sysconfdir}/systemd/system
    install -m 0644 ${S}/sysd-mqtt.service ${D}/${sysconfdir}/systemd/system
#    install -d ${D}/${systemd_unitdir}/system
#    install -m 0644 ${S}/sysd.service ${D}/${systemd_unitdir}/system
}
