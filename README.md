# ZynqDev
This repo contains support software for testing of hardware IP cores developed for Zedboard (Zynq in general). 
Tested with Xillinux 2.0 on Zedboard. OpenCV 2.4.1 has been natively compiled on the same system.
Basic VDMA functionality has been implemented. i.e. USB webcam video frames are captured and written to a specific RAM location. IP core reads from this location, processes it and then stores to another location. OpenCV routine then reads this processed frame and displays.
