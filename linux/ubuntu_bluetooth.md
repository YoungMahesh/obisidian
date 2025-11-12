#ubuntu/i3wm/bluetooth 

### bluetoothctl (built-in bluetooth manager)
```bash
	# before connecting, execute `bluetoothctl` in CLI, this will listen to requests -> upon request type `yes` in prompt to accept request
	scan on
	# MAC-address format: XX:XX:XX:XX:XX:XX
	pair <MAC-address-of-device>
	# If you see a prompt in the terminal (e.g., "Confirm passkey 123456 (yes/no):"), type:
	yes
	trust <MAC-address-of-device>
	connect <MAC-address-of-device>
	exit
```

### GUI  bluetooth manager
- [blueman](https://github.com/blueman-project/blueman)


## errors
### cannot turn on bluetooth on ubuntu  ?
#errors/bluetooth

```bash
# Try manually loading the Bluetooth modules again:
# modprobe - A Linux utility to add or remove #kernel modules
sudo modprobe -r btusb # -r == remove, remove btusb
sudo modprobe btusb # load btusb
```

```bash
# detailed information about your RAM
# Look for the "Speed" field in the output, which indicates the RAM speed in MT/s (megatransfers per second) or MHz.
sudo dmidecode -t memory
```
