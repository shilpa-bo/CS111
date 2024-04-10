# A Kernel Seedling
In ths lab, we create a /proc/count file that shows the current number of running processes (or tasks) running. The process table runs within kernel mode, so to access it we write a kernel module that runs in kernel mode

## Building
```shell
make 
```

## Running
```shell
sudo insmod proc_count.ko
cat /proc/count
```
The last command should report a single integer representing the number of processes (or tasks) running on the
machine

## Cleaning Up
```shell
sudo rmmod proc_count
make clean
```

## Testing
```python
python -m unittest
```

## Kernel Version
```shell
uname -r -s -v
kernel release version module is tested on is 5.14.8
```
