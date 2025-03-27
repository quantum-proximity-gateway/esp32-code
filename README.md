# ESP32 Code

<details>
  <summary><strong>Table of Contents</strong></summary>

- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Misc.](#misc)
- [License](#license)

</details>

This code is already setup on the ESP32s, but we have included the instructions below just in case you want to change the code yourself and test things out.

## Requirements

- PlatformIO

## Setup

The very first thing that needs to be done is to connect the ESP32 to the device which has this folder/code.

Next, navigate to the `BLE-Broadcasting/` directory in the terminal.

## Usage

Once the [Setup](#setup) steps have been completed, run the following command:

```bash
pio run --target upload
```

Then, you just need to wait until the *=== [SUCCESS] ===* message shows up. This should usually take approximately 30 seconds to complete.

## Troubleshooting

To see if the ESP32 code was flashed to the device correctly, run the following command:

```bash
pio device monitor
```

The MAC address of the device should be constantly outputted to the screen every couple of seconds. If this is not the case, then you may need to unplug and replug the ESP32 back into the computer, then re-flash the code to it.

To exit this *Serial Monitor*, type *Ctrl* and *C* on the keyboard.

## Misc.

- Instead of using the commands listed above individually, you can run `make run` or `make monitor` to flash to the ESP32 and run the serial monitor.

## License

This project is licensed under the terms of the MIT license. Refer to [LICENSE](LICENSE) for more information.
