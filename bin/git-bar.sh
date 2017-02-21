#!/bin/bash

if git rev-parse 2> /dev/null
then
        branch=$(git rev-parse --abbrev-ref HEAD 2> /dev/null) || branch="~"
        repo=$(basename $(git rev-parse --show-toplevel 2> /dev/null))
        git diff-index --quiet HEAD 2> /dev/null && mod="" || mod=":M"
        echo ":${repo}:${branch}${mod}"
        exit 0
else
        exit 1
fi

