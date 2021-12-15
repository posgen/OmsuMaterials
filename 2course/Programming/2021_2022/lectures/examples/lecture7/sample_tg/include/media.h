#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include <string>
#include <vector>

using StringArray = std::vector<std::string>;

class Media
{
public:
    static Media from_file(std::string gifs_file, std::string wishes_file);

    std::string gif_url_at(size_t index);
    std::string wish_at(size_t index);

    size_t gifs_count() const;
    size_t wishes_count() const;

private:
    StringArray gifs_, wishes_;
};

#endif // MEDIA_H_INCLUDED
