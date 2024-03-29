function virtualenv_info(){
    # Get Virtual Env
    if [[ -n "$VIRTUAL_ENV" ]]; then
        # Strip out the path and just leave the env name
        venv="${VIRTUAL_ENV##*/}"
        if [[ "$venv" =~ ([^-]+)-[^-]+-py([0-9\.]+) ]]; then
                venv="${BASH_REMATCH[1]}-${BASH_REMATCH[2]}"
        fi
    elif [[ -n "$CONDA_DEFAULT_ENV" ]]; then
	# For conda environments
        venv="${CONDA_DEFAULT_ENV##*/}"
    else
        # In case you don't have one activated
        venv=''
    fi
    [[ -n "$venv" ]] && echo "🐍:$venv"
}

virtualenv_info

