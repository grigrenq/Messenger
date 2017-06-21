#ifndef TRANSPORTLAYER_HPP
#define TRANSPORTLAYER_HPP

#include <string>
#include <list>
#include <memory>
#include <iterator>

#include "ExtractWord.hpp"

class TransportLayer
{
public:
	using String = std::string;
	using Message = std::shared_ptr<String>;
	using Messages = std::list<Message>;


	class Iterator
	{
	public:
		using Iter = Messages::iterator;
		using value_type = std::iterator_traits<Iter>::value_type;

		Iterator() {}
		Iterator(const Iter& it)
			: iter(it) {}

		void operator++()
		{
			++iter;
		}

		value_type& operator*()
		{
			return *iter;
		}

		bool operator==(const Iterator& it) 
		{
			return iter == it.iter;
		}

		bool operator!=(const Iterator& it)
		{
			return !(this->operator==(it));
		}

	private:
		Iter  iter;
	};

	Iterator begin();
	Iterator end();

	void processMessage(char*);
	void clear();
private:
	 Messages messages_;
	 ExtractWord extractWord_;
};


#endif