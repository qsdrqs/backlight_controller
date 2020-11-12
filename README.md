# backlight controller

Use TUI(ncursors) to control intel Graphic Card.

You can change the variable PATH's directory to make it suitable for your own Graphic Card.

## dependency

`ncurses`

Make sure that the user have permission to read and write access to brightness under PATH. You can follow the <a href="https://wiki.archlinux.org/index.php/Backlight#ACPI" >Arch Wiki</a> instrustion to do that.

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

default keybindings of brighter is `<ScrollWheelUp>`(achieved by 'A') and `l`, and darker is `<ScrollWheelDown>`(achieved by 'B') and `h`. You easily change the keybindings through source code.
