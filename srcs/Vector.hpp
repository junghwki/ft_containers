#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "VectorIterator.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
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
		explicit vector(const allocator_type& alloc = allocator_type())
			: mPtr(NULL), mAlloc(alloc), mSize(0), mCapacity(0)
		{
		};

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: mAlloc(alloc), mSize(0), mCapacity(0)
		{
			assign(n, val);
		};

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			: mPtr(NULL), mAlloc(alloc), mSize(0), mCapacity(0)
		{
			this->assign(first, last);
		};

		vector(const vector& x)
			: mPtr(NULL), mAlloc(x.mAlloc), mSize(0), mCapacity(0)
		{
			this->assign(x.begin(), x.end());
		};

		~vector()
		{
			if (this->mCapacity > 0)
			{
				this->clear();
				this->mAlloc.deallocate(this->mPtr, this->mCapacity);
			}
		};

		vector& operator=(const vector& x)
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
			return (iterator(this->mPtr));
		};

		const_iterator begin(void) const
		{
			return (const_iterator(this->mPtr));
		};

		iterator end(void)
		{
			return (iterator(this->mPtr + this->mSize));
		};

		const_iterator end(void) const
		{
			return (const_iterator(this->mPtr + this->mSize));
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
			return (this->mSize);
		};

		size_type max_size(void) const
		{
			return (this->mAlloc.max_size());
		}

		void expandCapacity(size_type n)
		{
			value_type*		tempPtr;
			if (this->mCapacity == 0)
			{
				this->mPtr = this->mAlloc.allocate(n);
				this->mCapacity = n;
			}
			else
			{
				tempPtr = this->mAlloc.allocate(n);	
				memcpy(tempPtr, this->mPtr, this->mSize * sizeof(value_type));
				for (size_type idx = 0; idx < this->mSize; ++idx)
				{
					this->mAlloc.destroy(this->mPtr + idx);
				}
				this->mAlloc.deallocate(this->mPtr, this->mCapacity);
				this->mCapacity = n;
				this->mPtr = tempPtr;
			}
		};

		void resize(size_type n, value_type val = value_type())
		{
			// value_type*		tempPtr;
			// size_type		tempCapacity;
			size_type		idx;

			if (n > this->mCapacity)
			{
				// tempCapacity = this->mCapacity;
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
				idx = this->mSize;
				while (idx < n)
				{
					this->mPtr[idx] = val;
					idx++;
				}
				// tempPtr = this->mAlloc.allocate(n);
				// idx = this->mSize;
				// while (idx < n)
				// {
				// 	tempPtr[idx] = val;
				// 	idx++;
				// }
				// memcpy(tempPtr, this->mPtr, this->mSize);
				// for (size_type idx = 0; idx < this->mCapacity; ++idx)
				// {
				// 	this->mAlloc.destroy(this->mPtr + idx);
				// }
				// this->mAlloc.deallocate(this->mPtr, tempCapacity);
				// this->mSize = n;
				// this->mPtr = tempPtr;
			}
			this->mSize = n;
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

		void reserve(size_type n)
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

		reference operator[](size_type n)
		{
			return (this->mPtr[n]);
		}

		const_reference operator[](size_type n) const
		{
			return (this->mPtr[n]);
		}

		reference at(size_type n)
		{
			if (this->mSize <= n)
			{
				throw std::out_of_range("vector");
			}
			return (*(this->mPtr + n));
		}

		const_reference at(size_type n) const
		{
			if (this->mSize <= n)
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
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type	idx = 0;

			this->clear();
			for (InputIterator it = first; it != last; ++it)
			{
				idx++;
			}
			this->mSize = idx;
			if (idx != 0)
				expandCapacity(idx);
			idx = 0;
			for (InputIterator it = first; it != last; ++it)
			{
				this->mPtr[idx] = *it;
				idx++;
			}
		};

		void assign(size_type n, const value_type& val)
		{
			this->clear();
			this->reserve(n);
			for (size_type idx = 0; idx < n; ++idx)
				this->push_back(val);
		};

		void push_back(const value_type& val)
		{
			if (this->mSize < this->mCapacity)
			{
				this->mPtr[this->mSize] = val;
			}
			else
			{
				if (this->mCapacity)
				{
					this->expandCapacity(this->mCapacity * 2);
				}
				else
				{
					this->expandCapacity(1);
				}
				this->mPtr[this->mSize] = val;
			}
			++this->mSize;
			//http://egloos.zum.com/indra207/v/4848273
			
		};

		void pop_back(void)
		{
			--this->mSize;
			this->mAlloc.destroy(&this->mPtr[this->mSize]);
		}

		iterator insert(iterator position, const value_type& val)
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
////////////////////////////////////////////
		void insert(iterator position, size_type n, const value_type& val)
		{
			size_type pos = 0;

			for (iterator it = begin(); it != position; ++it)
				pos++;
			if (this->mCapacity * 2 <= this->mSize + n)
				reserve(this->mSize + n);
			else if (this->mCapacity < this->mSize + n)
				reserve(this->mCapacity * 2);
			for (size_type idx = this->mSize; idx > pos; --idx)
				this->mPtr[idx + n - 1] = this->mPtr[idx - 1];
			for (size_type idx = pos; idx < pos + n; ++idx)
				this->mPtr[idx] = val;
			this->mSize += n;
		}
////////////////////////////////////////////
		template <class InputIterator>
		void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			size_type pos = 0;
			size_type size = 0;

			for (iterator it = begin(); it != position; ++it)
				pos++;
			for (InputIterator itr = first; itr != last; ++itr)
				size++;
			if (this->mCapacity * 2 <= this->mSize + size)
				reserve(this->mSize + size);
			else if (this->mSize + size > this->mCapacity)
				reserve(this->mCapacity * 2);
			for (size_type idx = this->mSize; idx > pos; --idx) // 앞은 건들지 말고 position 후의 값만 이동하면 된다
				this->mPtr[idx + size - 1] = this->mPtr[idx - 1];
			for (size_type idx = pos; idx < pos + size; ++idx)
			{
				this->mPtr[idx] = *first;
				first++;
			}
			this->mSize += size;
		};
