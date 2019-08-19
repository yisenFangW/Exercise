#!/bin/bash

if ping bbbbbbbaidu.com -W 1 -i 1 -c 10  >/dev/null 2>&1; then
    echo "success"
else
    echo "fail"
fi

