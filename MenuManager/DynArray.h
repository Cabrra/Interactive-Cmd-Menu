#pragma once

template<typename Type>
class DynArray
{

private:
	unsigned int _capacity;
protected:

	unsigned int _size;
	Type* element;

public:

	DynArray();
	~DynArray();
	DynArray(const DynArray<Type>& that);
	DynArray<Type>& operator=(const DynArray<Type>& that);
	Type& operator[](const unsigned int index);
	const Type& operator[](const unsigned int index) const;
	unsigned int size() const;
	unsigned int capacity() const;
	void clear();
	void append(const Type& item);
	void reserve(const unsigned int & newCap = 0);

	//CHALLENGE
	void insert(const Type val, const unsigned int index);
	void insert(const Type * val, const unsigned int n, const unsigned int index);
	void remove(const unsigned int index);
	void remove(const unsigned int index, const unsigned int n);

};

template<typename Type>
DynArray<Type>::DynArray(){
	_size = 0;
	_capacity = 0;
	element = NULL;
}

template<typename Type>
DynArray<Type>::~DynArray(){
	delete[] element;
}

template<typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& that){

	_size = that._size;
	_capacity = that._capacity;
	element = NULL;
	element = new Type[_capacity];
	for (unsigned int i = 0; i < _size; i++)
		element[i] = that.element[i];
}

template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that){
	if (this != &that)
	{
		_size = that._size;
		_capacity = that._capacity;
		delete[] element;
		element = new Type[_capacity];
		for (unsigned int i = 0; i < _size; i++)
			element[i] = that.element[i];
	}
	return *this;
}

template<typename Type>
Type& DynArray<Type>::operator[](const unsigned int index){
	return element[index];
}

template<typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const{
	return element[index];
}

template<typename Type>
unsigned int DynArray<Type>::size() const{
	return _size;
}

template<typename Type>
unsigned int DynArray<Type>::capacity() const{
	return _capacity;
}

template<typename Type>
void DynArray<Type>::clear(){
	if (element != NULL)
		delete[] element;
	element = NULL;
	_size = 0;
	_capacity = 0;
}

template<typename Type>
void DynArray<Type>::append(const Type& item){

	if (_capacity == 0){
		element = new Type[1];
		element[0] = item;
		_capacity++;
	}
	else if (_size == _capacity){
		Type *temp = new Type[_capacity * 2];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = element[i];
		temp[_size] = item;
		_capacity *= 2;
		delete[] element;
		element = temp;
	}
	else
		element[_size] = item;
	_size++;
}

template<typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap = 0){
	if (newCap == 0){
		if (_capacity == 0){
			element = new Type[1];
			_capacity = 1;
		}
		else{
			Type* temp = new Type[_capacity * 2];
			for (unsigned int i = 0; i < _size; i++)
				temp[i] = element[i];
			delete[] element;
			_capacity = _capacity * 2;
			element = temp;

		}
	}
	if (!(newCap <= _capacity)){
		Type* temp = new Type[newCap];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = element[i];
		delete[] element;
		_capacity = newCap;
		element = temp;
	}

}

template<typename Type>
void DynArray<Type>::insert(const Type val, const unsigned int index){
	if (index >= 0 && index <= _capacity){ // index control

		if (_capacity == 0){
			_capacity++;
			_size++;
			element = new Type[1];
			element[0] = val;
		}
		else{
			if (_size + 1 > _capacity){
				Type* temp = new Type[_capacity * 2];
				for (unsigned int i = 0; i < _size; i++)
					temp[i] = element[i];
				delete[] element;
				_capacity = _capacity * 2;
				element = temp;
			}

			for (unsigned int i = _size; i > index; i--)
				element[i] = element[i - 1];

			element[index] = val;
			_size++;
		}
	}
}

template<typename Type>
void DynArray<Type>::insert(const Type * val, const unsigned int n, const unsigned int index){
	if (index >= 0 && index <= _capacity){ // index control
		if (_capacity == 0){
			_capacity += n;
			delete[] element;
			element = new Type[n];
			for (unsigned int i = 0; i < n; i++)
				element[i] = val[i];
		}
		else{
			
			if (_size + n > _capacity){
				Type* temp = new Type[_capacity * 2];
				for (unsigned int i = 0; i < _size; i++)
					temp[i] = element[i];
				delete[] element;
				_capacity = _capacity * 2;
				element = temp;


			}
			for (unsigned int i = _size + n; i > index; i--){
				element[i] = element[i - n];
			}
			int count = 0;
			for (unsigned int i = index; i <= index + n - 1; i++){
				element[i] = val[count];
				count++;
			}
			_size += n;
		}
	}
}

template<typename Type>
void DynArray<Type>::remove(const unsigned int index){
	if (index >= 0 && index < _size){ // index control
		for (unsigned int i = index+1; i < _size; i++)
			element[i-1] = element[i];
		_size--;
	}
}

template<typename Type>
void DynArray<Type>::remove(const unsigned int index, const unsigned int n){
	if (index >= 0 && index < _size){ // index control
		if (index + n <= _size){ // limit control
			for (unsigned int i = index; i < _size-n; i++)
				element[i] = element[i + n];

			_size -= n;
		}
	}
}