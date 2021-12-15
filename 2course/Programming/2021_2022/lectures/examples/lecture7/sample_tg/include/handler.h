#ifndef HANDLER_H_INCLUDED
#define HANDLER_H_INCLUDED

#include <random>
#include <string>

#include <tgbot/tgbot.h>

#include "media.h"

class Handler
{
public:
    Handler(Media storage) : media{storage}
    {}

    void greetings(TgBot::Bot&, TgBot::Message::Ptr&);
    void log_text(TgBot::Message::Ptr&);
    void send_gif(TgBot::Bot&, TgBot::Message::Ptr&);
    void send_wish(TgBot::Bot&, TgBot::Message::Ptr&);
    void show_help(TgBot::Bot&, TgBot::Message::Ptr&);

private:
    Media media;

    size_t random_index(size_t up_to);

    static const std::string help_message;
    static std::mt19937_64 gnr;
};

#endif // HANDLER_H_INCLUDED
