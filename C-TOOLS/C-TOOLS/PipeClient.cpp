
#include "PipeClient.h"



PipeClient::PipeClient(CpipeParma _pipeParma):
	m_hPipe(NULL),m_pipeParma(_pipeParma)
{
}


bool PipeClient::Connect()
{
	int trytimes = 10;  //try to connect for 10 times
	for(int i=0;i<trytimes;i++)
	{
		m_hPipe = CreateFileA(
			m_pipeParma._fileName,
			m_pipeParma._desiredAccess,
			m_pipeParma._shareMode,
			m_pipeParma._securityAttributes,
			m_pipeParma._creationDisposition,
			m_pipeParma._flagsAndAttributes,
			m_pipeParma._templateFile
		);
		if (INVALID_HANDLE_VALUE != m_hPipe)
		{
			std::cout << "pipe create success."<< std::endl;
			m_bConnected = true;
			return true;
		}
		if (ERROR_PIPE_BUSY == GetLastError())
		{
			std::cout << "create pipe failed,pipe busy,error code:" << GetLastError() << std::endl;
			continue;
		}
		if (!WaitNamedPipeA(m_pipeParma._fileName, WAIT_PIPE_TIMEOUT))
		{
			continue;
		}
	}
	return false;
}

bool PipeClient::Recv()
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
				if (ERROR_IO_PENDING == GetLastError())
				{
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

				}
				else
				{
					std::cout << "read pipe failed..." << GetLastError() << std::endl;
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

bool PipeClient::Dispose()
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

bool PipeClient::Send(MsgItem oneMsg)
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