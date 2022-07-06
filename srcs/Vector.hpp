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
				if (this->mCapacity > 0)
				{
					this->clear();
					this->mAlloc.deallocate(this->mPtr, this->mCapacity);
				}
			};

			Vector& operator= (const Vector& x)
			{
				if (this == &x)
				{
					return (*this);
				}
				this->reserve(x.mSize);
				this->assign(x.begin(), x.end());
				return (*this);
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
				value_type*		tempPtr = this->mAlloc.allocate(n);	

				if (this->mCapacity == 0)
				{
					this->mPtr = this->mAlloc.allocate(n);
					this->mCapacity = n;
				}
				else
				{
					memcpy(tempPtr, this->mPtr, this->mSize);
					for (size_type idx = 0; idx < this->mCapacity; ++idx)
					{
						this->mAlloc.destroy(this->mPtr + idx);
					}
					this->mAlloc.deallocate(this->mPtr, this->mCapacity);
					this->mCapacity = n;
					this->mPtr = tempPtr;
				}
			};

			void resize (size_type n, value_type val = value_type())
			{
				value_type*		tempPtr;
				size_type		tempCapacity;
				int				idx;

				if (n > this->mCapacity)
				{
					tempCapacity = this->mCapacity;
					if (n > this->mCapacity * 2)
					{
						this->expandCapacity(n);
					}
					else
					{
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
					for (size_type idx = 0; idx < this->mCapacity; ++idx)
					{
						this->mAlloc.destroy(this->mPtr + idx);
					}
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
				if (this->mCapacity < n)
				{
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

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{

			};

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				for (size_type idx = 0; idx < n; ++idx)
					this->push_back(val);
			};

			void push_back (const value_type& val)
			{
				if (this->mSize < this->mCapacity)
				{
					this->mPtr[this->mSize + 1] = val;
				}
				else
				{
					this->expandCapacity(this->mCapacity * 2);
					this->mPtr[this->mSize + 1] = val;
				}
				++this->mSize;
				//전위가 빠름 아무튼 빠름
				
			};

			void pop_back(void)
			{
				--this->mSize;
				this->mAlloc.destory(this->mPtr[this->mSize]);
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type		idx = 0;
				const_iterator	it = this->begin();

				while (it != position)
				{
					it++;
					idx++;
				}
				this->insert(position, 1, val);
				return (iterator(this->mPtr + idx));
			};

			void insert (iterator position, size_type n, const value_type& val)
			{
				// size_type pos = 0;
				// for (const_iterator iter = this->begin(); iter != position; ++iter)
				// {
				// 	pos++;
				// }
				// if (this->_capacity < this->_size + n && this->_capacity * 2 < this->_size + n)
				// {
				// 	this->_expandCapacity(this->_size + n);
				// }
				// else if (this->_capacity < this->_size + n)
				// {
				// 	this->_expandCapacity();
				// }
				// memmove(reinterpret_cast<void *>(&this->_arr[pos + n]), reinterpret_cast<void *>(&this->_arr[pos]), sizeof(value_type) * (this->_size - pos));
				// for (size_type i = 0; i < n; ++i)
				// {
				// 	this->_arr[pos + i] = val;
				// }
				// this->_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{

			};

			iterator erase (iterator position)
			{
				// size_type	idx = 0;

				// for (const_iterator it = this->begin(); it != position; ++it)
				// {
				// 	idx++;
				// }
				// this->mAlloc.destroy(this->mPtr[idx]);
				// for (size_type i = 0; i < this->mSize - idx - 1; ++i)
				// {
				// 	this->mPtr[idx + i] = this->mPtr[idx + i + 1];
				// }
				// --this->mSize;
				// return (position);
				return (this->erase(position, position + 1));
			};

			iterator erase (iterator first, iterator last)
			{
				size_type	pos = 0;
				size_type	n = 0;
				iterator	it = this->begin();

				while (it != first)
				{
					pos++;
					it++;
				}
				while (it != last)
				{
					this->mAlloc.destroy(this->mPtr + pos + n++);
					it++;
				}
				for (size_type idx = 0; idx < this->mSize - pos - n; ++idx)
				{
					this->mPtr[pos + idx] = this->mPtr[pos + idx + n];
				}
				this->mSize -= n;
				return (first);
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