# Using Quilt Tool to Apply Patches in Yocto

The Quilt tool is employed to apply patches to a codebase efficiently. Below are the key commands and steps involved in the process.

## Commands

1. **push**: Apply the top patch from the `series`.
2. **pop**: Remove the effect of the last applied patch on the codebase.
3. **refresh**: Manually update the codebase and run `quilt refresh` to write changes/diff to the last pushed patch under `git/patches` folder.
4. **push -f**: Forcefully apply a patch. If errors persist, associated `.rej` files will be generated.

## Solving Hunk Errors While Applying Patches

Encountering HUNK errors during patch application is not uncommon. Follow these steps when dealing with such errors, especially during package builds:

### Example Error:

```bash
ERROR: ccsp-webui-jst-rdkb-2022q1-dunfell-r0 do_patch: Command Error: 'quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push' exited with 0  Output:
Applying patch 0006-fix_webui_port_forwarding_IPv6_rules.patch
patching file source/Styles/xb3/code/port_forwarding_edit.php
Hunk #1 FAILED at 513.
1 out of 1 hunk FAILED -- rejects in file source/Styles/xb3/code/port_forwarding_edit.php
Patch 0006-fix_webui_port_forwarding_IPv6_rules.patch does not apply (enforce with -f)
```

1. Navigate to the root git directory from the build directory:
   ```bash
   cd /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/git
   ```

2. Execute the commands provided by bitbake:
   ```bash
   quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push
   ```

3. Attempt to forcefully apply the patch:
   ```bash
   quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push -f
   ```

4. This will generate `.rej` files for each source file. Open the reject and source files in vim:
   ```bash
   vim -o source/Styles/xb3/code/port_forwarding_edit.php source/Styles/xb3/code/port_forwarding_edit.php.rej
   ```
   Update the source file only, with the reference being the reject file. No need to modify the reject file. Use `ctrl ww` to switch between the two files in vim.

5. Save the files.

6. Refresh the last patch:
   ```bash
   quilt --quiltrc /local/dpal/pon-dsl-latest/rdkb/build/tmp/work/core2-64-rdk-linux/ccsp-webui-jst/rdkb-2022q1-dunfell-r0/recipe-sysroot-native/etc/quiltrc push -f
   ```

7. Go to the `git/patches` directory and retrieve the updated patch (e.g., `0006-fix_webui_port_forwarding_IPv6_rules`). Place it in your source layers directory.
