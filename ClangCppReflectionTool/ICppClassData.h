#pragma once
#include <string>
#include <vector>

#include "Define.h"
#include "ISerializable.h"


namespace ccrt
{
	class CRRTAPI ICppClassData : public ISerializable
	{
	public:
		virtual std::string GetUSR() = 0;
		virtual std::string GetName() = 0;
		virtual std::string GetFileDirectoryPath() = 0;
		virtual std::string GetFilePath() = 0;
		virtual std::string GetFileName() = 0;
	};
}
