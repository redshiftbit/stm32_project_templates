# STM32 Project templates

This repository include my set of templates for several STM32 mcu. Templates are used as a basis for creating and working on projects in the "VS Code" environment. Tested on "Ubuntu 20.04" and "Ubuntu 24.04".

## Key features of the templates

*-* a script is used to build the project. In addition to building and flashing the microcontroller, it also checks for changes to the compiled firmware and prevents flashing the controller if the firmware file hasn't changed since the initial build;  
*-* debugging support;  
*-* "OpenOCD" is used to flash the microcontroller. It supports two operating modes:

- programming via the SWD interface with a software reset;
- programming via the SWD interface with a hardware reset (using the NRST pin on the "ST-Link" programmer).

> [!NOTE]  
> By default, the program attempts to use a software reset, and if that doesn't work, it switches to a hardware reset.

## Notices about software installation

Install "VS Code" manual or by command:

```bash
wget -O vscode.deb "https://go.microsoft.com/fwlink/?LinkID=760868" && sudo apt install ./vscode.deb && rm vscode.deb
```

Install toolchain and utilities for compilation:

```bash
sudo apt-get install gcc-arm-none-eabi libusb-1.0 libtool-bin libjim-dev make libtool pkg-config autoconf automake texinfo libjim-dev -y
```

Download "OpenOCD" repository, build and install it:

```bash
git clone https://github.com/openocd-org/openocd && cd openocd && sudo chmod ugo+rwx bootstrap && ./bootstrap && ./configure --enable-stlink && make && sudo make install && cd .. && sudo rm -r openocd
```

Install "GNU Debugger" and create link to it:

```bash
sudo apt-get update && sudo apt-get -y install gdb-multiarch && sudo ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb
```

Install extensions "Cortex-Debug" from author "marus25" and "С/С++" from "Microsoft" for VS Code:

```bash
code --install-extension marus25.cortex-debug mcu-debug.debug-tracker-vscode mcu-debug.memory-view mcu-debug.peripheral-viewer mcu-debug.rtos-views && code --install-extension ms-vscode.cpptools
```

Install drivers for ST-link:

```bash
sudo apt -y install stlink-tools
```

From folder "st-link-udev-rules" copy files to directory "/etc/udev/rules.d/", apply them and delete source:

```bash
sudo cp st-link-udev-rules/* /etc/udev/rules.d/ && sudo systemctl reload udev && sudo udevadm trigger && rm -r st-link-udev-rules
```

Setup "VS Code" hotkeys for compilation, firmware mcu and debug commands:
In "VS Code" interface open "Command Palette" by hotkey combination Ctrl+Shift+P and enter "keybindings.json". The file will open and enter the following lines into it:

```json
[
    {
        "key": "f8",
        "command": "workbench.action.tasks.runTask",
        "args": "Download"
    },
    {
        "key": "f6",
        "command": "workbench.action.tasks.runTask",
        "args": "Build"
    }
]
```

or by terminal command:

```bash
cat <<EOF >> $HOME/.config/Code/User/keybindings.json

[
    {
        "key": "f8",
        "command": "workbench.action.tasks.runTask",
        "args": "Download"
    },
    {
        "key": "f6",
        "command": "workbench.action.tasks.runTask",
        "args": "Build"
    }
]
EOF
```

Save and close.

Now everything is installed and should work.

## Usage

  1. copy template with necessary mcu to your project folder;
  2. rename template and *.code-workspace file to project name;
  3. add library sources and headers to "Code/src" and "Code/inc" folders;
  4. add library sources to "Makefile" to "C_SOURCES" variable.

> [!WARNING]  
> After copying the template, you may need to make the "build_and_firmware_script" build script executable. Do it by command (from main project directory):
>
> ```bash
> chmod ugo+x ./interface/build_and_firmware_script
> ```
