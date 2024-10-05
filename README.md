## system_info_display

### A simple C codes to display system information
```plaintext
This is my first C project, and I'm eager to learn more about concepts 
like file handling using FILE *ptr and cross-compilation.
also Learn about how to make a project.
```
#### Requirements

- gcc compiler : 9.4.0+
- gnu make : 4.2.1+
- Linux

#### File Structure
```
system_info_tool/
├── src/
│   ├── main.c
│   ├── linux_info.c
│   ├── windows_info.c
│   ├── common.h
│   ├── common.c
├── include/
│   ├── linux_info.h
│   ├── windows_info.h
├── Makefile
├── README.md
```
#### Usage

- Run the `make` command to compile the code
- Run the `./system_info_tool` command to display the system information
- It will display the system information such as CPU usage, memory usage, disk usage, and network usage .etc

```bash
git clone https://github.com/Gthelurd/system_info_display.git
cd system_info_display
make
./system_info_tool
```
- or clean the code build:
```bash
make clean
rm -f src/main.o src/linux_info.o src/windows_info.o src/common.o system_info_tool
```

#### Example
```bash
$ ./system_info_tool
>>>
 ####                                                                       
#    # # #    # #####  #     ######       ###### ###### #####  ####  #    #
#      # ##  ## #    # #     #            #      #        #   #    # #    #
 ####  # # ## # #    # #     #####  ##### #####  #####    #   #      #####
     # # #    # #####  #     #            #      #        #   #      #    #
#    # # #    # #      #     #            #      #        #   #    # #    #
 ####  # #    # #      ##### ######       #      ######   #    ####  #    #
Operating System Version: Linux 5.15.0-122-generic
Kernel Version: #132~20.04.1-Ubuntu SMP Fri Aug 30 15:50:07 UTC 2024
Boot Time: 434043 seconds or 5 days 0 hours 34 minutes 3 seconds
Current User: guran2
Load Average (1min, 5min, 15min): 1.07, 1.49, 1.79
CPU Model: Intel(R) Core(TM) i5-8250U CPU @ 1.60GHz
CPU Cores: 4
CPU Frequency: 1800.00 MHz = 1.80 GHz
Total Memory: 32523972 KB = 31761 MB = 31 GB
Free Memory: 2102048 KB = 2052 MB = 2 GB
Memory Usage: 98.54%
Total Disk Space: 459332712 KB = 448567 MB = 438 GB
Free Disk Space: 329133640 KB = 321419 MB = 313 GB
Disk Usage: 28.35%
IP Address: 172.17.0.1
MAC Address: 02:42:6d:ae:11:14
CPU Usage: 24.34%
Network Interfaces: 
lo:: RX: 2411670220 bytes, TX: 2411670220 bytes
enp3s0:: RX: 0 bytes, TX: 0 bytes
wlp5s0:: RX: 4053948086 bytes, TX: 406182537 bytes
docker0:: RX: 1386354 bytes, TX: 51106433 bytes
```
#### TODO-list
- [x] NEtwork Interfaces
- [ ] Process Information
- [ ] User argument input to select information
- [ ] Performance Optimization
- [ ] Error Handling and Logging

#### say something
you can also running those in bash and get some same(?) result like the project:
```bash
uname -a && lsb_release -a && lscpu && free -h &&  df -h &&  ifconfig  
```
or
```bash 
cat /proc/version && cat /proc/stat && cat /proc/meminfo && cat /proc/cpuinfo && cat /proc/uptime && cat /proc/diskstats && cat /proc/net/dev
```
#### License

- MIT License
