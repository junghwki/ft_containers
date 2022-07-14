#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include "Iterator.hpp"
#include "Utils.hpp"

namespace ft
{
	template <typename T, typename value_compare, typename Alloc, bool is_const>
	class MapIterator
	{
	public:
		typedef T																			value_type;
		typedef ptrdiff_t																	difference_type;
		typedef value_compare																comp;
		typedef Alloc																		allocator_type;
		typedef typename ft::typeSelector<value_type *, const value_type *, is_const>::type	pointer;
		typedef typename ft::typeSelector<value_type &, const value_type &, is_const>::type	reference;
		typedef typename ft::bidirectional_iterator_tag										iterator_category;
		typedef typename ft::BST<T, value_compare, Alloc>::Node								Node;

	private:
		Node*	mNode;
		Node*	mNullNode;

	public:
		MapIterator()
		{
		};

		MapIterator(Node* node, Node* nullNode)
			: mNode(node), mNullNode(nullNode)
		{
		};

		MapIterator(MapIterator<value_type, comp, allocator_type, false> const &arg)
		{
			mNode = arg.getNode();
			mNullNode = arg.getNullNode();
		};

		MapIterator &operator=(MapIterator const &arg)
		{
			mNode = arg.mNode;
			mNullNode = arg.mNullNode;
			return *this;
		};

		~MapIterator()
		{
		};

		Node* getNode() const
		{
			return this->mNode;
		};

		Node* getNullNode() const
		{
			return this->mNullNode;
		};

		bool operator==(MapIterator<value_type, comp, allocator_type, true> const &arg) 
		{
			return this->mNode == arg.getNode();
		}

		bool operator==(MapIterator<value_type, comp, allocator_type, false> const &arg)
		{
			return this->mNode == arg.getNode();
		}

		bool operator!=(MapIterator<value_type, comp, allocator_type, true> const &arg) 
		{
			return this->mNode != arg.getNode();
		}

		bool operator!=(MapIterator<value_type, comp, allocator_type, false> const &arg)
		{
			 return this->mNode != arg.getNode();
		}

		reference operator*() const
		{
			return this->mNode->mValue;
		};

		pointer operator->() const
		{
			return &(operator*());
		};

		MapIterator &operator++()
		{
			if (this->mNode->mRight != this->mNullNode)
			{
				this->mNode = this->mNode->mRight;
				while (this->mNode->mLeft != this->mNullNode)
				{	
					this->mNode = this->mNode->mLeft;
				}
			}
			else
			{
				while (this->mNode->mParent && this->mNode == this->mNode->mParent->mRight)
				{
					this->mNode = this->mNode->mParent;
				}
				this->mNode = this->mNode->mParent;
			}
			if (this->mNode == NULL)
			{
				this->mNode = this->mNullNode;
			}
			return (*this);
		};

		MapIterator operator++(int)
		{
			MapIterator ret(*this);

			++(*this);
			return (ret);
		};

		MapIterator &operator--()
		{
			if (this->mNode == this->mNullNode)
			{
				while (this->mNode->mRight != this->mNullNode)
				{
					this->mNode = this->mNode->mRight;
				}
			}
			else if (this->mNode->mLeft != this->mNullNode)
			{
				this->mNode = this->mNode->mLeft;
				while (this->mNode->mRight != this->mNullNode)
				{
					this->mNode = this->mNode->mRight;
				}
			}
			else
			{
				while (this->mNode->mParent && this->mNode == this->mNode->mParent->mLeft)
				{
					this->mNode = this->mNode->mParent;
				}
				this->mNode = this->mNode->mParent;
			}

			std::cout << this->mNode->mValue.second << std::endl;
			return (*this);
		};

		MapIterator operator--(int)
		{
			MapIterator ret(*this);

			--(*this);
			return (ret);
		};
	};
} // namespace ft

#endif
