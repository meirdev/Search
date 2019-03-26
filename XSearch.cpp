#include "XSearch.h"
#include "Runnable/Search.h"
#include "Runnable/File.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/Local/LocalFile.h"
#include "FileSystem/Local/LocalDirectory.h"
#include "Search/RegularSearch/RegularSearch.h"
#include "Search/RegexSearch/RegexSearch.h"
#include "Style/Ack/Ack.h"

XSearch::XSearch()
{
}

XSearch::~XSearch()
{
    m_config.m_threadPool.shutdown(true);
}

void XSearch::setStyle(const std::string& _style)
{
    m_config.m_style = nullptr;

    if (_style == "ack")
    {
        m_config.m_style = new Ack;
    }
}

void XSearch::setSearchEngine(const std::string& _engine)
{
    m_config.m_searchEngine = nullptr;

    if (_engine == "regular")
    {
        m_config.m_searchEngine = new RegularSearch;
    }
    else if (_engine == "regex")
    {
        m_config.m_searchEngine = new RegexSearch;
    }
}

void XSearch::setFileSystem(const std::string& _fileSystem)
{
    m_config.m_fileSystem = nullptr;

    if (_fileSystem == "local")
    {
        m_config.m_fileSystem = new FileSystem<LocalDirectory, LocalFile>();
    }
}

void XSearch::setContextLine(size_t _before, size_t _after)
{
    m_config.m_beforeContext = _before;
    m_config.m_afterContext  = _after;
}

void XSearch::setCaseSensitive(bool _state)
{
    m_config.m_searchEngine->setCaseSensitive(_state);
}

void XSearch::start(const std::string& _term, const std::string& _dir)
{
    Search::m_config = File::m_config = &m_config;
    
    Search(_term, _dir).run();
}