### headset vs handsfree
- headset is better for microphone and speaker

### fix problems on #ubuntu 
```bash
# detailed information about your RAM
# Look for the "Speed" field in the output, which indicates the RAM speed in MT/s (megatransfers per second) or MHz.
sudo dmidecode -t memory

# cannot turn on bluetooth?
# Try manually loading the Bluetooth modules again:
# modprobe - A Linux utility to add or remove #kernel modules
sudo modprobe -r btusb # -r == remove, remove btusb
sudo modprobe btusb # load btusb
```

### blueman bluetooth manager
- [blueman](https://github.com/blueman-project/blueman)
- [[i3wm]] does not have GNOME like GUI, you can use bluemen in it
- how to accept pairing code?
	```bash
	bluetoothctl
	# before connecting, execute `bluetoothctl` in CLI, this will listen to requests -> upon request type `yes` in prompt to accept request
```

### fix problems on Itel #feature-phone
- error in file-transfer : One headset is already activated, please deactivate it first, to activate another
	- solution: on Itel feature phone, 
	- open Extra -> BT (Bluetooth) -> Paired device 
	- -> hover on connected device 
	- -> click center button to disconnect (this is will disconnect voice transport and enable file transfer)