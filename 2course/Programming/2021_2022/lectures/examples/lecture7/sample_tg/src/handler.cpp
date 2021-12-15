#include "handler.h"

const std::string Handler::help_message = R"(
Попробуй команды:
  /wish_for_me
  /gif_for_me
)";

std::mt19937_64 Handler::gnr{static_cast<size_t>(time(nullptr))};

void Handler::greetings(TgBot::Bot &bot, TgBot::Message::Ptr &message)
{
    if (message != nullptr && message->chat->type == TgBot::Chat::Type::Private) {
        auto user = message->from;
        std::string greet_message = "Привет, ";

        greet_message += (user->username == "") ? user->firstName : user->username + "!";
        bot.getApi().sendMessage(message->chat->id, greet_message, true, message->messageId);
    }
}

void Handler::show_help(TgBot::Bot &bot, TgBot::Message::Ptr &message)
{
    if (message != nullptr && message->chat->type == TgBot::Chat::Type::Private) {
        auto user = message->from;
        bot.getApi().sendMessage(message->chat->id, help_message, true, message->messageId);
    }
}

void Handler::send_gif(TgBot::Bot &bot, TgBot::Message::Ptr &message)
{
    if (message != nullptr && message->chat->type == TgBot::Chat::Type::Private) {
        static const size_t gifs_count = media.gifs_count();

        if (gifs_count > 0) {
            auto user = message->from;
            const size_t index = random_index(gifs_count);
            const std::string gif_link = media.gif_url_at(index);

            std::cout << "gif link: " << gif_link << std::endl;

            bot.getApi().sendAnimation(message->chat->id, gif_link, 0, 0, 0, "", "", message->messageId);
        }
    }
}

void Handler::send_wish(TgBot::Bot &bot, TgBot::Message::Ptr &message)
{
    if (message != nullptr && message->chat->type == TgBot::Chat::Type::Private) {
        static const size_t wishes_count = media.wishes_count();

        if (wishes_count > 0) {
            auto user = message->from;
            const size_t index = random_index(wishes_count);
            const std::string wish = media.wish_at(index);

            bot.getApi().sendMessage(message->chat->id, wish, true, message->messageId);
        }
    }
}

void Handler::log_text(TgBot::Message::Ptr &message)
{
    if (message != nullptr && message->chat->type == TgBot::Chat::Type::Private) {
        const std::string msg_text = message->text;

        if (msg_text != "") {
            auto user = message->from;
            const std::string uname = (user->username == "") ? user->firstName : user->username;
            std::cout << "Пользователь <<" << uname << ">> написал:\n" << msg_text << std::endl << std::endl;
        }
    }
}

size_t Handler::random_index(size_t up_to)
{
    const static auto max_rnd = gnr.max();
    size_t right_bound = up_to == 0 ? 0 : up_to - 1;

    return right_bound * (double(gnr()) / max_rnd);
}
