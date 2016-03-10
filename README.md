meta-primiano-dma
---------------------
Bitbake recipes for @primiano's dma patch set

# Applying patch set
Applying this patch set involves building an image. This patch set is known to work against the 1.6.2 poky distribution of the edison (v2.1)

1. Checkout this repository to your development machine.
1. From your Edison SDK directory enter your build environment with the normal `source poky/oe-init-build-env` commnad.
1. Add the path to this repository to the list of `BBLAYERS` in `conf/bblayers.conf`
1. If you have NEVER built the image before, build the image at least once following https://software.intel.com/en-us/node/593591
1. Prepare a clean state for the kernel build with `bitbake -c cleansstate linux-yocto`
1. Build the kernel with `bitbake -k linux-yocto` (see https://software.intel.com/sites/default/files/m/4/d/8/5/8/42868-11__Developing_Kernel_Module_on_Yocto.pdf )
1. Re-build the kernen into the image with `bitbake edison-image`
1. For your own sanity package the needed files in a clean zip with `../meta-intel-edison/utils/flash/postBuild.sh`
1. Flash the fresh package to your edison
