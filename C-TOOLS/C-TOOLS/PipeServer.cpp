#include "PipeServer.h"

PipeServer::PipeServer(const SpipeParam &_param)
	:m_hPipe(NULL),m_pipeParam(_param), m_iInstanceCount(0)
{

}

//bool PipeServer::Connect()
//{
//	if (NULL == m_pipeParam._name)
//	{
//		return false;
//	}
//	while (true)
//	{
//
//	}
//
//}

bool PipeServer::ConnectNew()
{
	if (NULL == m_pipeParam._name)
	{
		return false;
	}
	m_hPipe = CreateNamedPipeA(
		m_pipeParam._name,
		m_pipeParam._openMode,
		m_pipeParam._pipeMode,
		m_pipeParam._maxInstances,
		m_pipeParam._outBufferSize,
		m_pipeParam._inBufferSize,
		m_pipeParam._dfaultTimeOut,
		m_pipeParam._pSecurityAttributes
	);

	//--Create namedpipe failed.
	if ((!m_hPipe) || (INVALID_HANDLE_VALUE == m_hPipe))
	{
		std::cout << "create named pipe failed.." << std::endl;
		return false;
	}

	//--wait for client to connect
	std::cout << "waiting for connect" << std::endl;
	OVERLAPPED ov;
	memset(&ov, 0, sizeof(OVERLAPPED));
	ov.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	bool res = ConnectNamedPipe(m_hPipe, &ov);
	if (!res)
	{
		switch (GetLastError())
		{
		case ERROR_PIPE_CONNECTED:
			std::cout << "connected." << std::endl;
			m_bConnected = true;
			return true;
		case ERROR_IO_PENDING:
			std::cout << "pipe io pending." << std::endl;
			switch (WaitForSingleObject(ov.hEvent, WAIT_CLIENT_TIMEOUT))
			{
			case WAIT_OBJECT_0:
				std::cout << "connected." << std::endl;
				m_bConnected = true;
				return true;
			case WAIT_TIMEOUT:
				std::cout << "wait for client connect timeout for " << WAIT_CLIENT_TIMEOUT << "ms.." << std::endl;
				m_bConnected = false;
				return false;
			case WAIT_FAILED:
				std::cout << "wait for client connect failed,error code: " << GetLastError() << std::endl;
				m_bConnected = false;
				return false;
			}
		case ERROR_NO_DATA:
			std::cout << "pipe close by client,disconnect it.." << std::endl;
			DisconnectNamedPipe(m_hPipe);
			m_hPipe = NULL;
			return false;
		}
	}
	else
	{
		std::cout << "pipe connect failed....." << std::endl;
	}
}


//bool PipeServer::Listen()
//{
//
//}



bool PipeServer::Recv()
{
	std::thread proc([this]() {
		while (m_bConnected&&m_hPipe)
		{
			char buf[BUFFER_SIZE] = { 0 };
			DWORD readBytes;
			//--TODO:VOERLAPPED
			OVERLAPPED ov;
			memset(&ov, 0, sizeof(OVERLAPPED));
			ov.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
			BOOL res = ReadFile(m_hPipe, buf, BUFFER_SIZE, &readBytes, &ov);
			if (!res)
			{
				switch (GetLastError())
				{
				case ERROR_IO_PENDING:
					switch (WaitForSingleObject(ov.hEvent, INFINITE))
					{
					case WAIT_OBJECT_0:
						GetOverlappedResult(m_hPipe, &ov, &readBytes, FALSE);
						if (readBytes != 0)
						{
							char *pBuf = new char[readBytes];
							m_msgQueue.push(std::make_pair(pBuf, readBytes));
						}
						else
						{
							std::cout << "read pipe readBytes==0." << std::endl;
						}
						break;
					case WAIT_FAILED:
						std::cout << "wait read event failed with a unexpect error,error code:" << GetLastError() << std::endl;
						break;
					default:
						std::cout << "wait read event default." << std::endl;
						break;
					}
					break;
				case ERROR_BROKEN_PIPE:
					std::cout << "read pipe failed because pipe broken."<< std::endl;
					break;
				default:
					std::cout<<"read pipe failed..." << GetLastError() << std::endl;
					break;
				}
			}
			else if (readBytes != 0)
			{
				char *pBuf = new char[readBytes];
				m_msgQueue.push(std::make_pair(pBuf, readBytes));
			}
			else
			{
				if (ERROR_BROKEN_PIPE == GetLastError())
				{
					std::cout << "read pipe failed,becouse pipe is broken.." << std::endl;
				}
				else
				{
					std::cout << "read pipe failed with a unexpected error,error code:" << GetLastError() << std::endl;
				}
			}
		}
	});
	proc.detach();
	return true;
}

bool PipeServer::Dispose()
{
	std::thread proc([this]() {
		while (true)
		{
			if (!m_msgQueue.empty())
			{
				MsgItem oneMsg = m_msgQueue.front();
				m_msgQueue.pop();
				std::cout << "\n-----recv message: " << std::string(oneMsg.first, oneMsg.second) << std::endl;
				if (oneMsg.first)
				{
					delete[]oneMsg.first;
					oneMsg.first = nullptr;
				}
			}
			else
			{
				Sleep(100);
			}
		}});
	proc.detach();
	return true;
}

bool PipeServer::Send(MsgItem oneMsg)
{
	DWORD writeBytes;
	if (m_bConnected&&m_hPipe)
	{
		bool res = WriteFile(m_hPipe, oneMsg.first, oneMsg.second, &writeBytes, NULL);
		if (!res || writeBytes != oneMsg.second)
		{
			std::cout << "write pipe failed,error code:" << GetLastError() << std::endl;
			return false;
		}
		return true;
	}
	std::cout << "write pipe failed,pipe not connect.." << std::endl;
	return false;
}

