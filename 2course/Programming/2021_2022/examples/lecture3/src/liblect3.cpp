#include "liblect3.h"

FP003Array::FP003Array(size_t arr_sz) : 
    data_{new int[arr_sz]}, length_{arr_sz}, capacity_{arr_sz}  
{}

FP003Array::~FP003Array()
{
  delete[] data_;
  data_ = nullptr;
}

FP003Array::FP003Array(const FP003Array& other) : 
    data_{new int[other.capacity_]}, length_{other.length_}, capacity_{other.capacity_}	
{
  for (size_t i = 0; i < other.length_; i++) {
    data_[i] = other.data_[i];
  }
}

int& FP003Array::operator[](size_t index)
{
  const size_t safe_index = (length_ == 0) ? 0 : index % length_;
  return data_[safe_index];
}

const int& FP003Array::operator[](size_t index) const
{
  const size_t safe_index = (length_ == 0) ? 0 : index % length_;
  return data_[safe_index];
}

FP003Array& FP003Array::operator=(const FP003Array& rhs)
{
  delete[] data_;
  
  length_ = rhs.length_;
  capacity_ = rhs.capacity_;
  
  data_ = new int[capacity_];
  for (size_t i = 0; i < rhs.length_; i++) {
    data_[i] = rhs.data_[i];
  }
  
  return *this;
}

size_t FP003Array::length() const
{
  return length_;
}

void FP003Array::push(int new_elem)
{
  if (length_ >= capacity_) {
    re_allocate();
  } 
  
  data_[length_] = new_elem;
  length_++;
}

void FP003Array::re_allocate()
{
  capacity_ = (capacity_ == 0) ? 
              2 : capacity_ * 2;
              
  int *new_data = new int[capacity_];
  for (size_t i = 0; i < length_; i++) {
    new_data[i] = data_[i];
  }
  
  delete[] data_;
  data_ = new_data;
}




