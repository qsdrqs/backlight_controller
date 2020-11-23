# backlight controller

Use TUI(based on ncurses) to control intel Graphic Card in linux (tested through ArchLinux)

**You need to change the variable PATH's directory to make it suitable for your own Graphic Card.**

## dependency

`ncurses`

***Make sure that the user have permission of reading and writing access to brightness under PATH otherwise you will get a `segmentation fault (core dumped)`.*** You can follow the <a href="https://wiki.archlinux.org/index.php/Backlight#ACPI" >Arch Wiki</a> instruction to do that. You can also use `sudo` to run it.(NOT RECOMMENDED)

## build & run

run

```bash
make
```

to build

run

```bash
./backlight
```

to start. You can also add the symbol link into `$PATH`.

## keybindings

default keybindings of brighter is `<ScrollWheelUp>`(achieved by 'A') and `k`, and darker is `<ScrollWheelDown>`(achieved by 'B') and `j`. You easily change the keybindings through source code.
