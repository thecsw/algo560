#ifndef _ARRAY_LIST_LIBRARY
#define _ARRAY_LIST_LIBRARY
#include <cstring>
#include <stddef.h>

template <typename T>
class ArrayList {
private:
        T* _arr;
        int _len;
        int _cap;

        void _expand();
public:
        ArrayList();
        ~ArrayList();
        T* List() const;
        int Len() const;
        bool Exists(T) const;
        void Append(T);
        void ForgetArr();
};

template <typename T>
ArrayList<T>::ArrayList() {
        _len = 0;
        _cap = 5;
        _arr = new T[_cap];
}

template <typename T>
ArrayList<T>::~ArrayList() {
        if (_arr)
                delete[] _arr;
}

template <typename T>
T* ArrayList<T>::List() const {
        return _arr;
}

template <typename T>
int ArrayList<T>::Len() const {
        return _len;
}

template <typename T>
bool ArrayList<T>::Exists(T what) const {
        for (int i = 0; i < _len; i++)
                if (_arr[i] == what)
                        return true;
        return false;
}

template <typename T>
void ArrayList<T>::_expand() {
        T* _old = _arr;
        _cap *= 2;
        _arr = new T[_cap];
        std::memcpy(_arr, _old, sizeof(T)*_len);
        delete[] _old;
}

template <typename T>
void ArrayList<T>::Append(T what) {
        if (_len == _cap)
                _expand();
        _arr[_len++] = what;
}

template <typename T>
void ArrayList<T>::ForgetArr() {
        _arr = nullptr;
}
#endif /* _ARRAY_LIST_LIBRARY */
