﻿#include "PixelFPSServer.h"

int main(int argc, char** argv)
{
    try
    {
        error_code ec;

        asio::io_context context;

        tcp::acceptor acceptor(context, tcp::endpoint(make_address("124.70.1.25", ec), 22));

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