function foam_info(){
    if [[ -n "$FOAM_API" ]]; then
        echo "🧽:${FOAM_API}"
    fi
}

foam_info

