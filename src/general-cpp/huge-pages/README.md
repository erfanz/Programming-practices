# Hugepages, Shared-memory and Socket binding

The goal of the code is to allocate memory using hugepages, and bind that to a certain socket.
Before compiling the code, hugepages must be enabled in the system.

To allocate 8192 hugepages on socket 0, simply run:
```
sudo echo 8192 | sudo tee /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages > /dev/null
```

And to be able to allocate huge chunks of memory (e.g. up to 4GB), adjust the `maximum_allocation_size`, by:
sudo echo 4294967296 | sudo tee /proc/sys/kernel/shmmax /proc/sys/kernel/shmall > /dev/null 

Then, compile the code using the Makefile, and run the shell script:
```
./run-me.sh REQ_SIZE
```
where `REQ_SIZE` is the requested allocation size in bytes.
Make sure that `REQ_SIZE` is a multiple of the hugepage size (i.e. 2MB).

For more information and list of relevant Linux commands, view the [./MORE_INFO.MD] tutorial.
