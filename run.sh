echo "which \033[1;32mtarget\033[0m you want to build && run: "
echo "input \033[1;32mAlgo or DS target\033[0m like \033[1;32m\"DS AVLTree\"\033[0m"
echo "\033[1;33m"
ls ./Algo ./DS --hide=*.txt 
echo "\033[1;34m"
read floder target
echo "\033[0m"
cd build && cmake .. && cmake --build ./$floder/$target && cd ..
./bin/$target
