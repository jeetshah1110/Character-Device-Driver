# Character-Device-Driver

This project is contains a client application and a character device driver which performs all necessary operations.

#### Platform required
Linux Distributions
#### Architectural requirement
Intel 32 bit processor
#### User Interface
Command User Interface
#### Technology used
System Programming using C

### About Character Device Driver
- - - - 
* This project is designed to get knowledge of Hardware abstraction model of operating system.
* We select Linux operating system to write character device driver as it is open source.
Device driver is considered as a kernel module designed for specific purpose. Device
driver is used to interact between kernel and device.
* In this device driver we provide all operational function like open ,close, read, write.
* Our client application access which is written in C can access all this features of Device
Driver.
* As it is the lowest level of System programming we have to first understand layout and
functionality of kernel.
* We use Makefiles to build our device driver application.
* All the record of activities performed by the device driver are maintained in kernel log
file as we can not directly interact with the user mode entity.
- - - - 
