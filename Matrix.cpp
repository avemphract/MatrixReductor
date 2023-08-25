#include <type_traits>
#include "MatrixRow.cpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>

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
        MatrixRow<T, C> getCopy(size_t rowIndex) {
            if (rowIndex < R)
                return values[rowIndex];
            else
                throw std::exception("Out of row index");
        }

        void set(MatrixRow<T, C> row,size_t rowIndex) {
            if (rowIndex < R) {
                values[rowIndex] = row;
            }
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
        
        template<rsize_t NR>
		Matrix<T,R,NR> product(Matrix<T,C,NR> product){
			Matrix<T,R,NR> result = Matrix<T, R, NR>();
			for(size_t i = 0; i < R; i++){
				for(size_t j = 0; j < NR; j++){
					for(size_t k = 0; k < C; k++){
						result.get(i).get(j) += this->get(i).get(k) * product.get(k).get(j);
					}
				}
			}
            return result;
		}

        //Gauss Elimination matrix inverse algorithm
		Matrix<T,R,C> inverse(){
            Matrix<T,R,C + C> withUnit = createNewMatrix<R,C + C>();
            for(size_t i = 0 ; i < C; i++){
                for(size_t j = 0; j < C; j++){
                    if(i == j)
                        withUnit.get(i).get(j + C) = 1.0;
                }
            }
            for (int i = 0; i < R; i++) {
                withUnit.get(i).product(1 / withUnit.get(i).get(i));
                for (int j = i + 1; j < R; j++) {
                    withUnit.get(j).add(withUnit.get(i), withUnit.get(j).get(i) * -1.0);
                }
            }
            for (int i = R - 2; i >= 0; i--) {
                for (int j = i; j >= 0; j--) {
                    auto v = withUnit.getCopy(i + 1);
                    auto k = withUnit.get(j).get(i + 1) * -1.0;
                    withUnit.get(j).add(v, k);

                }
            }
            return withUnit.createNewSmallMatrix<R,C>(true,false);
        }
        template<size_t OR, size_t OC>
        Matrix<T, OR, OC> createNewMatrix() {
            Matrix<T, OR, OC> oldMatrix = Matrix<T, OR, OC>();
            for (size_t i = 0; i < std::min(R, OR); i++)
            {
                for (size_t j = 0; j < std::min(R, OR); j++)
                {
                    oldMatrix.get(i).get(j) = this->get(i).get(j);
                }
            }
            return oldMatrix;
        }
        template<size_t NR, size_t NC>
        Matrix<T, NR, NC> createNewSmallMatrix(bool isUp, bool isLeft) {
            Matrix<T, NR, NC> newMatrix = Matrix<T, NR, NC>();
            size_t beginI = isUp ? 0 : (R - NR);
            size_t beginJ = isLeft ? 0 : (C - NC);
            for (size_t i = 0; i < NR; i++)
            {
                for (size_t j = 0; j < NC; j++)
                {
                    newMatrix.get(i).get(j) = this->get(beginI + i).get(beginJ + j);
                }
            }
            return newMatrix;
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