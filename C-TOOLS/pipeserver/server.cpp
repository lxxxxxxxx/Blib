#include "PipeServer.h"

#define PIPE_NAME  "\\\\.\\pipe\\test-pipe_adsfjafas1d6fasd5f5"



int main()
{
	SpipeParam pipeParam{
		PIPE_NAME,// pipe name 
		PIPE_ACCESS_DUPLEX| FILE_FLAG_OVERLAPPED,       // read/write access 
		PIPE_TYPE_MESSAGE |       // message type pipe 
		PIPE_READMODE_MESSAGE |   // message-read mode 
		PIPE_WAIT,                // blocking mode 
		PIPE_UNLIMITED_INSTANCES, // max. instances  
		BUFFER_SIZE,                  // output buffer size 
		BUFFER_SIZE,                  // input buffer size 
		0,                        // client time-out 
		NULL
	};


	PipeServer server(pipeParam);
	if (server.ConnectNew())
	{
		server.Recv();
		server.Dispose();
		while (1)
		{
			std::string msg;
			std::cout << "-----input msg:";
			std::cin >> msg;
			if (msg == "quit")
			{
				return 0;
			}
			std::cout << "-----send msg:" << msg << std::endl;
			server.Send({ const_cast<char*>(msg.c_str()),msg.size() });
		}
	}

	return 0;
}