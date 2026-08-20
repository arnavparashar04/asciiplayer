# asciiplayer

A terminal video player that renders videos as colored ASCII characters.

This player uses FFmpeg to decode video frames and converts them to characters with 24 bit rgb colours before rendering. Each small region of the frame is represented by a character. The average RGB value of the region determines its terminal color, while its luminance determines which character is chosen from the character ramp. The resulting frame is written directly to the terminal using ANSI truecolor escape sequences.

## Features

- ASCII based video rendering
- RGB truecolor support
- FFmpeg based decoding
- Frame timing using average fps

## Requirements

C23 compiler, CMake and FFmpeg development libraries.

On Arch Linux:

```bash
sudo pacman -S cmake pkgconf ffmpeg
```

## Building

```bash
cmake -S . -B build
cmake --build build
```

The executable will be located at:

```text
build/asciiplayer
```

To install it globally

```bash
cmake --install build
```

Make sure `~/.local/bin` is in your `PATH`.

## Usage

```bash
asciiplayer video.mp4
```

## Character Ramp

The current character ramp is:

```text
 .,:;irsXA253hMHGS#9B&@
```

## Terminal

The recommended terminal is Kitty.

Terminal performance can have a significant effect on playback, especially at higher resolutions. Kitty currently performs  well with this player, alacritty/konsole etc. struggle to play the video without flickering.

Note: Input video files higher than 720p resolution may cause fluttering even in kitty. To fix this you may change character cell height and width in renderer.c, in future versions this will be made available using cli flags.

## Project Status

This is an early version(v1.0.0) of the player. The core pipeline is working, improvements in rendering/displaying logic, new features like audio support and dirty updating, better memory managment, error handling etc will be worked on in future versions
