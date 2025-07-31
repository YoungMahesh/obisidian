#ubuntu/i3wm/bluetooth
-  Blueman is a popular Bluetooth manager on Ubuntu

```bash
sudo apt install blueman
blueman-manager

# manage bluetooth device volume
pavucontrol
```


### Audio Profile Options
- Headset Head Unit (HSP/HFP, codec mSBC)

- **Off**
  - Disables all audio streaming to and from the device. The Bluetooth device may stay paired, but no audio will be routed through it.

- **Headset Head Unit (HSP/HFP)**
  - “HSP” (Headset Profile) and “HFP” (Hands-Free Profile) are both Bluetooth profiles primarily designed for voice calls. They enable two-way, low-quality audio suitable for microphones and phone conversations.
  - Audio is mono and quality is limited to “phone call” standard, as the main goal is to allow you to talk and listen during calls or voice chats

- **High Fidelity Playback (A2DP Sink, codec SBC)**
  - Uses the “A2DP” (Advanced Audio Distribution Profile) for high-quality, stereo audio playback (music, media, etc.).
  - **SBC codec** (Subband Codec) is the default, mandatory codec for A2DP, providing decent sound quality suitable for music listening. Most Bluetooth headphones support at least this codec.

- **High Fidelity Playback (A2DP Sink, codec SBC-XQ)**
  - Also uses A2DP but with the **SBC-XQ** (eXtreme Quality) variant of the SBC codec.
  - SBC-XQ is an unofficial, high-bitrate use of the standard SBC codec, delivering sound quality comparable to premium codecs (such as aptX HD) by increasing bitrate (often over 500kbps). This gives you higher-quality Bluetooth music even with devices that only support SBC

- **Headset Head Unit (HSP/HFP, codec CVSD)**
  - Runs HSP/HFP profile (for calls/voice) with the standard **CVSD** (Continuously Variable Slope Delta) codec.
  - CVSD operates at 8kHz—good for basic voice transmission, but not ideal for clarity or naturalness (sounds most like a typical phone call)

- **Headset Head Unit (HSP/HFP, codec mSBC)**
  - Uses HSP/HFP with the **mSBC** (Modified Subband Codec) codec. This is a newer, “wideband speech” Bluetooth codec designed to improve voice quality.
  - mSBC runs at 16kHz, effectively doubling the audio bandwidth and improving clarity and naturalness for calls compared to CVSD. If both your headset and system support it, mSBC is the best audio option for calls and microphones among the headset profiles

**Summary Table**

| Option                                           | Profile   | Codec       | Typical Use          | Audio Quality              |
| ------------------------------------------------ | --------- | ----------- | -------------------- | -------------------------- |
| Off                                              | —         | —           | —                    | No audio                   |
| Headset Head Unit (HSP/HFP)                      | HSP/HFP   | Unspecified | Calls, mic           | Basic (mono, 8kHz)         |
| High Fidelity Playback (A2DP Sink, codec SBC)    | A2DP Sink | SBC         | Music/media playback | Good (stereo, up to 48kHz) |
| High Fidelity Playback (A2DP Sink, codec SBC-XQ) | A2DP Sink | SBC-XQ      | High-quality music   | Excellent (higher bitrate) |
| Headset Head Unit (HSP/HFP, codec CVSD)          | HSP/HFP   | CVSD        | Calls, mic           | Basic (mono, 8kHz)         |
| Headset Head Unit (HSP/HFP, codec mSBC)          | HSP/HFP   | mSBC        | Calls, mic           | Better (wideband, 16kHz)   |

In short: 
- For **music/media**, choose a “High Fidelity Playback” (A2DP) option—preferably SBC-XQ (if your device supports it) for the best quality.
- For **calls/voice/mic**, “Headset Head Unit (HSP/HFP, codec mSBC)” gives the best voice clarity. If unavailable, fallback to CVSD.
- “Off” disables audio to the device.