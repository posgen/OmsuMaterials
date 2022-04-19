/**
    !!!
    Пока только исходный код. Примеры, комментарии,
    инструкции для сборки будут добавлены попозже.
    !!!
*/

#include <csignal>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <random>
#include <string>

#include <tgbot/tgbot.h>

#include "handler.h"
#include "media.h"

int main()
{
    using namespace std;
    using namespace TgBot;

    string token(getenv("TOKEN"));

    Bot bot(token);
    auto storage = Media::from_file("gifs_links.dat", "wishes.txt");
    Handler handler{storage};

    bot.getEvents().onCommand("start", [&bot, &handler](Message::Ptr message) {
        handler.greetings(bot, message);
    });

    bot.getEvents().onCommand("help", [&bot, &handler](Message::Ptr message) {
        handler.show_help(bot, message);
    });

    bot.getEvents().onCommand("gif_for_me", [&bot, &handler](Message::Ptr message) {
        handler.send_gif(bot, message);
    });

    bot.getEvents().onCommand("wish_for_me", [&bot, &handler](Message::Ptr message) {
        handler.send_wish(bot, message);
    });

    bot.getEvents().onAnyMessage([&bot, &handler](Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/")) {
            return;
        }

        handler.log_text(message);
    });

    signal(SIGINT, [](int s) {
        cerr << "SIGINT got, code: " << s << endl;;
        exit(EXIT_SUCCESS);
    });

    try {
        cout << "Started successfully, working now..." << endl;
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (exception& e) {
        cerr << "error: " << e.what() << endl;
    }
}
