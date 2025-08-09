#!/bin/bash
cd src/SimpleBashUtils/cat/
make test 2>error.log
if [ -s error.log ]; then
cat error.log
exit 1
else
echo "Тесты утилиты cat завершены успешно"
fi
# cd ../grep/
# make test 2>error.log
# if [ -s error.log ]; then
# cat error.log
# exit 1
# else
# echo "Тесты утилиты grep завершены успешно"
# fi
