#!/bin/bash

cp materials/linters/.clang-format src/SimpleBashUtils/cat/
clang-format -n -Werror src/SimpleBashUtils/cat/s21_cat.c src/SimpleBashUtils/cat/s21_cat.h &>error.log
if [ -s error.log ]; then
cat error.log
exit 1
else
echo "Ошибков нет"
fi
cp materials/linters/.clang-format src/SimpleBashUtils/grep/
clang-format -n -Werror src/SimpleBashUtils/grep/s21_grep.c src/SimpleBashUtils/grep/s21_grep.h &>error.log
if [ -s error.log ]; then
cat error.log
exit 1
fi