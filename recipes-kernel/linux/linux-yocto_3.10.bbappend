FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "\
 file://0001-Fixes-to-Intel-trace-includes-to-make-the-kernel-bui.patch \
 file://0002-applied-patch-from-DOOM-on-Edison-with-adafruit2.8-T.patch \
 file://0003-applied-patch-from-DMA-SPI-8-bit-write-working-in-3..patch \
 file://0004-Enable-SPI-DMA-on-Intel-Edison.patch \
"

