# A quick note on how to use devtool in yocto projects for better productivity.


## Project source tree

```bash
ubuntu:~/playground/poky$ tree -L 1
.
├── Makefile
├── bitbake
├── documentation
├── build
├── meta
├── meta-dipankar
├── meta-dipankar-append
├── meta-poky
├── meta-selftest
├── meta-skeleton
├── meta-yocto-bsp
├── oe-init-build-env
└── scripts

```

# Using devtool
1. create a layer

```shell
ubuntu:~/playground/poky$ bitbake-layers create-layer meta-dipankar
```

2. Add the layer to build/conf/bblayers.conf

```shell
ubuntu:~/playground/poky/build$ bitbake-layers add-layer ../meta-dipankar
```

3. create a workspace 

```shell
ubuntu:~/playground/poky$ devtool create-workspace
```
4. Add a remote project  to the workspace (for example gnu-hello)

```shell
ubuntu:~/playground/poky/build/workspace$ devtool add https://ftp.gnu.org/gnu/hello/hello-2.12.tar.gz

```
This will create a gnu-hello recipe in workspace

5. Build the image and see if any error before pushing the changes into our base-layer

```shell
ubuntu:~/playground/poky/build/workspace$ devtool build hello

```

6. If build passes. go to `workspace/src/hello` and commit the initial changes

```shell
ubuntu:~/playground/poky/build/workspace/sources/hello$ git status
ubuntu:~/playground/poky/build/workspace/sources/hello$ git commit -m "message"

```
7. Export the workspace recipe to the base recipe dir ( It is suggested to <mark style="background: #FFF3A3A6;">keep the original recipe in the base recipe layer and apply patches with bbappend only in a separate recipe layer</mark>)

```shell
ubuntu:~/playground/poky/build/workspace$ devtool finish hello ../../meta-dipankar
```
where `meta-dipankar` is my base-layer

8. it is best a best practice to clear the hello recipe form workspace and build again from the base-layer we just updated

```shell
ubuntu:~/playground/poky/build/workspace$ devtool reset hello
```
9. fetch the recipe from base-layer again

```shell
ubuntu:~/playground/poky/build/workspace$ devtool modify hello
```
10. do the necessary changes in the `workspace/src/hello/` dir and commit the changes. Then update the recipe with patches in the bbappend file instead of the base recipe

```shell
ubuntu:~/playground/poky/build/workspace$ devtool update-recipe hello ../../meta-dipankar-append
```

`meta-dipankar-append` should be created with `bitabke-layers create ` `bitbake-create-layers add-layer ` commands manually.

11. Now onwards you can build as usual
12. test the application by deploying it to the target

```shell
ubuntu:~/playground/poky/build/workspace$ devtool deploy-target hello root@192.168.7.2
```
