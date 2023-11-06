# Installing `DENT` within the `ONIE` Environment

Before proceeding with the installation of `DENT` inside the `ONIE` environment, ensure you have reviewed the relevant ONIE-related documentation if needed.

1. Start by entering the `ONIE` environment. Once inside, select the `:ONIE: Embed ONIE` option. This action will write ONIE on top of the primary boot-loader. After the installation is complete, the system will automatically reboot and allow you to install a Network Operating System (NOS) of your choice.

2. Choose `ONIE: Install OS`. This selection will boot into the `onie-nos-installer` mode.

3. Log in with the following credentials:
   - Username: `root`
   - Password: `onie`

4. Disable the auto-discovery mode by running the following command:

```bash
onie-stop
```

5. Download the `DENT` image from your server using `scp`. Replace the server address and file path as needed:

```bash
scp deep5050@192.168.4.97:/home/deep5050/dentOS/images/DENTOS-main_ONL-OS10_2023-10-31.0724-fdb2eef_AMD64_INSTALLED_INSTALLER dentos
```

6. Finally, proceed with the installation of `DENT`. Use the following commands to initiate the installation process:

```bash
onie-nos-install dentos
```

7. Log in with the following credentials:
   - Username: `root`
   - Password: `onl`

With these steps, you can successfully install `DENT` within the `ONIE` environment and configure it as needed.
