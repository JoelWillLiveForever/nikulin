#!/usr/bin/env bash

# Make directory:
# ./make_dir_copy_and_delete_files -mkdir /path/to/destination_dir

# Copy options:
# ./make_dir_copy_and_delete_files file_path_to_copy.file ... /path_to_copy_dir ... /path_to_destination_dir
# ./make_dir_copy_and_delete_files -all /path_to_dir_copy_all_content

# Removal options:
# ./make_dir_copy_and_delete_files -rm file_to_delete.file ... /path_to_dir_to_delete ... /path_to_dir_where_delete
# ./make_dir_copy_and_delete_files -rm -all /path_to_dir_delete_all_content

case "$1" in
    --help)
        echo -e '\tMake directory:'
        echo -e '\t    -mkdir /path/to/destination_dir'
        echo -e '\n\tCopy options:'
        echo -e '\t    file_path_to_copy.file ... /path_to_copy_dir ... /path_to_destination_dir'
        echo -e '\t    -all /path_to_dir_copy_all_content'
        echo -e '\n\tRemoval options:'
        echo -e '\t    -rm file_to_delete.file ... /path_to_dir_to_delete ... /path_to_dir_where_delete'
        echo -e '\t    -rm -all /path_to_dir_delete_all_content'
        ;;
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
        chmod 755 $DEST_DIR #escalation of access rights
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
            chmod 755 $DEST_DIR
            echo "Директория создана!"
        fi

        case "$1" in
            -all)
                #copy all files or directories in destination from current current folder
                cp -r `pwd`/* $DEST_DIR/    

                echo "Все файлы и папки из текущей директории успешно скопированы в \"$DEST_DIR\""
                ;;
            *)
                cp -r "$@"

                echo "Успешное копирование в \"$DEST_DIR\""
                ;;
        esac
        ;;
esac
exit 0
