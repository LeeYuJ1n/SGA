#pragma once

namespace Utility
{
    string ToString(wstring str);
    wstring ToWString(string str);

    vector<string> SplitString(string origin, const string& tok);

    wstring GetExtension(wstring file);
}