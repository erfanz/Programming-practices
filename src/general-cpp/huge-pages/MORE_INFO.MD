# Useful Linux commands to work with memory and Hugepages:

See system's page size: 
```
getconf PAGESIZE
```

More complete information about page sizes, including hugepages:
```
cat /proc/meminfo
```

Information about memory and cpu and numa nodes:
```
lscpu
```

The root huge page control directory in sysfs is `/sys/kernel/mm/hugepages`.
For each huge page size supported by the running kernel, a subdirectory will exist, of the form: `hugepages-${size}kB`

## Managing Hugepages
Creating 8192 hugepages on socket 0 (assuming 2MB hugepages):
```
sudo echo 8192 | sudo tee /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages > /dev/null
```

and creating 8192 hugepages on each socket, on a 2-socket system:
```
sudo echo 8192 | sudo tee /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages /sys/devices/system/node/node1/hugepages/hugepages-2048kB/nr_hugepages > /dev/null
```

To remove the shared memory key 13:
```
sudo ipcrm -M 13
```

To check the max allocation size for shared memory (i.e. SHMMAX):
```
sudo cat /proc/sys/kernel/shmmax
```

To change that to, say, 134217728 bytes (or 128 MB):
```
sudo echo 134217728 | sudo tee /proc/sys/kernel/shmmax /proc/sys/kernel/shmall > /dev/null 
```
or
```
sudo sysctl -w kernel.shmmax=134217728
```

