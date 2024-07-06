#pragma once
#include <iostream>
#include <string>
#include <Rpc.h>

#pragma comment(lib, "Rpcrt4.lib")

namespace ccrt
{
	// trim from left 
	inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
	{
		s.erase(0, s.find_first_not_of(t));
		return s;
	}

	// trim from right 
	inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
	{
		s.erase(s.find_last_not_of(t) + 1);
		return s;
	}

	// trim from left & right 
	inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
	{
		return ltrim(rtrim(s, t), t);
	}

	inline std::string GenerateGUID()
	{
		UUID id;

		if (RPC_S_OK != UuidCreate(&id))
			id = GUID_NULL;
		char szIID[129];
		wchar_t wszIID[129];

		int r = ::StringFromGUID2(id, wszIID, 128);
		size_t result;
		::wcstombs_s(&result,szIID, wszIID, 128);

		return szIID;
	}
}