#ubuntu/i3wm/bluetooth 


## switch audio profile
To switch the audio profile for a connected Bluetooth device on Ubuntu (assuming you're using PipeWire or PulseAudio, which is standard), you can use the `pactl` command from the command line. This allows you to change profiles like A2DP (high-quality audio) or HSP (headset profile for calls).

### Prerequisites
- The Bluetooth device must already be connected (see previous responses for connecting).
- Install PulseAudio tools if needed: `sudo apt update && sudo apt install pulseaudio-utils` (though it's usually pre-installed).
- Note: Profiles include `a2dp_sink` (stereo audio), `headset_head_unit` (mono + mic), etc. The available profiles depend on the device

```bash
# list available cards and profiles
pactl list cards
# Look for the Bluetooth card (e.g., something like `bluez_card.XX_XX_XX_XX_XX_XX`). 
# Note the card index (e.g., `0`) and available profiles under "Profiles".

# set cad profile
pactl set-card-profile <card_name> <profile_name>
pactl set-card-profile bluez_card.XX_XX_XX_XX_XX_XX a2dp_sink

# check currently selected card profile
pactl list cards | grep -A 50 "Name: bluez_card.AA_BB_CC_DD_EE_FF"
# -A 50` tells `grep` to include the next 50 lines after the match (adjust the number if needed to capture all details for that card).
# under title "Active Profile:" you will see currently active profile for card
# under "Properties: device.alias" you will see name of the device
```

### example of profiles of device
- use profile -  `a2dp_sink` for high-quality audio
	- Choose codec `SBC-XQ` if your Bluetooth device supports it (check the device specs or test both)—it provides noticeably better audio fidelity for music without major drawbacks.
	- If `SBC-XQ` isn't compatible or causes issues (e.g., stuttering), fall back to `SBC` for broader compatibility.
	- For even better quality, look for `aptX` or `LDAC` profiles if available on your system/device.

- use profile - `headset_head_unit` for calls
	- choose codec `mSBC` if your device supports it —it provides noticeably better call quality without drawbacks for voice use.
	- If `mSBC` isn't compatible, `CVSD` will work as a fallback.

```bash
Profiles:
	off: Off (sinks: 0, sources: 0, priority: 0, available: yes)
	
	headset-head-unit: Headset Head Unit (HSP/HFP) (sinks: 1, sources: 1, priority: 1, available: yes)
	
	a2dp-sink: High Fidelity Playback (A2DP Sink, codec SBC) (sinks: 1, sources: 0, priority: 18, available: yes)
	
	a2dp-sink-sbc_xq: High Fidelity Playback (A2DP Sink, codec SBC-XQ) (sinks: 1, sources: 0, priority: 17, available: yes)
	
	headset-head-unit-cvsd: Headset Head Unit (HSP/HFP, codec CVSD) (sinks: 1, sources: 1, priority: 2, available: yes)
	
	headset-head-unit-msbc: Headset Head Unit (HSP/HFP, codec mSBC) (sinks: 1, sources: 1, priority: 3, available: yes)
```

## bluetoothctl (built-in bluetooth manager)
- bluetoothctl is part of bluez bluetooth stack, which is pre-installed on ubuntu

### connect / disconnect
```bash
# power on and connect
bluetoothctl power on && bluetoothctl connect 41:42:37:A3:15:00

# disconnect and power off
bluetoothctl power off
```

### connect through interactive mode (for new devices)
```bash
# before connecting, execute `bluetoothctl` in CLI, this will listen to requests -> upon request type `yes` in prompt to accept request
bluetoothctl
	# power on adapter (if not already on)
	power on

	# enable agent (required for pairing)
	agent on
	default-agent

	# scan for devices
	scan on
	
	# list available devices alongwith their name and mac-address
	devices

	# pair with a device if not already paired
	# MAC-address format: XX:XX:XX:XX:XX:XX
	pair <MAC-address-of-device>
	# If you see a prompt in the terminal (e.g., "Confirm passkey 123456 (yes/no):"), type:
	yes

	# optional, for device you are using first-time, but recommended for automatic reconnection
	trust XX:XX:XX:XX:XX:XX

	# connect device
    connect XX:XX:XX:XX:XX:XX

	# disconnect fromt he device
	disconnect XX:XX:XX:XX:XX:XX
   
	exit
```


### restart
```bash
# restart bluetooth
sudo systemctl restart bluetooth
man bluetoothctl
```

## GUI  bluetooth manager
- [blueman](https://github.com/blueman-project/blueman)


## Errors
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
