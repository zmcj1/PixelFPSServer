#include "PixelFPSServer.h"

int main()
{
    try
    {
        asio::io_context context;

        tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 17971));

        cout << "Server open.\n";

        while (true)
        {
            tcp::socket socket(context);
            acceptor.accept(socket);

            string msg = "Hello Client!";

            error_code ec;
            write(socket, buffer(msg), ec);
        }
    }
    catch (exception& e)
    {
        cout << e.what() << "\n";
    }

    return 0;
}