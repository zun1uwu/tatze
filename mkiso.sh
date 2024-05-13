git clone https://github.com/limine-bootloader/limine.git \
        --branch=v7.x-binary --depth=1

make -C limine
mkdir -p iso
mkdir -p iso/boot
cp -v bin/tatze iso/boot/
mkdir -p iso/boot/limine
cp -v limine.cfg limine/limine-bios.sys limine/limine-bios-cd.bin \
        limine/limine-uefi-cd.bin iso/boot/limine
mkdir -p iso/EFI/BOOT
cp -v limine/BOOTX64.EFI iso/EFI/BOOT/
cp -v limine/BOOTIA32.EFI iso/EFI/BOOT/

xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot boot/limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        iso -o tatze.iso

./limine/limine bios-install tatze.iso