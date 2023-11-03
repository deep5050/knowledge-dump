# Building and Installing ONIE on KVM/QEMU (Open Network Install Environment) with DUE

In this guide, we will walk through the steps to build and install ONIE (Open Network Install Environment) on KVM/QEMU using the DUE tool. DUE is used to create a Debian Docker environment for cross-compiling ONIE. Here are the steps involved:

**Step 1: Install DUE**
To get started, you need to install DUE. DUE is used to create a Debian Docker environment for cross-compiling ONIE. First, clone the DUE repository and navigate to the DUE directory.

```bash
git clone https://github.com/CumulusNetworks/DUE.git
cd DUE
```

**Step 2: Enable Docker Experimental Features**
To make the `--platform` argument work during Docker container creation, you need to enable experimental features in Docker. Edit the Docker daemon configuration file.

```bash
sudo vi /etc/docker/daemon.json
```

Add the following content to the file:

```json
{
    "experimental": true
}
```

Save the file and exit the text editor. Then, restart Docker to apply the experimental changes.

```bash
systemctl restart docker
```

**Step 3: List Available DUE Targets**
You can list all the available targets that can be built with DUE by running the following command:

```bash
./due --create help
```

**Step 4: Select ONIE Project and Prepare Debian System**
Select the ONIE project that you want to build with Debian 10. Note that this step prepares the Debian system to be compatible with ONIE compilation. Run the following command:

```bash
./due --create --platform linux/amd64 --name onie-build-debian-10 --prompt ONIE-10 --tag onie --use-template onie --from debian:10 --description "ONIE Build Debian 10"
```

**Step 5: Create the Docker Container and Log In**
To create the Docker container and log in, run the following command:

```bash
./due --run
```

This command will detect the last built Docker image and create a container. The container will have a volume mounted to `/home/`, which means the container's filesystem is accessible on the host, allowing you to see all the files on the host as well.

**Step 6: Clone ONIE Repository**
Inside the Docker environment, clone the ONIE repository and configure your Git user information:

```bash
cd ~
git clone https://github.com/opencomputeproject/onie.git
git config --global user.email "dipankarpal5050@gmail.com"
git config --global user.name "Dipankar Pal"
cd ~/onie/build-config
```

**Step 7: Build ONIE**
Now, you can build ONIE with the following commands:

```bash
make MACHINE=kvm_x86_64 signing-keys-generate
make MACHINE=kvm_x86_64 -j4 shim-self-sign
make -j 18 MACHINE=kvm_x86_64 all recovery-iso
```

**Step 8: Build a Demo ONIE-Installer Image**
To build a demo ONIE-installer image, use the following command:

```bash
make -j 18 MACHINE=kvm_x86_64 demo
```

These steps will guide you through building and installing ONIE on KVM/QEMU using DUE. Make sure to follow each step carefully to ensure a successful setup.
