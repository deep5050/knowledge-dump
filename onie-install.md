# Running ONIE on QEMU: Two Options

When it comes to running ONIE on QEMU, you have two options, each with its own advantages and disadvantages. Let's explore both methods.

## Option 1: Using the ONIE Provided Script

The ONIE distribution includes a handy script called `oni-vm.sh`, which simplifies the process of running ONIE on QEMU. This script comes with preconfigured settings, making it user-friendly but less customizable.

1. Navigate to the emulation directory:

```bash
cd ~/onie/build/emulation
```

2. Edit the `onie-vm.sh` file to modify the HDD and USB device size according to your requirements:

```bash
# Virtual Hard Drive size in GB
HARD_DRIVE_SIZE=5G
# Virtual USB Drive size in MB
USB_SIZE="4096M"
```

3. Run ONIE in legacy BIOS mode using the following command:

```bash
sudo ./onie-vm.sh run --machine-name kvm_x86_64 --machine-revision r0 --m-bios-clean --m-hd-clean --m-embed-onie --m-boot-cd --m-onie-iso ../build/images/onie-recovery-x86_64-kvm_x86_64-r0.iso
```

4. This will create a QEMU instance that can be accessed via telnet:

```bash
telnet localhost 9300
```

Additional notes:

- You can clean or format the HDD and USB with `sudo ./onie-vm.sh clean`.
- Update the virtual USB drive by running `sudo ./onie-vm.sh update-m-usb` after manually copying files under "onie/emulation-files/usb/usb-data."
- If you don't want to clean the HDD on each run, remove `--m-bios-clean --m-hd-clean` from the command.

## Option 2: Manual QEMU Commands

For more control and fine-tuning of your VM, you can directly invoke QEMU commands. This approach allows you to adjust parameters like RAM, CPU, VNC, and SSH configurations as needed.

1. Create a HDD in qcow2 format with a specified size (e.g., 5GB):

```bash
qemu-img create -f qcow2 qemu-hdd.qcow2 -o preallocation=full 5G
```

You can also resize an existing image using:

```bash
qemu-img resize qemu-hdd.qcow2 +10G
```

2. Run ONIE with the following command, adjusting parameters to your needs:

```bash
sudo qemu-system-x86_64 --enable-kvm -cpu host -smp 1 -m 256 -name onie -boot order=cd,once=d -cdrom ./onie-recovery-x86_64-kvm_x86_64-r0.iso -drive file=qemu-hdd.qcow2,media=disk,if=virtio,index=0 -vnc 0.0.0.0:128 -device virtio-net,netdev=onienet,mac=52:54:00:13:34:1E -netdev user,id=onienet,hostfwd=tcp::4022-:22 -nographic -serial telnet:localhost:9300,server
```

3. Connect to ONIE via telnet:

```bash
telnet localhost 9300
```

With this manual approach, you have more flexibility to customize your QEMU environment for running ONIE.
