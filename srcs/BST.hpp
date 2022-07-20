#ifndef BST_HPP
# define BST_HPP

namespace ft
{
	template <typename T, typename Compare, typename Alloc>
	class BST
	{
	public:
		class Node
		{
		public:
			Node*												mParent;
			Node*												mLeft;
			Node*												mRight;
			T													mValue;

			Node()
				: mParent(NULL), mLeft(NULL), mRight(NULL), mValue(T())
			{}

			Node(T value, Node* nullNode)
				: mParent(NULL), mLeft(nullNode), mRight(nullNode), mValue(value)
			{}

			Node(const Node& node)
				: mParent(node.mParent), mLeft(node.mLeft), mRight(node.mRight), mValue(node.mValue)
			{}

			Node& operator=(const Node& arg)
			{
				this->mParent = arg.mParent;
				this->mLeft = arg.mLeft;
				this->mRight = arg.mRight;
				this->mValue = arg.mValue;
				return (*this);
			}

			~Node()
			{}
		};
		
	private:
		typedef typename Alloc::template rebind<Node>::other	nodeAlloc;

	public:
		Node*													mRoot;
		Node*													mNullNode;
		nodeAlloc												mNodeAlloc;
		Alloc													mAlloc;
		Compare													mComp;
		size_t													mSize;

		BST(const Alloc& alloc = Alloc(), const Compare& comp = Compare())
			: mRoot(NULL), mNodeAlloc(alloc), mComp(comp), mSize(0)
		{
			this->mNullNode = this->mNodeAlloc.allocate(1);
			this->mNodeAlloc.construct(this->mNullNode, Node());
		}

		BST(const BST& arg)
			: mRoot(NULL), mNodeAlloc(arg.mAlloc), mComp(arg.mComp), mSize(0)
		{
			this->mNullNode = this->mNodeAlloc.allocate(1);
			this->mNodeAlloc.construct(this->mNullNode, Node());
		}

		~BST()
		{
			this->clear(this->mRoot);
			this->mNodeAlloc.destroy(this->mNullNode);
			this->mNodeAlloc.deallocate(this->mNullNode, 1);
		}

		BST& operator=(const BST& arg)
		{
			if (this->mRoot)
			{
				clear(this->mRoot);
				this->mRoot = NULL;
				this->mNullNode->mRight = this->mRoot;
			}
			this->copy(arg.mRoot, arg.mNullNode);
			
			return (*this);
		}

		void copy(Node* node, Node* nullNode)
		{
			if (!node || node == nullNode)
			{
				return ;
			}
			this->addNode(node->mValue);
			this->copy(node->mLeft, nullNode);
			this->copy(node->mRight, nullNode);
		}

		void clear(Node* node)
		{
			if (!node || (node == this->mNullNode))
			{
				return ;
			}
			clear(node->mLeft);
			clear(node->mRight);
			this->mNodeAlloc.destroy(node);
			this->mNodeAlloc.deallocate(node, 1);
			--this->mSize;
		}

		Node* addNode(T value)
		{
			Node*	node;
			Node*	temp = this->mRoot;

			node = this->mNodeAlloc.allocate(1);
			this->mNodeAlloc.construct(node, Node(value, this->mNullNode));
			if (this->mRoot == NULL)
			{
				this->mRoot = node;
				this->mNullNode->mRight = this->mRoot;
				++this->mSize;
				return (node);
			}
			while (temp != this->mNullNode)
			{
				if (this->mComp(temp->mValue, value))
				{
					if (temp->mRight == this->mNullNode)
					{
						temp->mRight = node;
						node->mParent = temp;
						++this->mSize;
						return (node);
					}
					temp = temp->mRight;
				}
				else if (this->mComp(value, temp->mValue))
				{
					if (temp->mLeft == this->mNullNode)
					{
						temp->mLeft = node;
						node->mParent = temp;
						++this->mSize;
						return (node);
					}
					temp = temp->mLeft;
				}
				else
				{
					this->mNodeAlloc.destroy(node);
					this->mNodeAlloc.deallocate(node, 1);
					return (temp);
				}
			}
			return (NULL);
		}

		Node* searchNode(T value)
		{
			Node*	temp = this->mRoot;

			while (temp != this->mNullNode && temp != NULL)
			{
				if (this->mComp(temp->mValue, value))
				{
					temp = temp->mRight;
				}
				else if (this->mComp(value, temp->mValue))
				{
					temp = temp->mLeft;
				}
				else
				{
					return (temp);
				}
			}
			return (NULL);
		}

		bool deleteNode(T value)
		{
			Node*	delNode = searchNode(value);
			Node*	delParent;
			Node*	temp = delNode;
			Node*	tempParent;

			if (!delNode)
			{
				return (false);
			}
			delParent = delNode->mParent;
			if (temp->mLeft != this->mNullNode)
			{
				temp = temp->mLeft;
				while (temp->mRight != this->mNullNode)
				{
					temp = temp->mRight;
				}
				tempParent = temp->mParent;
				temp->mLeft->mParent = tempParent;
				if (delNode == tempParent)
				{
					tempParent->mLeft = temp->mLeft;
				}
				else
				{
					tempParent->mRight = temp->mLeft;
				}
			}
			else if (temp->mRight != this->mNullNode)
			{
				temp = temp->mRight;
				while (temp->mLeft != this->mNullNode)
				{
					temp = temp->mLeft;
				}
				tempParent = temp->mParent;
				temp->mRight->mParent = tempParent;
				if (delNode == tempParent)
				{
					tempParent->mRight = temp->mRight;
				}
				else
				{
					tempParent->mLeft = temp->mRight;
				}
			}
			else
			{
				if (delParent && delParent->mLeft == delNode)
				{
					delParent->mLeft = this->mNullNode;
				}
				else if (delParent && delParent->mRight == delNode)
				{
					delParent->mRight = this->mNullNode;
				}
			}
			if (delNode == this->mRoot)
			{
				this->mRoot = temp;
				if (delNode == temp)
				{
					this->mRoot = NULL;
				}
				this->mNullNode->mRight = this->mRoot;
			}
			this->nodeSwap(delNode, temp);
			this->mNodeAlloc.destroy(delNode);
			this->mNodeAlloc.deallocate(delNode, 1);
			--this->mSize;
			return (true);
		}

		void nodeSwap(Node* delNode, Node* temp)
		{
			temp->mParent = delNode->mParent;
			if (delNode->mParent && delNode->mParent->mLeft == delNode)
			{
				delNode->mParent->mLeft = temp;
			}
			else if (delNode->mParent && delNode->mParent->mRight == delNode)
			{
				delNode->mParent->mRight = temp;
			}
			temp->mLeft = delNode->mLeft;
			temp->mLeft->mParent = temp;
			temp->mRight = delNode->mRight;
			temp->mRight->mParent = temp;
		}
	};
}

#endif