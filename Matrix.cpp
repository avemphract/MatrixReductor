#include <type_traits>
#include "MatrixRow.cpp"
#include <vector>
#include <iostream>
#include <iterator>

#pragma once
template<typename T, size_t R, size_t C>
class Matrix{

    public:
        Matrix<T, R, C>() :values{std::vector<MatrixRow<T,C>>(R)} {

        }
        Matrix<T, R, C>(T* values): Matrix<T,R,C>() {
            for (int i = 0; i < R; i++) {
                this->get(i) = (MatrixRow<T,C>(values + i * C));
            }
        }
        
		MatrixRow<T, C>& get(size_t rowIndex) {
            if (rowIndex < R)
                return values[rowIndex];
            else
                throw std::exception("Out of row index");

        }
        T getValue(size_t x, size_t y) {
            if (y < R)
                return this->values[y].get(x);
            else
                throw std::exception("Out of row index");
        }
        Matrix<T, R, C - 1> reductionColumn(size_t columnIndex) {
            Matrix<T, R, C - 1> result = Matrix<T, R, C - 1>();
            for (int i = 0; i < R; i++) {
                result.get(i) = this->get(i).reduction(columnIndex);
            }
            return result;
        }
        Matrix<T, R - 1, C> reductionRow(size_t rowIndex) {
            Matrix<T, R - 1, C> result = Matrix<T, R - 1, C>();
            bool afterInsert = false;
            for (int i = 0; i < R; i++) {
                if (rowIndex == i) {
                    afterInsert = true;
                    continue;
                }
                for (int j = 0; j < C; j++) {
                    result.get(afterInsert ? i - 1 : i).get(j) = this->get(i).get(j);
                }
            }
            return result;
        }
        template<size_t NR>
		Matrix<T,R,NR> product(Matrix<T,C,NR> product){
			Matrix<T,R,NR> result;
			for(size_t i = 0; i < R; i++){
				for(size_t j = 0; j < NR; j++){
					for(size_t k = 0; k < C; k++){
						result.get(i).get(j) += this->get(i).get(k) * product.get(k).get(j);
					}
				}
			}
            return result;
		}
		void print() {
            for (MatrixRow<T, C> matrixRow: values){
                matrixRow.print();
                std::cout << std::endl;
            }
        }
    private:
        std::vector<MatrixRow<T,C>> values;
};