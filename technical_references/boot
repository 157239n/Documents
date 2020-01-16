
now that I can sort of erases everything and setup the OS entirely, may be, read up on partitions and booting stuff, and try to mess around with the structure, and may be really understand how these things work. Because now I sort of have nothing to lose anyway, and I sort of need to separate the OS partition and the data partition anyway, so I have to reinstall everything again, so why not lmao.
- try to understand everything
  - uefi
  - efi
  - master boot record
  - guid partition table
  - fdisk
  - bios boot partition
  - disk sector
  - booting process
  - how windows and linux comes into play? How can they coexist?
- try to completely delete the very first partition, the one formatted as fat32 and recover
- try to install 2 OS, mounting the same home folder
- try doing the same thing as the above, but this time encrypt the home folder, to see if the 2nd os can actually read from it
- log mint setup stuff. May be just the ctrl tab thingy in 
- try to mess around with gnu grub and try that command line thingy again, where it seems like I can boot any kernels I want, which is kinda cool and mind-blowing
- try to boot both using UEFI mode and Legacy mode
- try to have multiple data partitions, but don't mount them automatically. Then try to have them mounted automatically when the ocmputer boots up
- try to control booting 2 OSes without grub and without that messy details. The kernel should be placed inside the primary partitions already, so it's pretty much pointless to have to specify stuff like that.
- try to mount a device to an existing directory. Then try to unmount that, and see if the original files are restored, just like docker volumes
- try to create logical partitions. Previously, via gparted, I can only create primary partitions, and I've heard that primary partitions are kinda suck and serious, so can't be touched around too much. Logical ones can
- practice moving partitions around and around.
- oh yeah, try to mount the efi partition, the first one, to a folder, then sort of poke around in it, to understand the structure more

POST: power on self test
- checks bios
- checks cmos ram

- usb ports
- serial ports
- ide/sata ports

G3 state (pull power cord)
-> G2/S5 state (plugged power back in), some hw is listening for specific patterns
-> S0 power state, reached by pressing the on button, which triggers the power management unit/controller
-> BIOS/UEFI control. UEFI defines a pre-initializer
-> Driver Execution Environment is prepared, allows loading of additional hardware/software drivers. Drive encryption done here too

firmware -> BIOS -> bootloader from disk

"most bios can only boot from an MBR-partitioned disks"
"most bios can't boot from gpt"

UEFI: Unified Extensible Firmware Interface, 2nd version of EFI. UEFI and BIOS do the same thing, and more:
- boot from disks larger than 2TB (because the 2TB limit is because of the MBR thingy, and MBR is replaced by GPT here)
- tasty graphics
- mouse
- secure boot, based on chain-of-trust
- network boot
- independent from cpu architecture
- interface for devices based on EFI drivers

so, 2 modes:
- UEFI mode: requires separate partition (called "EFI partition") where bootloaders are stored
- BIOS mode: bootloader stored on disks

"Operating Systems installed in BIOS mode can't be booted using UEFI mode and vice versa". Okay this is interesting. "That's why many UEFI now support the so-called Legacy Mode"

legacy mode:
- can't Secure Boot or Fast Boot
- will be able to boot from MBR disks

/sys/firmware/efi exists ? installed in UEFI mode : not

secure boot: denying execution of unsigned code, thus enforces protection against malwares that operate in the pre-boot environment. Negative to Linux users. "To be able to boot an OS, the bootloader had to be signed by a known key, which had to be recognized by the UEFI"

so, turning off secure boot allows unsigned OSes to be booted

partitions are stored in a "partition table"

then file system, then file

MBR:
- only 4 partitions
- partitions are limited to 2TB

GUID partition table:
- 128 partitions
- partitions are limited to 9.4 ZB (windows restricts this to only 256TB)

ESP: EFI System Partition

mount: displays all attached file systems, including virtual ones like cgroups, sysfs and others
mount -t ext4
mount [option...] device_name directory, like mount /dev/sdb1 /mnt/media

what's up with /dev/* files?

find devices and filesystem type
fdisk -l
ls -l /dev/disk/by-id/usb*
dmesg
lsblk

umount directory
umount device_name
mount -t msdos /dev/fd0 /mnt/floppy. Right, so this does not follow the sd{letter}{number} nomenclature

so many people have said that you don't need a second boot loader, like grub. UEFI is enough and can allow to have the lists anyway.

might be valuable articles:
- https://unix.stackexchange.com/questions/83669/how-to-recreate-efi-boot-partition
- https://askubuntu.com/questions/706414/accidentally-deleted-efi-partition-
- https://superuser.com/questions/764799/how-to-create-an-efi-system-partition
- "just reformat and create a normal fat32 filesystem partition >.5GB and label it EFI", https://linuxsuperuser.com/reinstall-grub2-efi-bootloader-ubuntu/
- https://www.prime-expert.com/articles/a20/rebuild-efi-system-partition-from-scratch/

grub> linux  (hd0,1)/vmlinuz root=/dev/sda1
grub> initrd  (hd0,1)/initrd.img
grub> boot
