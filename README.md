# AVPatcher
A simple demonstration to apply c# patches to AV1 via [Harmony](https://harmony.pardeike.net/)

## Requirements
- [Python](https://www.python.org/downloads/) 
- [Frida](https://frida.re/)  via pip
### For Dev
- [VS 2022](https://visualstudio.microsoft.com/de/downloads/) with .NET Framework 4.8, C++, Python
- [VS 2019]() with .NET Framework 4.0

## Build
- Open the project in VS 2022
- Build the whole project in x86

## Usage
- Locate your own compiled files inside the project folder or the prebuilt ones in the bin folder
- Put the AV1Patcher.py, Bootloader.dll, Patcher.dll, agent.js, steam_appid.txt files into the AV1 game folder
- Start your AV1
- Execute the python file 

## Info
To debug you can read the debug file *"harmony.log"* on your desktop