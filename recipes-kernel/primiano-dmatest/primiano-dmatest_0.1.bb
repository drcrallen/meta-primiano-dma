SUMMARY = "Primiano's DMA test module"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://intel_edison_spi_working.c;mdt=408c63986b074dacec4c216a5f8dbb69"

inherit module

PR = "r0"
PV = "0.1"

SRC_URI = "file://Makefile \
           file://intel_edison_spi_working.c \
          "

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
