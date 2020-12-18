#pragma once

#include <thread>
#include <string>
#include <atomic>


class CThread 
{
public:
	CThread(std::string name);
	virtual  ~CThread();
	bool Run();
	bool Quit();
	bool Looping();

protected:
	virtual void Running();

private:
	void ThreadFunc();

private:
	std::string m_name;
	std::thread::id m_id;
	std::atomic_bool m_exit;
};



