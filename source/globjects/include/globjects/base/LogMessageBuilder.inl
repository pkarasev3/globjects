
#pragma once


namespace globjects
{


template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(const T * pointer)
{
    return *this << static_cast<const void*>(pointer);
}

template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::vector<T> & vector)
{
    *this << "vector(";
    for (size_t i = 0; i < vector.size(); ++i)
    {
        *this << vector[i];
        if (i < vector.size()-1)
            *this << ", ";
    }
    *this << ")";

    return *this;
}

template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::vector<T *> & vector)
{
    *this << "vector(";
    for (size_t i = 0; i < vector.size(); ++i)
    {
        *this << vector[i];
        if (i < vector.size()-1)
            *this << ", ";
    }
    *this << ")";

    return *this;
}

template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::vector<std::unique_ptr<T>> & vector)
{
    *this << "vector(";
    for (size_t i = 0; i < vector.size(); ++i)
    {
        *this << vector[i].get();
        if (i < vector.size()-1)
            *this << ", ";
    }
    *this << ")";

    return *this;
}

template <typename T, std::size_t Count>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::array<T, Count> & array)
{
    *this << "array(";
    for (size_t i = 0; i < Count; ++i)
    {
        *this << array[i];
        if (i < Count-1)
            *this << ", ";
    }
    *this << ")";

    return *this;
}

template <typename T, std::size_t Count>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::array<T *, Count> & array)
{
    *this << "array(";
    for (size_t i = 0; i < Count; ++i)
    {
        *this << array[i];
        if (i < Count-1)
            *this << ", ";
    }
    *this << ")";

    return *this;
}

template <typename T, std::size_t Count>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::array<std::unique_ptr<T>, Count> & array)
{
    *this << "array(";
    for (size_t i = 0; i < Count; ++i)
    {
        *this << array[i].get();
        if (i < Count-1)
            *this << ", ";
    }
    *this << ")";

    return *this;
}


} // namespace globjects
