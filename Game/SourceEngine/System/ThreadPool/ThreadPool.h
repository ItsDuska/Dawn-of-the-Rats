#pragma once

#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <iostream>


class ThreadPool
{
public:
	using Task = std::function<void()>;

	explicit ThreadPool();
	~ThreadPool();

	void enqueue(Task task);

private:
	std::vector<std::thread> _Threads;
	std::condition_variable _EventVar;
	std::mutex _EventMutex;
	std::queue<Task> _tasks;
	unsigned int NUMBER_OF_ALLOWED_THREADS;

	bool _stopping = false;

	void start();
	void stop() noexcept;
};
