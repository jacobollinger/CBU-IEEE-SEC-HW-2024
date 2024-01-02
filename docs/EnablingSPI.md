# How To Setup SPI On a Jetson Orin Nano

It took nearly all winter break to figure out SPI on a Jetson Orin Nano and to
debug all of the things that didn't work with it, so here are the simplest steps
to enable it.

1. Enable SPI in the device tree using the following command:

```
sudo /opt/nvidia/jetson-io/config-by-function.py -o dtb spi1
```

If the command gives an error about the file `/boot/kernel_tegra*-user-custom.dtb` and `/mnt/APP/boot/kernel_tegra*-user-custom.dtb` being the same file, then remove the one in the boot directory and try again.

2. Reboot the device

3. Check that the device is enabled by running the following command:

```
sudo /opt/nvidia/jetson-io/config-by-function.py -l enabled
```

4. Start the SPI driver by running the following command:

```
sudo modprobe spidev
```

This command will need to be run every time the device is rebooted. To make it load automatically on boot, run the following commands:

```
echo "spidev" | sudo tee -a /etc/modules-load.d/spidev.conf
```


5. Check that the SPI driver is running by running the following command:

```
ls /dev/spidev*
```
If the command returns `/dev/spidev0.0  /dev/spidev0.1` then the SPI driver is running and it is ready to be used.
