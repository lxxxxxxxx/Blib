/*
* file PipeServer.h
* Windows namedpipe server class.
*/

#include <string>
#include <stdint.h>

#define PIPE_DEFAULT_MAGIC 0x1a2b3c4d

typedef void (*ReadCompleteFunc)(uint8_t *data, uint32_t size);
typedef void (*WriteCompleteFunc)(uint32_t real);

namespace Blib
{
    typedef struct _PipeMsgHead
    {
        uint32_t magic;
        uint32_t size;
        uint8_t data[0];
    } PipeMsgHead;

    class WPipeServer
    {
    public:
        WPipeServer(std::string name, int maxIns);

        ~WPipeServer();

        void ListenAndServe();

        void Register(ReadCompleteFunc r, WriteCompleteFunc w);

        bool Write(uint8_t *data, uint32_t size);

    private:
        std::string m_name;
        int m_maxIns;
    };
} // namespace Blib