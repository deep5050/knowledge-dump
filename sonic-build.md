## Installation Steps for SONiC on Ubuntu

### Install Curl
- Command: `sudo apt install curl`
- Reference: [Install Curl on Ubuntu](https://linuxize.com/post/how-to-install-and-use-curl-on-ubuntu-18-04/)

### Install MAKE
- Command: `sudo apt install make`
- Reference: [Install Make on Ubuntu](https://linuxize.com/post/how-to-install-make-on-ubuntu-18-04/)

> Creating on Docker 19. (You may omit this step)


### Remove Docker
1. Check for installed Docker packages:
   - Command: `dpkg -l | grep -i docker`
   - Reference: [How to Completely Uninstall Docker](https://askubuntu.com/questions/935569/how-to-completely-uninstall-docker)

2. Purge Docker packages:
   - Command: 
     ```bash
     sudo apt-get purge -y docker-engine docker docker.io docker-ce docker-ce-cli docker-compose-plugin
     sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce docker-compose-plugin
     ```
   - Reference: [How to Completely Uninstall Docker](https://askubuntu.com/questions/935569/how-to-completely-uninstall-docker)

### Install Docker 19 Version
- Reference: [Install Docker on Ubuntu 18.04](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04)
1. Run the following commands to install Docker 19.03.9:
   - Command: 
     ```bash
     sh get-docker.sh --version 19.03.9 --channel stable
     sudo usermod -aG docker sonic
     ```
   - Reference: [Install Docker on Ubuntu 18.04](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04)
   
   **Note:** Downgrading to Docker 19 is possible on Ubuntu 20.04 LTS.

### Fetch SONiC Source Code
- Command: `git clone --recurse-submodules https://github.com/sonic-net/sonic-buildimage.git`

### Install Python Modules
1. Install Python3-pip:
   - Command: `sudo apt install -y python3-pip`
   
2. Install j2cli using pip:
   - Command: `pip3 install --user j2cli`
   - Set PATH to include the installed script:
     - Command: `export PATH=/home/sonic/.local/bin:$PATH`

   **Note:** You might receive a warning about the script location; you can consider adding the directory to PATH or use `--no-warn-script-location` to suppress the warning.

### Ensure Overlay Module
- Ensure the 'overlay' module is loaded on your development system:
  - Command: `sudo modprobe overlay`

### Build SONiC
1. Navigate to the SONiC source code directory:
   - Command: `cd sonic-buildimage`

2. Choose a specific branch (replace `[branch_name]` with the desired branch name):
   - Command: `git checkout [branch_name]`

3. Initialize the build environment:
   - Command: `make init`

4. Configure the platform and ASIC vendor (replace `[ASIC_VENDOR]` with the appropriate vendor):
   - Command: `make configure PLATFORM=[ASIC_VENDOR]`

5. Build SONiC:
   - Command: `make SONIC_BUILD_JOBS=4 all`
   - Reference: [SONiC Buildimage README](https://github.com/sonic-net/sonic-buildimage/blob/master/README.md)

   **Note:** Avoid using the master branch. Check out any latest release branch for stability and reliability.

This guide provides the necessary steps to install and build SONiC on your Ubuntu system. Please follow the instructions carefully, and consider the provided references for additional information.