////////////////////////////////////////////

		iterator erase(iterator position)
		{
			return (this->erase(position, position + 1));
		};

		iterator erase(iterator first, iterator last)
		{
			size_type	pos = 0;
			size_type	n = 0;
			iterator	it = this->begin();

			for (; it != first; ++it)
			{
				pos++;
			}
			for (; it != last; ++it)
			{
				this->mAlloc.destroy(this->mPtr + pos + n);
				n++;
			}
			for (size_type idx = 0; idx < this->mSize - pos - n; ++idx)
			{
				this->mPtr[pos + idx] = this->mPtr[pos + idx + n];
			}
			this->mSize -= n;
			return (first);
		};

		void swap(vector& x)
		{
			// if (x == *this)
			// 	return;

			pointer			saveStart = x.mPtr;
			size_type		saveEnd = x.mSize;
			size_type		saveEndCapacity = x.mCapacity;
			allocator_type	saveAllocator = x.mAlloc;

			x.mPtr = this->mPtr;
			x.mSize = this->mSize;
			x.mCapacity = this->mCapacity;
			x.mAlloc = this->mAlloc;

			this->mPtr = saveStart;
			this->mSize = saveEnd;
			this->mCapacity = saveEndCapacity;
			this->mAlloc = saveAllocator;
		};

		void clear(void)
		{
			// int idx = 0;

			for (size_type idx = 0; idx < this->mSize; ++idx)
			// while (idx < this->mSize)
			{
				this->mAlloc.destroy(&this->mPtr[idx]);
				// idx++;
			}
			this->mSize = 0;
		};

		allocator_type get_allocator(void) const
		{
			return (this->mAlloc);
		};
	};
	template <typename T, typename Alloc>
	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename T, typename Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T, typename Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename T, typename Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, typename Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T, typename Alloc>
	void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
			// template <class T, class Alloc>
			// bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			// {

			// };

			// template <class T, class Alloc>
			// bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			// {

			// };

			// template <class T, class Alloc>
			// bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			// {

			// };

			// template <class T, class Alloc>
			// bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			// {

			// };

			// template <class T, class Alloc>
			// bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			// {

			// };

			// template <class T, class Alloc>
			// bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			// {

			// };

			// template <class T, class Alloc>
			// void swap(Vector<T,Alloc>& x, Vector<T,Alloc>& y)
			// {

			// };
};

#endif