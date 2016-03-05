FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-applied-patch-from-DOOM-on-Edison-with-adafruit2.8-T.patch"
SRC_URI += "file://0002-applied-patch-from-DMA-SPI-8-bit-write-working-in-3..patch"
SRC_URI += "file://0003-Enable-SPI-DMA-on-Intel-Edison.patch"

