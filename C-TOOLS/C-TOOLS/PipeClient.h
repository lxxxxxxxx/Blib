#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <queue>
#include <utility>
#include <thread>


#define WAIT_PIPE_TIMEOUT  1000*20    //--10min
#define BUFFER_SIZE            1024*5        //--5k


typedef struct
{
	const char* _fileName;
	DWORD _desiredAccess;
	DWORD _shareMode;
	LPSECURITY_ATTRIBUTES _securityAttributes;
	DWORD _creationDisposition;
	DWORD _flagsAndAttributes;
	HANDLE _templateFile;
}CpipeParma;

typedef std::pair<char*, DWORD> MsgItem;
class PipeClient {
public:
	PipeClient(CpipeParma _pipePrama);
	bool Connect();
	bool Recv();
	bool Dispose();
	bool Send(MsgItem oneMsg);
	~PipeClient(){}

private:
	HANDLE m_hPipe;
	CpipeParma m_pipeParma;
	bool m_bConnected;
	std::queue<MsgItem> m_msgQueue;
};