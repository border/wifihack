unset HISTORY HISTFILE HISTSAVE HISTZONE HISTORY HISTLOG
export HISTFILE=/dev/null
export HISTSIZE=0
export HISTFILESIZE=0

# ssh -o UserKnownHostsFile=/dev/null -T user@host /bin/bash -i
# stdin not terminal
# python -c 'import pty; pty.spawn("/bin/sh")'
