#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {
	template <typename value_type, typename const_value_type, bool is_const = false>
	class typeSelector {
		public:
			typedef value_type				type;
	};

	template <typename value_type, typename const_value_type>
	class typeSelector<value_type, const_value_type, true> {
		public:
			typedef const_value_type		type;
	};

	
};

#endif