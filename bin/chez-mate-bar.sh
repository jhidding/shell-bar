function chez_mate_info(){
    if [[ -n "$CHEZ_MATE" ]]; then
        # Strip out the path and just leave the env name
        venv="${CHEZ_MATE##*/}"
    else
        # In case you don't have one activated
        venv=''
    fi
    [[ -n "$venv" ]] && echo "👾:$venv"
}

chez_mate_info

