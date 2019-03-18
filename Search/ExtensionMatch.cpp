#include <algorithm>
#include <string.h>

#include "Search/ExtensionMatch.h"

static std::string toLower(std::string _string)
{
    for (auto& i : _string)
    {
        i = static_cast<char>(tolower(i));
    }

    return _string;
}

bool ExtensionMatch::match(const std::string& _filename)
{
    size_t index = _filename.find_last_of('.');

    if (index == std::string::npos || index+1 == _filename.size())
    {
        return false;
    }

    std::string extension = _filename.substr(index+1);

    auto begin = m_extensions.begin();
    auto end   = m_extensions.end();

    auto result = std::find(begin, end, toLower(extension));

    return result != end;
}

void ExtensionMatch::add(const std::string& _extension)
{
    m_extensions.push_back(_extension);
}