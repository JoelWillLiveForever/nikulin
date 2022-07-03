#!/usr/bin/env bash

case "$1" in
    -mkdir)
        # make folder in destination
        
        DEST_DIR="$2"
        echo "Пункт назначения: $DEST_DIR"
        
        if [ -d $DEST_DIR ]
        then
            echo "Ошибка! Директория \"$DEST_DIR\" уже существует!"
            exit 1
        fi

        mkdir $DEST_DIR #create folder/directory
        chmod 777 $DEST_DIR #escalation of access rights
        ;;
    -rm)
        #delete files or directories in destination

        DEST_DIR="${!#}"
        echo "Пункт назначения: $DEST_DIR"

        if [ ! -d $DEST_DIR ]
        then
            echo "Ошибка! Директории назначения \"$DEST_DIR\" не существует!"
            exit 1
        fi
       
        case "$2" in
            -all)
                #delete all files or directories in destination
                echo "$DEST_DIR/*"

                rm -rf $DEST_DIR/*
                rm -rf $DEST_DIR/.*
                rm -rf $DEST_DIR/*.*

                echo "Все файлы и директории удалены в \"$DEST_DIR\""
                ;;
            *)
                while [ ! -z $3 ]
                do
                    rm -f "$DEST_DIR/$2"
                    echo "Файл \"$2\" удалён!"
                    shift
                done
                ;;
        esac

        #rm -f "$2..${@: -2:1}"
        ;;
    *)
        #copy files and create directory if not exists
   
        DEST_DIR="${!#}"
        echo "Пункт назначения: $DEST_DIR"

        if [ ! -d $DEST_DIR ]
        then
            echo "Нет такой директории!"
            mkdir $DEST_DIR
            chmod 777 $DEST_DIR
            echo "Директория создана!"
        fi

        case "$1" in
            -all)
                #copy all files or directories in destination from current current folder
                cp -r `pwd`/* $DEST_DIR/    

                echo "Все файлы и папки из текущей директории успешно скопированы в \"$DEST_DIR\""
                ;;
            *)
                cp "$@"
                ;;
        esac
        ;;
esac
exit 0
