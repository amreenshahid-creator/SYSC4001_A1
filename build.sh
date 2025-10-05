if [ ! -d "bin" ]; then
    mkdir bin
else
	rm bin/*
fi
g++ -std=c++17 interrupts.cpp -o bin/interrupts
