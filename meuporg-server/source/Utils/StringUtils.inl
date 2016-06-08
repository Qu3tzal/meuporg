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

void trim(std::string s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}
