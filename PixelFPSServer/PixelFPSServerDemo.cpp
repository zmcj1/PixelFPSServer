#include "PixelFPSServer.h"

int main(int argc, char** argv)
{
    try
    {
        error_code ec;

        asio::io_context context;

        int port = 17971;
        if (argc == 2)
        {
            port = stoi(string(argv[1]));
        }

        tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), port));
        //tcp::acceptor acceptor(context, tcp::endpoint(make_address("127.0.0.1", ec), port));

        cout << "Server open.\n";

        while (true)
        {
            tcp::socket socket(context);
            acceptor.accept(socket);

            cout << "received client!\n";

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