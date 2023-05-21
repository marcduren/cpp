string trim(const string& str) {
    // Find the first non-whitespace character
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return ""; // The string is all whitespace
    }

    // Find the last non-whitespace character
    size_t last = str.find_last_not_of(' ');

    // Return the trimmed string
    return str.substr(first, last - first + 1);
}

string ltrim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return ""; // The string is all whitespace
    }
    return str.substr(first);
}
std::vector<std::string> splitString(std::string str, char splitter) {
    std::vector<std::string> result;
    std::string current = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == splitter) {
            if (current != "") {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.size() != 0)
        result.push_back(current);
    return result;
}

std::string to_uppercase(const std::string& str) {
    std::string result = "";
    for (char c : str) {
        result += std::toupper(c);
    }
    return result;
}

std::wstring utf8_to_wstring(const std::string& utf8_str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8_str);
}

std::string wstring_to_utf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}
std::string to_uppercase_utf8(const std::string& utf8_str) {
    std::wstring result = L"";
    std::wstring wstr = utf8_to_wstring(utf8_str);
    for (wchar_t& c : wstr) {
        if (c ==L'é') result += L'É';
        else result += std::towupper(c);
    }
    return wstring_to_utf8(result);
}
std::string UTF8toISO8859_1(const char * in) {
    std::string out;
    if (in == NULL)
        return out;

    unsigned int codepoint;
    while (*in != 0) {
        unsigned char ch = static_cast<unsigned char> (*in);
        if (ch <= 0x7f)
            codepoint = ch;
        else if (ch <= 0xbf)
            codepoint = (codepoint << 6) | (ch & 0x3f);
        else if (ch <= 0xdf)
            codepoint = ch & 0x1f;
        else if (ch <= 0xef)
            codepoint = ch & 0x0f;
        else
            codepoint = ch & 0x07;
        ++in;
        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff)) {
            if (codepoint <= 255) {
                out.append(1, static_cast<char> (codepoint));
            } else {
                out += '.';
            }
        }
    }
    return out.c_str();
}

std::string utf8_to_latin1(const std::string& utf8_str) {
    // Create iconv conversion descriptor
    iconv_t cd = iconv_open("ISO-8859-1", "UTF-8");
    if (cd == (iconv_t) - 1) {
        printf("iconv_open() failed\n");
    }

    // Convert the string
    size_t in_bytes_left = utf8_str.size();
    size_t out_bytes_left = in_bytes_left; // Maximum possible size of the Latin-1 string
    char* in_buf = const_cast<char*> (utf8_str.data());
    char* out_buf = new char[out_bytes_left];
    char* out_ptr = out_buf;
    if (iconv(cd, &in_buf, &in_bytes_left, &out_ptr, &out_bytes_left) == (size_t) - 1) {
        iconv_close(cd);
        delete[] out_buf;
        printf("iconv() failed\n");
    }
    std::string latin1_str(out_buf, out_ptr - out_buf);

    // Clean up
    iconv_close(cd);
    delete[] out_buf;

    return latin1_str;
}

