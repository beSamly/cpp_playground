//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <thread>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

using asio::ip::tcp;
using std::shared_ptr;
using std::vector;
using std::make_shared;

class session
    : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket)
        : socket_(std::move(socket))
    {
    }

    ~session()
    {
        std::cout << "Session deconstructor " << std::endl;
    }

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(asio::buffer(data_, max_length),
            [this, self](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    std::thread::id this_id = std::this_thread::get_id();
                    std::cout << "thread id is " << this_id << std::endl;
                    do_read();
                }
                else {
                    std::cout << "Disconnection or error??" << std::endl;
                }
            });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        asio::async_write(socket_, asio::buffer(data_, length),
            [this, self](std::error_code ec, std::size_t /*length*/)
            {
                if (!ec)
                {
                    do_read();
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class server
{
public:
    server(asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
        socket_(io_context)
    {
        do_accept();
    }

public:
    void do_accept()
    {
        acceptor_.async_accept(socket_,
            [this](std::error_code ec)
            {
                if (!ec)
                {
                    shared_ptr<session> s = make_shared<session>(std::move(socket_));
                    s->start();
                    sessionVector.push_back(s);
                }

                do_accept();
            });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    vector<shared_ptr<session>> sessionVector;
};

int main(int argc, char* argv[])
{
    try
    {
        std::vector<std::thread> threads;

        asio::io_context io_context;

        server s(io_context, 7777);

        for (int n = 0; n < 4; ++n)
        {
            threads.emplace_back([&]
                {
                    //s.do_accept();
                    io_context.run();

                });
        }

        for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}