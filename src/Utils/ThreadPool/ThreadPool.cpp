#include "ThreadPool.h"

ThreadPool::ThreadPool()
	: NUMBER_OF_ALLOWED_THREADS(std::thread::hardware_concurrency() / 2)
{
	std::cout << "\nUsing " << this->NUMBER_OF_ALLOWED_THREADS << " threads for the application.\n";
	this->start();
}

ThreadPool::~ThreadPool()
{
	this->stop();
}

void ThreadPool::enqueue(Task task)
{
	{
		std::unique_lock<std::mutex> lock{ this->_EventMutex };
		this->_tasks.emplace(std::move(task));
	}

	this->_EventVar.notify_one();
}

void ThreadPool::start()
{
	for (auto i = 0u; i < this->NUMBER_OF_ALLOWED_THREADS; ++i)
	{
		this->_Threads.emplace_back([=] {
			while (true)
			{
				Task task;

				{
					std::unique_lock<std::mutex> lock{ this->_EventMutex };

					this->_EventVar.wait(lock, [=] 
						{ 
							return this->_stopping || !this->_tasks.empty();
						}
					);

					if (this->_stopping && this->_tasks.empty())
					{
						break;
					}

					task = std::move(this->_tasks.front());
					this->_tasks.pop();
				}

				task();
			}
		});
	}
}

void ThreadPool::stop() noexcept
{
	{
		std::unique_lock<std::mutex> lock{ this->_EventMutex };
		this->_stopping = true;
	}

	this->_EventVar.notify_all();

	for (auto& thread : this->_Threads)
	{
		thread.join();
	}
}
