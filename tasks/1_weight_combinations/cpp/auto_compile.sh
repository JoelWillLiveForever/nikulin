#!/usr/bin/env bash
DETAIL="-detail"

case $1 in
    --help)
        echo "Usage: [OPTION] [FILES_LIST_TO_COMPILE: FILE_1 FILE_2 ... FILE_N]"
        echo "Supported file types: .c; .cpp;"
        echo "Options:"
        echo "    --help: Get script description;"
        echo "    -clear: Remove all compilation files;"
        echo "    $DETAIL: Compilation of all stages of compilation."
        ;;
    -clear)
        rm -f $(pwd)/*.i
        rm -f $(pwd)/*.ii
        rm -f $(pwd)/*.s
        rm -f $(pwd)/*.o
        rm -f $(pwd)/a.out
        find . -type f  ! -name "*.?*" -delete
        ;;
    $DETAIL|*)
        for SOURCE_FILE in "$@"
        do
            if [[ $SOURCE_FILE == $DETAIL ]]
            then
                continue
            elif [[ $SOURCE_FILE == *.c ]]
            then
                echo "Compile $SOURCE_FILE!"
        
                FILE_NAME=$(basename -- "$SOURCE_FILE")
                FILE_EXTENSION="${FILE_NAME##*.}"
                FILE_NAME="${FILE_NAME%.*}_$FILE_EXTENSION"
                
                if [[ $1 == $DETAIL ]]
                then
                    gcc -E $SOURCE_FILE -o $FILE_NAME.i
                    gcc -S $FILE_NAME.i -o $FILE_NAME.s
                    as $FILE_NAME.s -o $FILE_NAME.o
                    gcc $FILE_NAME.o -o $FILE_NAME
                else
                    gcc $SOURCE_FILE -o $FILE_NAME
                fi
            elif [[ $SOURCE_FILE == *.cpp ]]
            then
                echo "Compile $SOURCE_FILE!"

                FILE_NAME=$(basename -- "$SOURCE_FILE")
                FILE_EXTENSION="${FILE_NAME##*.}"
                FILE_NAME="${FILE_NAME%.*}_$FILE_EXTENSION"
                
                if [[ $1 == $DETAIL ]]
                then
                    g++ -E $SOURCE_FILE -o $FILE_NAME.ii
                    g++ -S $FILE_NAME.ii -o $FILE_NAME.s
                    as $FILE_NAME.s -o $FILE_NAME.o
                    g++ $FILE_NAME.o -o $FILE_NAME
                else
                    g++ $SOURCE_FILE -o $FILE_NAME
                fi
            else
                echo "Error! $SOURCE_FILE is unsupported file type!"
                exit 1
            fi
        done
    ;;
esac
exit 0
