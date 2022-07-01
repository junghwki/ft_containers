#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include "VectorIterator.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T>>
	class Vector
	{
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::VectorIterator<T, false>			iterator;
			typedef typename ft::VectorIterator<T, true>			const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef size_t											size_type;
		
		private:
			value_type*												mPtr;
			allocator_type											mAlloc;
			size_type												mSize;
			size_type												mCapacity;

		public:
		//생성자
			explicit Vector (const allocator_type& alloc = allocator_type())
				: mPtr(NULL), mAlloc(alloc), mSize(0), mCapacity(0)
			{
			};

			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: mAlloc(alloc), mSize(0), mCapacity(0)
			{
				assign(n, val);
			};

			template <class InputIterator>
			Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: mPtr(NULL), mAlloc(alloc), mSize(0), mCapacity(0)
			{
				this->assign(first, last);
			};

			Vector (const Vector& x)
				: mPtr(NULL), mAlloc(x.mAlloc), mSize(0), mCapacity(0)
			{
			};
		//생성자 끝
			~Vector()
			{
			};

			Vector& operator= (const Vector& x)
			{

			};

			iterator begin(void)
			{
				return (iterator(this->mArr));
			};

			const_iterator begin(void) const
			{
				return (const_iterator(this->mArr));
			};

			iterator end(void)
			{
				return (iterator(this->mArr + this->mSize));
			};

			const_iterator end(void) const
			{
				return (const_iterator(this->mArr + this->mSize));
			};

			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(this->end()));
			};

			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(this->end()));
			};

			reverse_iterator rend(void)
			{
				return (reverse_iterator(this->begin()));
			};

			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(this->begin()));
			};

			size_type size(void) const
			{
				return (this->mSize)
			};

			size_type max_size(void) const
			{
				return (this->mAlloc.max_size());
			}

			void expandCapacity(size_type n)
			{
				value_type*	tempPtr;

				/*if (n < this->mSize)
				{
					error
				}*/
				tempPtr = this->mAlloc.allocate(n);
				memcpy(tempPtr, this->mPtr, this->mSize);
				this->mAlloc.destroy(this->mPtr);
				this->mAlloc.deallocate(this->mPtr, this->mCapacity);
				this->mCapacity = n;
				this->mPtr = tempPtr;
			};

			void resize (size_type n, value_type val = value_type())
			{
				value_type*	tempPtr;
				size_type	tempCapacity;
				int			idx;

				if (n > this->mCapacity)
				{
					tempCapacity = this->mCapacity;
					if (n > this->mCapacity * 2)
					{
						// this->mCapacity = n;
						this->expandCapacity(n);
					}
					else
					{
						// this->mCapacity *= 2;
						this->expandCapacity(this->mCapacity * 2);
					}
				}
				if (n > this->mSize)
				{
					tempPtr = this->mAlloc.allocate(n);
					idx = this->mSize;
					while (idx < n)
					{
						tempPtr[idx] = val;
						idx++;
					}
					memcpy(tempPtr, this->mPtr, this->mSize);
					this->mAlloc.destroy(this->mPtr);
					this->mAlloc.deallocate(this->mPtr, tempCapacity);
					this->mSize = n;
					this->mPtr = tempPtr;
				}
			};

			size_type capacity(void) const
			{
				return (this->mCapacity);
			};

			bool empty(void) const
			{
				if (this->mSize)
				{
					return (false);
				}
				return (true);
			};

			void reserve (size_type n)
			{
				if (this->max_size() < n)
				{
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				}
				if (n > this->mCapacity)
				{
					// this->mCapacity = n;
					this->expandCapacity(n);
				}
			};

			reference operator[] (size_type n)
			{
				return (this->mPtr[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return (this->mPtr[n]);
			}

			reference at (size_type n)
			{
				if (this->_size <= n)
				{
					throw std::out_of_range("vector");
				}
				return (*(this->mPtr + n));
			}

			const_reference at (size_type n) const
			{
				if (this->_size <= n)
				{
					throw std::out_of_range("vector");
				}
				return (*(this->mPtr + n));
			}

			reference front(void)
			{
				return (this->mPtr[0]);
			}

			const_reference front(void) const
			{
				return (this->mPtr[0]);
			}

			reference back(void)
			{
				return (this->mPtr[this->mSize - 1]);
			}

			const_reference back(void) const
			{
				return (this->mPtr[this->mSize - 1]);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral< InputIterator>::value, InputIterator>::type* = NULL)
			{
				
			};

			void assign (size_type n, const value_type& val)
			{
				int idx = 0;

				this->clear();
				if (n > this->mCapacity)
				{
					this->mAlloc.destroy(this->mPtr);
					this->mAlloc.deallocate(this->mPtr, this->mCapacity);
					this->mCapacity = n;
					this->mPtr = this->mAlloc.allocate(this->mCapacity);
				}
				while (idx < n)
				{
					this->mPtr[idx] = val;
					idx++; 
				}
				this->mSize = n;
			};

			void push_back (const value_type& val)
			{
				if (this->mSize < this->mCapacity)
				{
					this->mPtr[this->mSize + 1] = val;
					++this->mSize;
					//전위가 빠름 아무튼 빠름
				}
				else
				{
					this->expandCapacity(this->mCapacity * 2);
					this->mPtr[this->mSize + 1] = val;
					++this->mSize;
					//전위가 빠름 아무튼 빠름
				}
				
			};

			void pop_back(void)
			{
				this->mAlloc.destory(this->mPtr[this->mSize - 1]);
			}

			iterator insert (iterator position, const value_type& val)
			{

			};

			void insert (iterator position, size_type n, const value_type& val)
			{

			};

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{

			};

			iterator erase (iterator position)
			{

			};

			iterator erase (iterator first, iterator last)
			{

			};

			void swap (Vector& x)
			{

			};

			void clear(void)
			{
				int idx = 0;

				while (idx < this->mSize)
				{
					this->mAlloc.destroy(&this->mPtr[idx]);
					idx++;
				}
				this->mSize = 0;
			};

			allocator_type get_allocator(void) const
			{
				return (this->mAlloc);
			};

			template <class T, class Alloc>
			bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{
				
			};

			template <class T, class Alloc>
			bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{

			};

			template <class T, class Alloc>
			bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{

			};

			template <class T, class Alloc>
			bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{

			};

			template <class T, class Alloc>
			bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{

			};

			template <class T, class Alloc>
			bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{

			};

			template <class T, class Alloc>
			void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y);
		private:
	};
}

#endif