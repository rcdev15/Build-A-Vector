

#ifndef VECTOR_H
#define VECTOR_H


#include <memory>
#include <stdexcept>
#include <iterator>



template <typename T>
class Vector {
public:
    typedef int size_type;

    class iterator {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef std::unique_ptr<T[]> u_pointer;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(u_pointer ptr) : ptr_(ptr.get()) {}
        
        ~iterator() { delete ptr_; }
        
        self_type operator ++() { self_type i = *this; ptr_++; return i; }
        
        self_type operator ++(int junk) { ptr_++; return *this; }
        
        reference operator *() { return *ptr_; }
        
        pointer operator ->() { return ptr_; }
        
        bool operator ==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        
        bool operator !=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

    private:
        pointer ptr_;
    };

    class const_iterator {
    public:
        typedef const_iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef std::unique_ptr<T[]> u_pointer;
        typedef T* pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;

        const_iterator(u_pointer ptr) : ptr_(ptr.get()) {}
        
        ~const_iterator() { delete ptr_; }
        
        self_type operator ++() { self_type i = *this; ptr_++; return i; }
        
        self_type operator ++(int junk) { ptr_++; return *this; }
        
        reference operator *() { return *ptr_; }
        
        const pointer operator ->() { return ptr_; }
        
        bool operator ==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        
        bool operator !=(const self_type& rhs) { return ptr_ != rhs.ptr_; }

    private:
        pointer ptr_;
    };

    Vector(size_type capacity = 0) : mSize(0), mCapacity(capacity) {
        if (mCapacity == 0) {
            arr = std::make_unique<T[]>(mCapacity + 1);
        } else {
            arr = std::make_unique<T[]>(mCapacity);
        }
    }

    Vector(const Vector<T> &giver) {
        mCapacity = giver.mCapacity;
        mSize = giver.mSize;
        arr = std::make_unique<T[]>(mCapacity);
        for (unsigned int i = 0; i < mSize; i++) {
            arr[i] = giver.arr[i];
        }
    }

    Vector(Vector<T> &&rValue) {
        mCapacity = rValue.mCapacity;
        mSize = rValue.mSize;
        arr.reset(new T[mCapacity]);
        arr = std::move(rValue.arr);
    }

    Vector& operator =(const Vector<T> &rhs) {
        if (this != &rhs) {
            if (mSize != rhs.mSize || mCapacity != rhs.mCapacity) {
                mCapacity = rhs.mCapacity;
                mSize = rhs.mSize;
            }
            arr.reset(new T[mCapacity]);
            for (unsigned int i = 0; i < mSize; i++) {
                arr[i] = rhs.arr[i];
            }
        }
        return( *this );
    }

    Vector& operator =(Vector<T> &&rValue) {
        if (this != &rValue) {
            mCapacity = rValue.mCapacity;
            mSize = rValue.mSize;
            arr.reset(new T[mCapacity]);
            arr = std::move(rValue.arr);
        }
        return ( *this );
    }

    bool operator ==(const Vector<T> &rhs) const {
        if (this != &rhs) {
            if (mSize != rhs.mSize || mCapacity != rhs.mCapacity) {
                return ( false );
            }
            for (unsigned int i =0 ; i < mSize; i++) {
                if (arr[i] != rhs.arr[i]) {
                    return( false );
                }
            }
        }
        return( true );
    }

    size_type capacity() const { return mCapacity; }

    size_type size() const { return mSize; }

    T& operator[](size_type index) {
        if (index < 0 || index >= mSize) {
            throw std::out_of_range("Bad Index");
        }
        return arr[index];
    }

    const T& operator[](size_type index) const {
        if (index < 0 || index >= mSize) {
            throw std::out_of_range("Bad index");
        }
        return arr[index];
    }

    void clear() { arr.reset(new T[mCapacity]); }

    void push_back(const T& value) {
        if (mCapacity == 0) mCapacity++;
        if (isFull()) reserve(mCapacity * 2);
        arr[mSize] = value;
        mSize++;
    }

    void reserve(size_type new_cap) {
        if (new_cap > mCapacity) {
            Vector<T> temp(*this);
            mCapacity = new_cap;
            arr.reset(new T[mCapacity]);
            for (unsigned int i = 0; i < mSize; i++) {
                arr[i] = temp[i];
            }
        }
    }

    void shrink_to_fit() {
        if (mSize != mCapacity) {
            Vector<T> temp(*this);
            mCapacity = mSize;
            arr.reset(new T[mCapacity]);
            for (unsigned int i = 0; i < mSize; i++) {
                arr[i] = temp[i];
            }
        }
    }

    iterator begin() { return iterator(arr); }

    iterator end() { return iterator(arr + mSize); }

    const_iterator begin() const { return const_iterator(arr); }

    const_iterator end() const { return const_iterator(arr + mSize); }

private:
    bool isFull() const { return mSize >= mCapacity; }

    std::unique_ptr<T[]> arr;

    size_type mSize;

    size_type mCapacity;

};



#endif //Vector_H
