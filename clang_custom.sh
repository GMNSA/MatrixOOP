#!/bin/bash

count=$#
do_it=$1

function format() {
    if [ ${count} = 1 ]; then
        if [ ${do_it} = "i" ]; then
            echo "fix"
            for f in $(find ./ -name '*.h' -or -name '*.hpp' -or -name '*.mm' -or -name '*.c' -or -name '*.cpp' -or -name '*.cc'); do
                clang-format -i ${f};
            done
        elif [ ${do_it} = "n" ]; then
            echo "check"
            for f in $(find ./ -name '*.h' -or -name '*.hpp' -or -name '*.mm' -or -name '*.c' -or -name '*.cpp' -or -name '*.cc'); do
                clang-format -n ${f};
            done
        else
            echo "failed"
        fi
    fi
}

format;
