#include <type_traits>
#include <vector>
#include <iostream>

#pragma once
template<typename T, size_t C>
class MatrixRow{
public:

    T& get(size_t x) {
		if (C > x)
			return values[x];
		else
			throw std::exception("Out of column index");
	}
	MatrixRow<T, C>() : values{ std::vector<T>(C) } {}
	MatrixRow<T, C>(T* ts): MatrixRow<T,C>() {
		for (int i = 0; i < C; i++) {
			values[i] = ts[i];
		}
	}
	MatrixRow<T, C - 1> reduction(size_t index) {
		MatrixRow<T, C - 1> result = MatrixRow<T, C - 1>();
		bool afterInsert = false;
		for (int i = 0; i < C; i++) {
			if(index == i) {
				afterInsert = true;
				continue;
			}
			result.get(afterInsert ? i - 1 : i) = values[i];
		}
		return result;
	}

	void print(){
		for(T val:values){
			std::cout << val << " ";
		}
	}
private:	
	std::vector<T> values;
};