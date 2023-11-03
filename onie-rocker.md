To simulate a QEMU device as a switch we need `rocker` configured with qemu.
Use the below Python script to generate the qemu commands:

```python
#!/usr/bin/env python3

import json
import subprocess

def generate_qemu_command(config):
    command = [
        'sudo', 'qemu-system-x86_64',
        '--enable-kvm', '-cpu', 'host',
        '-smp', f'{config["cpu"]}',
        '-m', f'{config["ram"]}',
        '-name', 'onie',
        '-boot', 'order=d,once=d',  # skipping cdrom, always boot from disk
        '-drive', f'file={config["disk"]},media=disk,if=virtio,index=0',
        '-vnc', '0.0.0.0:128',
        '-device', 'virtio-net,netdev=onienet,mac=52:54:00:13:34:1E',  # management interface assignment
        '-netdev', 'user,id=onienet,hostfwd=tcp::4022-:22',  # management interface with SSH port forwarding
        '-nographic',
        f'-serial telnet:localhost:{config["telnet_port"]},server',  # dynamic telnet port
    ]

    num_tap = config['num_tap_interfaces']

    # Generate the rocker len-ports
    partial_command = "-dev rocker,name=sw1"
    len_ports = str(num_tap)
    port_details = ",".join(f"ports[{i}]=dev{i}" for i in range(num_tap))
    tap_command = f"-device rocker,name=sw1,len-ports={len_ports},{port_details}"

    netdev_command = " ".join(f"-netdev tap,id=dev{i},ifname=tap{i+1}" for i in range(num_tap))

    command.append(tap_command)
    command.append(netdev_command)

    return command

def main():
    with open('qemu_config.json', 'r') as config_file:
        config = json.load(config_file)

    qemu_command = generate_qemu_command(config)
    concatenated_string = " ".join(qemu_command)
    print(concatenated_string.strip())
    # subprocess.run(qemu_command)

if __name__ == '__main__':
    main()
```

Config file:

```json
{
    "cpu": 2,
    "ram": 2048,
    "disk": "dent.qcow2",
    "telnet_port": 9500,
    "num_tap_interfaces": 50
}
```

Here TAP is used to create the virtual interfaces for the guest OS

> This command is tested on qemu version 2.11.1
