/** 
*  @file    TransportLayer.hpp
*  @author  GRI Team
*  @date    06/22/2017  
*  @version 1.0 
*  @brief ...
*/


#ifndef TRANSPORTLAYER_HPP
#define TRANSPORTLAYER_HPP

#include <string>
#include <list>
#include <memory>
#include <iterator>
#include <mutex>

#include "WordExtractor.hpp"

/**
*  @brief ....  
*/
class TransportLayer
{
public:
	using String = std::string;
	using Message = std::shared_ptr<String>;
	using Messages = std::list<Message>;


        /**
        *  @brief .....
        */
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

	void processMessage();
	void clear();

	size_t getBufferSize() const; 
	char* getBuffer();

	void setEnd(const int, const char = '\0');

private:
	void processMessageHelper(char*);

	Messages messages_;
	WordExtractor wordExtractor_;
	static const size_t bufferSize = 2048;
	char buffer[bufferSize];

	std::mutex mutex;
};


#endif
