Shell-bar
=========

Shell-bar is a small program that draws a pretty bar in your shell prompt.
Currently this has only been tested with Bash. The bar gets a random colour for
each terminal window.

![screenshot](screenshot.png)

Build
-----

Shell-bar compiles with GCC 5 and 6. Just type `make`.

Install
-------

Copy the files in `./bin` to `~/.local/bin`, or better yet, use
[`xstow`](http://xstow.sourceforge.net) to get a similar effect. Make sure
`~/.local/bin` is in your `$PATH`. To see an example of how to enable
`shell-bar` in your `.bashrc`, see below.

Additional info scripts
-----------------------

This distribution currently has two extra scripts:

- git
- Python VirtualEnv

And a helper script to setup the shell-bar with the desired plugins. If you
create additions of your own, share, pull-request!

Example section in `.bashrc`
----------------------------

        case "$TERM" in
        xterm*|x-term*)
                export VIRTUAL_ENV_DISABLE_PROMPT=1
                source setup-shell-bar.sh venv git
                ;;
        *)
                PS1="[\[\e[1m\]\#\[\e[m\]]-[\[\e[32m\]\u@\h\[\e[m\]]"
                PS1+="-[\[\e[1;34m\]\w\[\e[m\]$ "
                ;;
        esac
