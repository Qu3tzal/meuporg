template<typename T>
std::string from(T x)
{
    std::stringstream ss;
    ss << x;
    return ss.str();
}

template<typename T>
T to(std::string str)
{
    T x;

    std::stringstream ss(str);
    ss >> x;

    return x;
}
