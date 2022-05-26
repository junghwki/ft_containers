#ifndef VECTOR_HPP
# define VECTOR_HPP

template < typename T >
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
		{
		};

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: mAlloc(alloc), mSize(0), mCapacity(0)
		{
			assign(n, val);
		};

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		{

		};

		vector (const vector& x)
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
		size_type size() const;
		size_type max_size() const;
		void resize (size_type n, value_type val = value_type());
		size_type capacity() const;
		bool empty() const;
		void reserve (size_type n);
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
		reference at (size_type n);
		const_reference at (size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val)
		{
			int idx = 0;

			this->clear();
			if (n > this->mCapacity)
			{
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
		void push_back (const value_type& val);
		void pop_back();

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

		allocator_type get_allocator() const;
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

#endif