<img src="https://github.com/GeorgiaCharalampous/SpiceMate/blob/main/Branding/Logos/Cropped%20Logo.png" alt="drawing" width="1500"/>

# 🌶Introducing the SpiceMate

A contactless spice dispenser device utilising a Flight of Time proximity sensor VL6180X, an ERM vibrational motor driven by a DRV2605/L driver and a SG90 Micro Servo als operated through a Raspberry Pi 3B.
During operation dispensing is triggered when an object is introduced to the region monitored by the sensor. Motor activation/deactivation occurs in response to retained presence of the object within the sensor field.

# Table of Contents
1. [Project Aims](#aims)
2. [Live Demo](#demo)
3. [Prerequisites](#pre)
4. [Media Engagement](#media)

# Project Aims <a name="aims" />
- Increase efficiency & hygiene through contactless control
- Greater accessibility & independance in the kitchen for people with limited dexterity
- Spice wastage minimisation through real-time response to events

# Live Demo <a name="demo" />

# Prerequisites <a name="pre" />
## Libraries
```
apt-get install cmake
apt-get install libgpiod-dev
```
## Components
* Raspberry PI 3B
* VL6180X - Time-of-Flight (ToF) proximity sensor and ambient light sensing (ALS) module
* DRV2605 - Haptic driver for ERM/LRA with 2-V operation, waveform library & auto-resonance tracking
* ERM Mini Coin Vibration Motor
* Servo Six board or equivalent for servo control
* 9g SG90 Micro Servo

# Build
To build project use following commands in command line:
```
cmake ..
make
```
# Install
```
sudo make install
```
# Run example
Run this example code in command line to 
```
// In appropriate
mkdir Build
cd Build
// Build CMake as explained earlier
cmake ..
make
//Run executable
./TestDriver
```
# Documentation
For easy to read documentation of the classes used for this device you can access our online document -> 
# Media Engagement <a name="media" />
## Social Media Channels: <a name="channels" />
* [Instagram](https://www.instagram.com/spicemate.pi/)
* [Facebook](https://www.facebook.com/profile.php?id=61555942478445)
* [TikTok](https://www.tiktok.com/@spicemate.dispenser?is_from_webapp=1&sender_device=pc)

## Articles: <a name="publications" />
Published an [Article](https://www.rs-online.com/designspark/spicemate-an-automated-contact-less-spice-dispenser) detailing our project on RS components' public forum **DesignSparks**. DesignSparks is an online forum and community where both professionals, students and tinkerers can read, listen and learn about the latest technologies and products relating to CAD, 3D printing, electronics. 

# Analytics: <a name="analytics" />
* Combined accounts reached across all platforms: **~2K organic interactions**
* Total number of followers across all platforms: **57**
* Combined views on videos across all platforms: **~10K views**

