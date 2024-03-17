#include <iostream>
using namespace std;

template <class T>
class myVector {
    T* _arr;
    size_t _size;
    size_t _capacity;

public:
    /*typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef T* pointer;*/

    myVector() {
        _arr = new T[1];
        _capacity = 1;
        _size = 0;
    };

    myVector(int count) {
        _size = count;
        _capacity = count;
        _arr = new T[count];
    };

    ~myVector() {
        delete[] _arr;
    };

    myVector(const myVector& other) {
            _arr = new T[other._capacity];
            for (size_t i = 0; i < other._size; ++i)
                _arr[i] = other._arr[i];
            _size = other._size;
            _capacity = other._capacity;
    };

    myVector(myVector&& other) noexcept {
            _arr = other._arr;
            other._arr = nullptr;
            _size = other._size;
            other._size = 0;
            _capacity = other._capacity;
            other._capacity = 0;
     };

    myVector& operator=(const myVector& other) {
        if (this != &other) {
            delete[] _arr;
            _arr = new T[other._capacity];
            for (size_t i = 0; i < other._size; ++i)
                _arr[i] = other._arr[i];
            _size = other._size;
            _capacity = other._capacity;
        }
    };

    myVector& operator=(myVector&& other) noexcept {
        if (this != &other) {
            delete[] _arr;
             _size = other._size;
            other._size = 0;
            _capacity = other._capacity;
            other._capacity = 0;
            _arr = other._arr;
            other._arr = nullptr;
        }
    };

    T& operator[](int i) {
        return _arr[i];
    }

    T* begin() {
        return _arr;
    }

    T* end() {
        return (_arr + _size);
    }

    size_t size() {
        return _size;
    }

    void pop_back() {
        _size = _size-1;
    }

    void resize(size_t newSize) {
        if (newSize > _size) {
            if (_size >= _capacity) {
                if(newSize > _size*2)
                    _capacity = newSize;
                else
                    _capacity = _size*2;
                T* tmp = _arr;
                _arr = new T[_capacity];
                for (size_t i = 0; i < _size; ++i)
                    _arr[i] = tmp[i];
                delete[] tmp;
            }
            for (int i = _size; i < newSize; i++)
                _arr[i] = T();

        }
        _size = newSize;
    }

    void push_back(const T& x) {
        this->resize(_size+1);
        _arr[_size-1] = x;
    }

};

int main() {

    myVector <int> v(3);
    int i=0;
    for (int &x:v) x=i++; //работает
    for (int x:v) cout<<x<<' ';
    v.pop_back(); //работает

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' '; //работает

    myVector <int> v1;
    for (int i = 0; i < 4; i++) {
        v1.push_back(i);
    }

    for (int x:v1) cout<<x<<' ';
    for (int i = 0; i < v1.size(); i++)
        cout << v1[i] << ' ';

    cout << v1.size();
    v = move(v1);
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' '; //работает



    return 0;
}

//оператор индексации, resize, push_back(), pop_back(), begin(), end()
