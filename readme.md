# DLL Whitelist

This proof of concept showcases how you can construct a list of allowed DLLs and repeatedly unload any other DLL not on the list. Please keep in mind that this does not 100% prevent other DLLs from loading or operating, but forces them to load again after being constantly unloaded.

## Files

inc/dllWhitelist.cpp includes functions for checking the loaded module list and unloading any dll that is not on the whitelist.

inc/Sleep.h is a small, custom sleep function. It's expected that devs may customize this further.

main.cpp contains the POC (run, trigger a DLL whitelist thread, sleep for 5 seconds, end)

## Use Cases

Personal, educational, research, "whitehat", legal use cases only.

To test effectiveness of your other programs' ability to analyze or monitor a program that unloads dlls.

To test security and runtime performance with a whitelisted dll list.

## Notes

Certain software does not handle unexpected unload events.

Certain software functionality does not work 100% with frequent unload events.

## Compiling Example

```
g++ main.cpp -static -o main.exe
```
