#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

//asio lib
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

//platform API
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif