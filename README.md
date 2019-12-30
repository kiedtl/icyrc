# icyrc
> no bs irc client

![scrot](https://x.icyphox.sh/8K0.png)

Built on top of https://c9x.me/irc/.

## Installing

Requires `ncurses` development files.
Clone this repo and:

```
$ make
# make install
```

Similarly, to uninstall:

```
# make uninstall
```

## Usage

```
usage: irc [-n NICK] [-u USER] [-s SERVER] [-p PORT] [-l LOGFILE ] [-t] [-h]
```

A password can be specified via an `IRCPASS` environment variable.

### Commands

- `/j #channel` -- Join channel
- `/l #channel` -- Leave channel
- `/q user msg` -- Send private message
- `/r something` -- Send raw command
- `/x` -- Quit
