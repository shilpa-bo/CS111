# Hey! I'm Filing Here

In this lab, I successfully implemented a 1 MiB ext2 file system with 2 directories, 1 regular file, and 1 symbolic link. We are given the ext2 structures and some initial skeleton code which creates a file called cs111-base.img
in the current working directory. From this, we create a valid ext2 filesystem.

## Building
To compile the executable
```make # 
./ ext2 - create # run the executable to create cs111 -base.img
dumpe2fs cs111 -base.img # dumps the filesystem information to help debug
fsck.ext2 cs111 -base.img # this will check that your filesystem is correct
mkdir mnt # create a directory to mnt your filesystem to
sudo mount -o loop cs111 -base.img mnt # mount your filesystem , loop lets you use a file
sudo umount mnt # unmount the filesystem when you 're done
rmdir mnt # delete the directory used for mounting when you 're done
```
## Running

TODO


## Cleaning up

TODO
