#pragma once
#include <SFML/System/Mutex.hpp>

class ThreadHandler
{
private:
	sf::Mutex mutex;
	int numberOfActiveThreads = 0;
	ThreadHandler() {}

	int IgetNumberOfActiveThreads()
	{
		return numberOfActiveThreads;
	}

	void IsetNumberOfActiveThreads(int num)
	{
		numberOfActiveThreads += num;
	}

	sf::Mutex& IgetMutex()
	{
		return mutex;
	}

public:
	ThreadHandler(const ThreadHandler&) = delete;
	static ThreadHandler& get()
	{
		static ThreadHandler instance;
		return instance;
	}

	static int getNumberOfActiveThreads()
	{
		return get().IgetNumberOfActiveThreads();
	}

	static void setNumberOfActiveThreads(int num)
	{
		get().IsetNumberOfActiveThreads(num);
	}
	
	static sf::Mutex& getMutex()
	{
		return get().IgetMutex();
	}
};
