#!/usr/bin/env bash

user=$1
if [ -z $user ]
then
    echo "Ошибка! Пустой аргумент!"
    exit 1
else
    if grep $user /etc/passwd
    then
        echo "Пользователь $user существует!"
    else    
        echo "Пользователь $user не существует!"
    fi
fi
exit 0
