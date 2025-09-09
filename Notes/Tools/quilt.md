# using quilt tool to fix patches in yocto

We use quilt tool to generally apply patches to a codebase.

# Commands

1. **push**: push/apply the top patch from the `series` .
2. **pop**: Pop / remove the affect of the last patch applied on the codebase.
3. **refresh**:  When we update  the codebase manually and run `quilt refresh` the changes / diff will be written to the last pushed patch. under `git/patches` folder.
4. **push -f**: Forcefully apply a patch. If still error occurs, associated `.rej` files  will be generated.
## Solving hunk errors while applying patches

Occasionally we come across situations while applying patches results in HUNK errors.

While building a package we find this, these are the steps to be followed:

Example error:

```bash
ERROR: ccsp-webui-jst-rdkb-2022q1-dunfell-r0 do_patch: Command Error: 'quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push' exited with 0  Output:                                                                                                 
Applying patch 0006-fix_webui_port_forwarding_IPv6_rules.patch                                                                                                                 
patching file source/Styles/xb3/code/port_forwarding_edit.php                                                                                                                  
Hunk #1 FAILED at 513.                                                                                                                                                         
1 out of 1 hunk FAILED -- rejects in file source/Styles/xb3/code/port_forwarding_edit.php                                                                                      
Patch 0006-fix_webui_port_forwarding_IPv6_rules.patch does not apply (enforce with -f)                                                                                         

```

1. From the build directory `cd` into `/local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/git` . Notice that we need to go the root git directory.


2. Run the commands bitbake tells us to:
```bash
quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push
```

3. Try to forcefully apply the patch
```bash
quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push -f
```

1. This will generate a `rej` files for each source file. Open the reject and source file in vim. `vim -o source/Styles/xb3/code/port_forwarding_edit.php source/Styles/xb3/code/port_forwarding_edit.php.rej` . **update the source file only** and reference should be the reject file. No need to update the reject file. TIPS: `ctrl ww` to switch between to two files in vim.
2. Save the files
3. Refresh the last patch. `quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push -f`
4. Go to the `git/patches` directory and get the updated patch which we can place in our source layers directory. In our example :`0006-fix_webui_port_forwarding_IPv6_rules`

