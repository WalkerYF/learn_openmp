#include <iostream>
#include <omp.h>
using namespace std;

void func(int t) {
#pragma omp parallel
  {
    cout << "!!in thread:" << t  << "  thread " << omp_get_thread_num() << " in function func()" << endl;
  }
}

int main() {
// omp_set_nested(1);
  cout << "Main thread" << endl;
#pragma omp parallel
  {
    cout << "               thread " << omp_get_thread_num() << " in function main()" << endl;
    func(omp_get_thread_num());
  }
} // end of main