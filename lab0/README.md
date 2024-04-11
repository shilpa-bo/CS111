# A Kernel Seedling
In ths lab, we create a /proc/count file that shows the current number of running processes (or tasks) running. The process table runs within kernel mode, so to access it we write a kernel module that runs in kernel mode

## Building
```shell
make 
```
Compiles the kernel module from source files using a makefile

## Running
```shell
sudo insmod proc_count.ko
cat /proc/count
```
Inserts the compiled proc_count kernel module into the running kernel.
The cat command should report a single integer representing the number of processes (or tasks) running on the
machine

## Cleaning Up
```shell
sudo rmmod proc_count
make clean
```
The sudo rmmod command removes the proc_count kernel module from the running kernel
Then, clean up the build environment by removing any compiled objects and the kernel module.

## Testing
```python
python -m unittest
```

## Kernel Version
```shell
uname -r -s -v
kernel release version module is tested on is 5.14.8
```
