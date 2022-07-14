#ifndef MAP_HPP
# define MAP_HPP

#include "Utils.hpp"
#include "BST.hpp"
#include "Pair.hpp"
#include "MapIterator.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key																key_type;
		typedef T																mapped_type;
		typedef ft::pair<const key_type, mapped_type>							value_type;
		typedef Compare															key_compare;
		typedef Alloc															allocator_type;
		typedef	typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;

		class value_compare
		{
		public:
			Compare	mComp;
			value_compare()
			{
			}
			value_compare(Compare c)
			: mComp(c)
			{
			}
		
		public:
			typedef bool														result_type;
			typedef value_type													first_argument_type;
			typedef value_type													second_argument_type;
			bool operator()(const value_type& x, const value_type& y) const
			{
				return (this->mComp(x.first, y.first));
			}
		};

		typedef ft::MapIterator<value_type, value_compare, Alloc, false>		iterator;
		typedef ft::MapIterator<value_type, value_compare, Alloc, true>			const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type			difference_type;
		typedef std::size_t														size_type;

		typedef BST<value_type, value_compare, Alloc>							bst_type;
		typedef typename Alloc::template rebind<bst_type>::other				bst_alloc;
		typedef typename bst_type::Node	Node;
	private:
		bst_type*																mBST;
		allocator_type 															mAlloc;
		key_compare																mKeyComp;
		bst_alloc																mBstAlloc;

	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: mAlloc(alloc), mKeyComp(comp)
		{
			this->mBST = mBstAlloc.allocate(1);
			this->mBstAlloc.construct(this->mBST, bst_type());
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: mAlloc (alloc), mKeyComp(comp)
		{
			this->mBST = mBstAlloc.allocate(1);
			this->mBstAlloc.construct(this->mBST, bst_type());
			this->insert(first, last);
		}

		map(const map& x)
		{
			this->mBST = mBstAlloc.allocate(1);
			this->mBstAlloc.construct(this->mBST, bst_type());
			this->mAlloc = x.mAlloc;
			this->mKeyComp = x.mKeyComp;
			this->mBstAlloc = x.mBstAlloc;
			*(this->mBST) = *(x.mBST);
		}

		~map()
		{
			clear();
			this->mBstAlloc.destroy(this->mBST);
			this->mBstAlloc.deallocate(this->mBST, 1);
		}

		map &operator=(const map &x)
		{
			this->mAlloc = x.mAlloc;
			this->mKeyComp = x.mKeyComp;
			this->mBstAlloc = x.mBstAlloc;
			*(this->mBST) = *(x.mBST);
			return (*this);
		}

		iterator begin()
		{
			Node*	temp;

			temp = this->mBST->mRoot;
			if (!temp)
			{
				return (this->end());
			}
			while (temp->mLeft != this->mBST->mNullNode)
			{
				temp = temp->mLeft;
			}
			return (iterator(temp, this->mBST->mNullNode));
		}

		const_iterator begin() const
		{
			Node*	temp;

			temp = this->mBST->mRoot;
			if (!temp)
			{
				return (this->end());
			}
			while (temp->mLeft != this->mBST->mNullNode)
			{
				temp = temp->mLeft;
			}
			return (const_iterator(temp, this->mBST->mNullNode));
		}

		iterator end()
		{
			return (iterator(this->mBST->mNullNode, this->mBST->mNullNode));
		}

		const_iterator end() const
		{
			return (const_iterator(this->mBST->mNullNode, this->mBST->mNullNode));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin()));
		}

		bool empty() const
		{
			return (!(this->mBST->mSize));
		}

		size_type size() const
		{
			return (this->mBST->mSize);
		}

		size_type max_size() const
		{
			return (this->mAlloc.max_size());
		}

		mapped_type& operator[](const key_type& k)
		{
			Node* ret;
			
			ret = this->mBST->searchNode(value_type(k, mapped_type()));
			if (!ret)
			{
				return (this->mBST->addNode(value_type(k, mapped_type()))->mValue.second);
			}
			return (ret->mValue.second);
		}

		pair<iterator,bool> insert(const value_type& val)
		{
			Node* temp;

			temp = this->mBST->searchNode(val);
			if (temp)
			{
				return (pair<iterator,bool>(iterator(temp, this->mBST->mNullNode), false));
			}
			temp = this->mBST->addNode(val);
			return (pair<iterator,bool>(iterator(temp, this->mBST->mNullNode), true));
		}

		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return (iterator(this->mBST->addNode(val), this->mBST->mNullNode));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->mBST->addNode(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			this->mBST->deleteNode(*position);
		}

		size_type erase(const key_type& k)
		{
			return (this->mBST->deleteNode(value_type(k, mapped_type())));
		}

		void erase(iterator first, iterator last)
		{
			iterator temp;

			for (iterator it = first; it != last;)
			{
				temp = it;
				it++;
				erase(temp);
			}
		}

		void swap(map& x)
		{
			this->swap(this->mBST, x.mBST);
			this->swap(this->mAlloc, x.mAlloc);
			this->swap(this->mKeyComp, x.mKeyComp);
			this->swap(this->mBstAlloc, x.mBstAlloc);
		}

		void clear()
		{
			this->mBST->clear(this->mBST->mRoot);
			this->mBST->mRoot = NULL;
		}

		key_compare key_comp() const
		{
			return (this->mKeyComp);
		}

		value_compare value_comp() const
		{
			return (value_compare());
		}

		iterator find(const key_type& k)
		{
			Node* ret;

			ret = this->mBST->searchNode(value_type(k, mapped_type()));
			if (ret)
			{
				return (iterator(ret, this->mBST->mNullNode));
			}
			return (this->end());
		}

		const_iterator find(const key_type& k) const
		{
			Node* ret;

			ret = this->mBST->searchNode(value_type(k, mapped_type()));
			if (ret)
			{
				return (const_iterator(ret, this->mBST->mNullNode));
			}
			return (this->end());
		}

		size_type count(const key_type& k) const
		{
			if (this->find(k) != this->end())
				return (true);
			return (false);
		}

		iterator lower_bound(const key_type& k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!this->mKeyComp(it->first, k))
				{
					return (it);
				}
			}
			return (this->end());
		}

		const_iterator lower_bound(const key_type& k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (!this->mKeyComp(it->first, k))
				{
					return (it);
				}
			}
			return (this->end());
		}

		iterator upper_bound(const key_type &k)
		{
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (this->mKeyComp(k, it->first))
				{
					return (it);
				}
			}
			return (this->end());
		}

		const_iterator upper_bound(const key_type &k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (this->mKeyComp(k, it->first))
				{
					return (it);
				}
			}
			return (this->end());
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{
			return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		pair<iterator,iterator>	equal_range(const key_type& k)
		{
			return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

		allocator_type get_allocator() const
		{
			return (this->mAlloc);
		}

	private:
		template <typename U>
		void swap(U& x, U& y)
		{
			U	temp;

			temp = x;
			x = y;
			y = temp;
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return false;
		}
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif