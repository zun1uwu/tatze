make clean && make && ./mkiso.sh && qemu-system-x86_64 tatze.iso -d int -D qemu.log -no-reboot -m 128

# qemu-system-i386                                 \
#   -accel tcg,thread=single                       \
#   -cpu core2duo                                  \
#   -m 128                                         \
#   -no-reboot                                     \
#   -drive format=raw,media=cdrom,file=myos.iso    \
#   -serial stdio                                  \
#   -smp 1                                         \
#   -usb                                           \
#   -vga std