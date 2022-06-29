#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>

namespace ft {
	template < typename T, typename Alloc = std::allocator<T> >
	class Vector {
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::VectorIter<T, false>				iterator;
			typedef typename ft::VectorIter<T, true>				const_iterator;
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
			explicit vector (const allocator_type& alloc = allocator_type())
				: mPtr(NULL), mAlloc(alloc), mSize(0), mCapacity(0)
			{};

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: mAlloc(alloc), mSize(0), mCapacity(0)
			{
				assign(n, val);
			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: mPtr(NULL), mAlloc(alloc), mSize(0), mCapacity(0)
			{
				this->assign(first, last);
			};

			vector (const vector& x)
				: mPtr(NULL), mAlloc(x.mAlloc), mSize(0), mCapacity(0)
			{

			};
		//생성자 끝
			~Vector();
			vector& operator= (const vector& x);
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			size_type size() const
			{
				return (this->mSize)
			};

			size_type max_size() const
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

			size_type capacity() const
			{
				return (this->mCapacity);
			};

			bool empty() const
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

			reference front()
			{
				return (this->mPtr[0]);
			}

			const_reference front() const
			{
				return (this->mPtr[0]);
			}

			reference back()
			{
				return (this->mPtr[this->mSize - 1]);
			}

			const_reference back() const
			{
				return (this->mPtr[this->mSize - 1]);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
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
					this->mSize++;
				}
				else
				{
					this->expandCapacity(this->mCapacity * 2);
				}
				
			};

			void pop_back()
			{
				this->mAlloc.destory(this->mPtr[this->mSize - 1]);
			}

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (vector& x);
			void clear()
			{
				int idx = 0;

				while (idx < this->mSize)
				{
					this->mAlloc.destroy(&this->mPtr[idx]);
					idx++;
				}
				this->mSize = 0;
			};

			allocator_type get_allocator() const
			{
				return (this->mAlloc);
			};
			template <class T, class Alloc>
			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
		private:
	};
}

#endif