#include "Matrix.cpp"
#include <iostream>
#include <vector>

int main(int sizeOfArgs, char** args){
    
    double values1[] = {
        1, 2, 3, 4, 
        5, 6, 7, 8, 
        9, 1, 2, 3, 
        11,1, 8, 17
    };
    Matrix<double, 4, 4> aMatrice = Matrix<double, 4, 4>(values1);
    std::cout << "A matrisi" << std::endl;
    aMatrice.print();

    double values2[] = {
        1,
        8,
        7,
        -9,
    };
    Matrix<double, 4, 1> bMatrice = Matrix<double, 4, 1>(values2);
    std::cout << std::endl << std::endl << "B matrisi" << std::endl;
    bMatrice.print();
    std::cout << std::endl << std::endl << "A^-1 * B matrisi ile x vectorü bulunur" << std::endl;

    aMatrice.inverse().product(bMatrice).print();
    //if we now x_2(index of vector) so

    std::cout << std::endl << "x matrisinde 2'ye 4 dersek ve bunu diðer elementlere daðýtýrsak matrislerin yeni hali" << std::endl;
    double x_2 = 6.25;
    auto temp = aMatrice.reductionRow(2);
    auto newB = bMatrice.reductionRow(2);
    for (int i = 0; i < 3; i++) {
        newB.get(i).set(0, newB.get(i).get(0) - temp.getValue(2,i) * x_2);
    }
    auto newA = temp.reductionColumn(2);
    std::cout << std::endl << "A matrisinin yeni hali" << std::endl;
    newA.print();
    std::cout << std::endl << "B matrisinin yeni hali" << std::endl;
    newB.print();
    std::cout << std::endl << std::endl << "A^-1 * B matrisi ile x vectorü bulunur" << std::endl;
    newA.inverse().product(newB).print();

    std::cout << std::endl << std::endl << "Her iki matris de ayný olduðuna göre yaptýðýmýz iþlem dogrudur.";



}