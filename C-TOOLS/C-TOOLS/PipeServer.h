#pragma once
#include <Windows.h> 
#include <string>
#include <iostream>
#include <queue>
#include <utility>
#include <thread>

#define WAIT_CLIENT_TIMEOUT  1000*60*10    //--10min
constexpr auto BUFFER_SIZE = 1024 * 5;        //--5k;

typedef struct
{
	const char* _name;
	DWORD _openMode;
	DWORD _pipeMode;
	DWORD _maxInstances;
	DWORD _outBufferSize;
	DWORD _inBufferSize;
	DWORD _dfaultTimeOut;
	LPSECURITY_ATTRIBUTES _pSecurityAttributes;
}SpipeParam;


typedef std::pair<char*, DWORD> MsgItem;

class PipeServer {
public:
	PipeServer(const SpipeParam &_param);
	//bool Connect();   
	//bool Listen();
	bool Dispose();
	bool ConnectNew();
	bool Recv();
	bool Send(MsgItem oneMsg);
	~PipeServer() {}

private:
	HANDLE m_hPipe;
	SpipeParam m_pipeParam;
	size_t m_iInstanceCount;
	bool m_bConnected;
	std::queue<MsgItem> m_msgQueue;
};