#include "PixelFPSServer.h"
#include "NetworkCommon.hpp"

vector<char> DataBuffer(1024 * 20);

void GrabSomeData(tcp::socket& socket)
{
    socket.async_read_some(buffer(DataBuffer.data(), DataBuffer.size()),
        [&](error_code ec, size_t length)
        {
            if (!ec)
            {
                cout << "read" << length << "bytes\n";

                for (int i = 0; i < length; i++)
                {
                    cout << DataBuffer[i];
                }

                GrabSomeData(socket);
            }
        }
    );
}

int main()
{
    cout << "Hello CMake.\n";

    error_code ec;

    io_context context;

    tcp::endpoint endPoint(make_address("93.184.216.34", ec), 80);

    tcp::socket socket(context);

    socket.connect(endPoint, ec);

    if (!ec)
    {
        cout << "Connected!\n";
    }
    else
    {
        cout << "Failed!\n" + ec.message() + "\n";
    }

    if (socket.is_open())
    {
        string request = "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(buffer(request.data(), request.size()), ec);

        //socket.wait(socket.wait_read);
        this_thread::sleep_for(2000ms);

        size_t bytes = socket.available();
        cout << "Bytes Available:" << bytes << "\n";

        if (bytes > 0)
        {
            vector<char> data_buffer(bytes);
            socket.read_some(buffer(data_buffer.data(), data_buffer.size()), ec);

            for (auto& c : data_buffer)
            {
                cout << c;
            }
        }
    }

    cin.get();
    return 0;
}
