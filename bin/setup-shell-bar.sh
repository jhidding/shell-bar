#!/bin/bash

PS_COLOR=$(bc -l <<< "scale=4 ; ${RANDOM}/32767")
PS1="\[\n\$(shell-bar bar \${PS_COLOR} \$?"

for arg in $@;
do
        case $arg in
                venv)
                        PS1+=" \$(python-venv-bar.sh)"
                        ;;
                git)
                        PS1+=" \$(git-bar.sh)"
        esac
done

PS1+=")\]"
PS1+="$(shell-bar prompt ${PS_COLOR})"

