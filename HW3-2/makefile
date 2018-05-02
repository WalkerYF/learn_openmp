a.out:t1.cpp
	g++.exe t1.cpp -o a.out -fopenmp -std=c++11
	g++.exe t1.cpp -o b.out -std=c++11
	echo "with openmp: "`./a.out`
	echo "without openmp: "`./b.out`
	# make clean

clean:
	rm *.out