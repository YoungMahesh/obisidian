#ubuntu/i3wm/bluetooth 

```bash
# install
sudo apt install pavucontrol

# launch app
pavucontrol
```

### manage input/output device during call
- NOTE: your audio-profile in [[blueman]] must be set at one of the - `HeadSet Head Unit` type
	- To select audio profile: `blueman-manager` -> right-click on bluetooth-device -> Audio-profile
	- Test which profile is supported by your device using app like - Perplexity Voice Chat	
- select input/microphone device
	- Recording section -> `[app-name] input: RecordStream from` -> select device
- select output/audio device
	- Playback section -> `[app-name]: Playback on` -> select device
	