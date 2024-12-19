#include "file_handler.hpp"

File_Writer::File_Writer(const std::string& filename): m_file(filename, std::ios_base::out | std::ios_base::trunc)
{
    if (!m_file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing");
    }
}
File_Writer::~File_Writer()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}
void File_Writer::write(const std::string& content)
{
    m_file << content;
}


File_Reader::File_Reader(const std::string& filename): m_file(filename, std::ios_base::in)
{
    if (!m_file.is_open())
    {
        throw std::runtime_error("Failed to open file for reading");
    }
}
File_Reader::~File_Reader()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}
std::string File_Reader::readAll()
{
    std::stringstream buffer;
    buffer << m_file.rdbuf();
    return buffer.str();
}