#ifndef CONT_VECTOR_HPP
# define CONT_VECTOR_HPP

# include "utils.hpp"
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector 
	{

	public:
		typedef 			T												value_type;
		typedef				Alloc											allocator_type;
		typedef typename	allocator_type::reference						reference;
		typedef typename	allocator_type::const_reference					const_reference;
		typedef typename	allocator_type::pointer							pointer;
		typedef typename	allocator_type::const_pointer					const_pointer;
		typedef typename	ft::vector_iterator<value_type>					iterator;
		typedef typename	ft::vector_iterator<const value_type>			const_iterator;
		typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef 			size_t											size_type;

		/*			VECTOR
		
		private:
			pointer			_data;
			size_t			_size;
			size_t			_capacity;
			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity_end;

		public:
			vector()
			vector(size_t count, value_type value)
			template <class InputIterator>
        	vector (InputIterator first, InputIterator last, const allocator_type& alloc)
			vector(const vector& x)
			virtual ~vector;
			
			vector&			operator=(const vector& x)
			
			reference		operator[](size_type n)
			reference		at(size_type n)

			void			push_back(const value_type& value)
			void			pop_back()

			void			insert(iterator position, size_type n, const value_type& val)
			iterator		insert(iterator position, const value_type& val)
			void			insert(iterator position, InputIterator first, InputIterator last)
			
			iterator		erase(iterator position)
			iterator		erase(iterator first, iterator last)
			
			void			swap(vector<T>& x)
			
			reference		front()
			const_reference	front() const
			reference		back()
			const_reference	back() const

			size_type				size() const
			size_type				capacity() const
			size_type				max_size() const
			bool					empty() const

			void					reserve(size_type n)
			void					resize(size_type n, value_type value = value_type())

			void					assign(size_type n, const value_type& val)
			void					assign(InputIterator first, InputIterator last)

			iterator				begin()
			iterator				end()
			const_iterator			begin() const
			const_iterator			end() const
			reverse_iterator		rbegin()
			reverse_iterator		rend()
			const_reverse_iterator	rbegin() const
			const_reverse_iterator	rend() const

			void					clear()
			allocator_type			get_allocator() const
			*/


	private:
		pointer			_data;
		size_t			_size;
		size_t			_capacity;
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_capacity_end;
		
		
		void			reallocate(size_t n = 0)
		{
			size_t		count_to_allocate;
			pointer		tmp;

			if (_capacity == 0)
				count_to_allocate = 1;
			else if (n)
				count_to_allocate = n;
			else
				count_to_allocate = _capacity * 2;
			tmp = _data;
			if (!(_data = _alloc.allocate(count_to_allocate)))
				throw std::bad_alloc();
			for (size_t i = 0; i < _size; ++i)
			{
				_alloc.construct(&_data[i], tmp[i]);
				_alloc.destroy(&tmp[i]);
			}
			_alloc.deallocate(tmp, _capacity);
			_capacity = count_to_allocate;
		}

	public:
		vector() : _data(NULL), _size(0), _capacity(0), _alloc(allocator_type()), _begin(0), _end(0) {}
		vector(size_t count, value_type value = value_type()) : _data(0), _size(count), _capacity(count), _alloc(allocator_type())
		{
			if (!(_data = _alloc.allocate(count)))
				throw std::bad_alloc();
			for (unsigned int i = 0; i < count; ++i)
				_alloc.construct(&_data[i], value);
			_end = _begin + _size;
		}
		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		: _data(0), _size(0), _capacity(0), _alloc(alloc), _begin(0), _end(0)
		{
			insert(begin(), first, last);
		};
		vector(const vector& x)
		: _data(0), _size(0), _capacity(0), _alloc(allocator_type()), _begin(0), _end(0)
		{
			insert(begin(), x.begin(), x.end());
		}
		virtual ~vector() {}

		vector&			operator=(const vector& x)
		{
			clear();
			insert(x.begin(), x.end());
		}

		void			push_back(const value_type& value)
		{
			if (_size == _capacity)
				this->reallocate();
			_alloc.construct(&_data[_size++], value);
			_begin = _data;
			_end = _begin + _size;
			_capacity_end = _begin + _capacity;
		}

		void			pop_back()
		{
			_alloc.destroy(&_data[--_size]);
			--_end;
		}

		void			insert(iterator position, size_type n, const value_type& val)
		{
			if (!n)
				return ;
			if (_capacity < _size + n)
			{
				size_type	count_to_allocate = _size + n > _capacity * 2 ? _size + n : _capacity * 2;
				pointer		new_data = _alloc.allocate(count_to_allocate);
				iterator	it = begin();
				size_type	i;

				for (i = 0; it != position; ++i)
					_alloc.construct(new_data + i, *it++);
				for (size_type j = 0; j < n; ++j)
					_alloc.construct(new_data + i++, val);
				for (; it != end(); ++i)
					_alloc.construct(new_data + i, *it++);
				for (size_type j = 0; j < _size; ++j)
					_alloc.destroy(_data + j);
				_data = new_data;
				_size += n;
				_capacity = count_to_allocate;
				_begin = _data;
				_end = _data + _size;
				_capacity_end = _data + _capacity;
			}
			else
			{
				size_type	tail_size = end() - position;
				value_type	tmp[tail_size];
				iterator	tail = position;
				
				for (size_type i = 0; tail != end(); ++i)
					_alloc.construct(&tmp[i], *tail++);
				for (size_type i = 0; i < n; ++i)
				{
					_alloc.destroy(&*position);
					_alloc.construct(&*position++, val);
				}
				for (size_type	i = 0; i < tail_size; ++i)
				{
					_alloc.construct(&*position++, tmp[i]);
					_alloc.destroy(tmp + i);
				}
				_size += n;
				_end += n;
			}
		}


		iterator		insert(iterator position, const value_type& val)
		{
			size_type	pos = position - begin();
			insert(position, 1, val);
			return begin() + pos;
		}

		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last)
		{
			if (first == last)
				return ;
			size_type	n = ft::distance(first, last);
			if (_capacity < _size + n)
			{
				size_type	count_to_allocate = _size + n > _capacity * 2 ? _size + n : _capacity * 2;
				pointer		new_data = _alloc.allocate(count_to_allocate);
				iterator	it = begin();
				size_type	i;

				for (i = 0; it != position; ++i)
					_alloc.construct(new_data + i, *it++);
				for (size_type j = 0; j < n; ++j)
					_alloc.construct(new_data + i++, *first++);
				for (; it != end(); ++i)
					_alloc.construct(new_data + i, *it++);
				for (size_type j = 0; j < _size; ++j)
					_alloc.destroy(_data + j);
				_data = new_data;
				_size += n;
				_capacity = count_to_allocate;
				_begin = _data;
				_end = _data + _size;
				_capacity_end = _data + _capacity;
			}
			else
			{
				size_type	tail_size = end() - position;
				value_type	tmp[tail_size];
				iterator	tail = position;
				
				for (size_type i = 0; tail != end(); ++i)
					_alloc.construct(&tmp[i], *tail++);
				for (size_type i = 0; first != last; ++i)
				{
					_alloc.destroy(&*position);
					_alloc.construct(&*position++, *first++);
				}
				for (size_type i = 0; i < tail_size; ++i)
				{
					_alloc.construct(&*position++, tmp[i]);
					_alloc.destroy(tmp + i);
				}
				_size += n;
				_end += n;
			}
		}

		iterator		erase(iterator position)
		{
			iterator	res = position;
			iterator	it = _begin;
			while (it != _end && it != position)
				++it;
			_alloc.destroy(&*it);
			while (it != end())
				*it = *(it++);
			--_size;
			--_end;
			return res;			
		}

		iterator		erase(iterator first, iterator last)
		{
			iterator	res = first;
			size_type	n = ft::distance(first, last);

			for (iterator it = first; it != last; ++it)
				_alloc.destroy(&*it);
			for (iterator it = last; it != end(); ++it)
				_alloc.construct(&*first++, *it);
			_size -= n;
			_end = _begin + _size;
			return res;
		}

		void			swap(vector<T>& x)
		{
			ft::swap(&_data, &x._data);
			ft::swap(&_size, &x._size);
			ft::swap(&_begin, &x._begin);
			ft::swap(&_end, &x._end);
			ft::swap(&_capacity, &x._capacity);
			ft::swap(&_capacity_end, &x._capacity_end);
			ft::swap(&_alloc, &x._alloc);
		}

		reference		operator[](size_type n) {return _data[n];};
		reference		front() {return *_data;};
		const_reference	front() const {return *_data;};
		reference		back() {return *(_end - 1);};
		const_reference	back() const {return *(_end - 1);};
		reference		at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("ft::vector: out of range");
			else
				return *(_data + n);
		}

		size_type				size() const {return _size;};
		size_type				capacity() const {return _capacity;};
		size_type				max_size() const {return _alloc.max_size();};
		bool					empty() const {return begin() == end();};
		void					reserve(size_type n)
		{
			if (n > _capacity)
			{
				reallocate(n);
				_begin = _data;
				_end = _begin + _size;
				_capacity = n;
				_capacity_end = _begin + _capacity;
			}
		}

		void					resize(size_type n, value_type value = value_type())
		{
			if (n > _capacity)
			{
				this->reallocate(n > _capacity * 2 ? n : 0);
				while (_size < n)
					_alloc.construct(&_data[_size++], value);
			}
			else if (n > _size)
			{
				while (_size < n)
					_alloc.construct(&_data[_size++], value);
			}
			else
			{
				while (_size > n)
					_alloc.destroy(&_data[_size-- - 1]);
			}
			_begin = _data;
			_end = _begin + _size;
			_capacity_end = _begin + _capacity;
			
		}

		iterator				begin() {return this->_begin;};
		iterator				end() {return this->_end;};
		const_iterator			begin() const {return this->_begin;};
		const_iterator			end() const {return this->_end;};
		reverse_iterator		rbegin() {return reverse_iterator(end() - 1);};
		reverse_iterator		rend() {return reverse_iterator(begin() - 1);};
		const_reverse_iterator	rbegin() const {return reverse_iterator(end() - 1);};
		const_reverse_iterator	rend() const {return reverse_iterator(begin() - 1);};

		void					assign(size_type n, const value_type& val)
		{
			if (_capacity < n)
			{
				reserve(n);
				while (_size)
					_alloc.destroy(&_data[_size-- - 1]);
				while (_size < n)
					_alloc.construct(&_data[_size++], val);
			}
			else if (_size > n)
			{
				for (size_t i = 0; i < _size; ++i)
				{
					_alloc.destroy(&_data[i]);
					if (i < n)
						_alloc.construct(&_data[i], val);
				}
			}
			else
			{
				for (size_t i = 0; i < n; ++i)
				{
					if (i < _size)
						_alloc.destroy(&_data[i]);
					_alloc.construct(&_data[i], val);
				}
			}
			_size = n;
			_end = _begin + _size;
		}

		template <class InputIterator>
		void	assign(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type first, InputIterator last)
		{
			size_type	n = ft::distance(first, last);
			if (_capacity < n)
				reserve(n);
			for (size_type i = 0; first != last; ++i)
			{
				if (i < _size)
					_alloc.destroy(&_data[i]);
				_alloc.construct(&_data[i], *first++);
			}
			for (size_type i = _size; i < n; ++i)
				_alloc.destroy(&_data[i]);
			_size = n;
			_end = _begin + _size;
		}

		void	clear()
		{
			while (_size)
				pop_back();
		}

		allocator_type	get_allocator() const
		{
			return _alloc;
		}
	};

	template <class T, class Alloc>
	bool				operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template <class T, class Alloc>
	bool				operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};
	
	template <class T, class Alloc>
	bool				operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class T, class Alloc>
	bool				operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};

	template <class T, class Alloc>
	bool				operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};

	template <class T, class Alloc>
	bool				operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
};

#endif
