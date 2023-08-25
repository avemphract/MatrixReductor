#include <type_traits>
#include <vector>
#include <iostream>

#pragma once
template<typename T, size_t C>
class MatrixRow{
public:

	MatrixRow<T, C - 1> reduction(size_t index) {
		MatrixRow<T, C - 1> result = MatrixRow<T, C - 1>();
		bool afterInsert = false;
		for (int i = 0; i < C; i++) {
			if (index == i) {
				afterInsert = true;
				continue;
			}
			result.get(afterInsert ? i - 1 : i) = values[i];
		}
		return result;
	}

    T& get(size_t x) {
		if (C > x)
			return values[x];
		else
			throw std::exception("Out of column index");
	}
	T getCopy(size_t x) {
		if (C > x)
			return values[x];
		else
			throw std::exception("Out of column index");
	}
	void set(size_t x, T value) {
		if (C > x)
			values[x] = value;
		else
			throw std::exception("Out of column index");
	}
	
	void product(T value) {
		for (size_t i = 0; i < C; i++)
		{
			this->values[i] = this->values[i] * value;
		}
	}
	
	MatrixRow<T,C> productGet(T value) {
		std::vector<T> temp = values;
		for (size_t i = 0; i < C; i++)
		{
			temp[i] *= value;
		}
		return MatrixRow<T, C>(temp);
	}
	void add(MatrixRow<T, C> added, T multiplier) {
		for (size_t i = 0; i < C; i++)
		{
			this->values[i] += added.getCopy(i) * multiplier;
		}
	}
	MatrixRow<T, C>() : values{ std::vector<T>(C) } {}
	MatrixRow<T, C>(T* ts) : MatrixRow<T, C>() {
		for (int i = 0; i < C; i++) {
			values[i] = ts[i];
		}
	}
	MatrixRow<T, C>(std::vector<T> values) : values{ values }
	void add(MatrixRow<T, C> added) {
		add(added, 1);
	}


	void print(){
		for(T val:values){
			std::cout << val << " ";
		}
	}
private:	
	std::vector<T> values;
};