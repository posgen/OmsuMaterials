#include "media.h"

#include <cstdlib>
#include <fstream>

Media Media::from_file(std::string gifs_file, std::string wishes_file)
{
    std::ifstream gifs_io{gifs_file};
    if (!gifs_io) {
        exit(EXIT_FAILURE);
    }

    std::string line;
    Media item;
    while (std::getline(gifs_io, line)) {
        item.gifs_.push_back(line);
    }

    std::ifstream wishes_io{wishes_file};
    if (!wishes_io) {
        exit(EXIT_FAILURE);
    }

    std::string accum;
    while (getline(wishes_io, line)) {
        if ( line.find("===") == 0 ) {
            item.wishes_.push_back(accum.substr(0, accum.length() - 1));
            accum.clear();
        } else {
            accum += line + '\n';
        }
    }

    return item;
}

std::string Media::gif_url_at(size_t index)
{
    return gifs_[index];
}

std::string Media::wish_at(size_t index)
{
    return wishes_[index];
}

size_t Media::gifs_count() const
{
    return gifs_.size();
}

size_t Media::wishes_count() const
{
    return wishes_.size();
}
