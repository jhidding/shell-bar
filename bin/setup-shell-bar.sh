#!/bin/bash

PS_COLOR=$(bc -l <<< "scale=4 ; ${RANDOM}/32767")
PS1="\[\n\$(shell-bar"

if [ "$1" == "-oldterm" ]
then
        PS1+=" -oldterm"
fi

PS1+=" bar \${PS_COLOR}"

for arg in $@;
do
        case $arg in
                return-value)
                        PS1+=" \$?"
                        ;;
                time)
                        PS1+=" \"\$(date +%X)\""
                        ;;
                venv)
                        PS1+=" \$(python-venv-bar.sh)"
                        ;;
                chez)
                        PS1+=" \$(chez-mate-bar.sh)"
                        ;;
                git)
                        PS1+=" \$(git-bar.sh)"
                        ;;
                *)
                        ;;
        esac
done

PS1+=")\]"

if [ "$1" == "-oldterm" ]
then
        PS1+="$(shell-bar -oldterm prompt ${PS_COLOR})"
else
        PS1+="$(shell-bar prompt ${PS_COLOR})"
fi


