a.out:matrix_product.cpp
	g++.exe matrix_product.cpp -o a.exe -fopenmp -std=c++11 -D SIMGLE
	g++.exe matrix_product.cpp -o b.exe -fopenmp -std=c++11 -D PARALLEL
run:
	./a.exe
	./b.exe
	# make clean
clean:
	rm *.out