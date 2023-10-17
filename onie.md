# A guide on how to build and Install ONIE on KVM/QEMU (Open Network Install Environment)

## Install DUE

Install DUE to create Debian docker to cross-compile ONIE

```bash
git clone https://github.com/CumulusNetworks/DUE.git
cd DUE

```
set docker experimental features on. to make  --platform argument work during docker container creation. needed by the DUE.

```bash


$ sudo vi /etc/docker/daemon.json 
"{
        "experimental": true
}"
```
restart docker to reflect the experimental changes

`systemctl restart docker`

list all the available targets that can be built with DUE
`./due --create help`

selecting ONIE project which to be built with Debian 10.
NOTE: This will just prepare the Debian system to be compatible with ONIE compilation.

```bash

./due --create --platform linux/amd64 --name onie-build-debian-10 --prompt ONIE-10 --tag onie --use-template onie --from debian:10 --description "ONIE Build Debian 10"
```

this will detect the last built docker image and create a container. The container will have a volume mounted to /home/sonic/ i.e. the container's filesystem is mounted on the host. we can see all the files on the host too!

we are inside the container now!
`./due --run`

You are now under a docker env.

Clone ONIE now

```bash
cd ~
git clone https://github.com/opencomputeproject/onie.git
git config --global user.email "dipankarpal5050@gmail.com"
git config --global user.name "Dipankar Pal"
cd ~/onie/build-config

make MACHINE=kvm_x86_64 signing-keys-generate
make MACHINE=kvm_x86_64 -j4 shim-self-sign
make -j 18 MACHINE=kvm_x86_64 all recovery-iso 
```

To build a demo onie-installer image run

`make -j 18 MACHINE=kvm_x86_64 demo`

