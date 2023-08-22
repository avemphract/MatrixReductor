#include "Matrix.cpp"
#include <iostream>

int main(int sizeOfArgs, char** args){
    int values1[] = {
        1, 2, 3, 4, 
        5, 6, 7, 8, 
        9, 1, 2, 3, 
    };
    Matrix<int, 3, 4> unitM2 = Matrix<int, 3, 4>(values1);


    int values2[] = {
        1, 2, 0, 
        1, 0, 3, 
        1, 7, 0, 
        1, 0, 9
    };
    Matrix<int, 4, 3> unitM3 = Matrix<int, 4, 3>(values2);

    Matrix<int, 3, 3> pr = unitM2.product(unitM3);

    unitM2.print();
    std::cout << std::endl << "*" << std::endl << std::endl;
    unitM3.print();
    std::cout << std::endl << "=" << std::endl << std::endl;
    pr.print();
    std::cout << std::endl << "--- --- Example2 --- --- " << std::endl << std::endl;



    int values3[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 1, 2, 3,
        1, 7, 9, 10
    };
    Matrix<int, 4, 4> m3 = Matrix<int, 4, 4>(values3);

    int values4[] = {
        1,  2,
        3,  4,
        5,  6,
        7,  8,
        9,  0
    };
    Matrix<int, 2, 5> m4 = Matrix<int, 2, 5>(values4);

    m3.print();
    std::cout << std::endl << "Reduction column index 3" << std::endl << std::endl;
    auto m3_2 = m3.reductionColumn(3);
    m3_2.print();
    std::cout << std::endl << "Reduction column index 1" << std::endl << std::endl;
    auto m3_3 = m3_2.reductionColumn(1);
    m3_3.print();
    std::cout << std::endl << "product with" << std::endl << std::endl;
    m4.print();
    auto m5 = m3_3.product(m4);
    std::cout << std::endl << "=" << std::endl << std::endl;
    m5.print();


}