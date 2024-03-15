#include <iostream>
using namespace std;



double function1(double x) {
    return x*x;
}
double function2(double x) {
    return x;
}

//intersect function that takes two functions and returns the x y coordinates of the intersection with input values ranging from 0 to 1
#include <fstream>

void intersect(double (*f1)(double), double (*f2)(double)) {
    std::ofstream file;
    file.open("intersect.out");
    file << "x,y1,y2\n";  // Write the header

    for (double x = 0; x <= 1; x += 0.1) {
        double y1 = f1(x);
        double y2 = f2(x);
        file << x << "," << y1 << "," << y2 << "\n";  // Write the data

        if (y1 == y2) {
            cout << "Intersection at x = " << x << " y = " << y1 << endl;
        }
    }

    file.close();
}

int main() {
    intersect(function1, function2);
    return 0;
}
