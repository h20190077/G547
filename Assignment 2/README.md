kernel module for a driver that reads the capacity of a USB pen drive. Make sure your
USB pen drive is a valid USB attached SCSI device. Discussion on UAS devices and SCSI
commands were discussed in one of the recent lectures.
Output of your driver should be shown in the kernel log and must follow following guidelines.
● Upon insertion of the kernel module. It should just log “UAS READ Capacity Driver
Inserted”.
● After insertion pf kernel module, If an USB drive with known VID PID (already known
to your driver) is inserted, your driver should detect it, and print “Known USB drive
detected”
● It should read it’s descriptors and print the following information in log.
○ VID, should come from descriptor
○ PID, should come from descriptor
○ Device or Interface Class
○ Interface Subclass
○ Interface Protocol
○ Number and type of endpoints
