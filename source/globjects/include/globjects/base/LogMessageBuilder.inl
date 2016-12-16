
#pragma once


namespace globjects
{


template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(const std::shared_ptr<T> & ref_pointer)
{
    *this << ref_pointer.get();

    return *this;
}

template <typename T>
LogMessageBuilder& LogMessageBuilder::operator<<(const T * pointer)
{
    *this << static_cast<const void*>(pointer);

    return *this;
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


} // namespace globjects
