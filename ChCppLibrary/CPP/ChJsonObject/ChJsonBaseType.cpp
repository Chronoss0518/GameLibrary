#include"../../BaseIncluder/ChBase.h"
#include<cmath>

#include"../ChTextObject/ChTextObject.h"
#include"ChJsonBaseType.h"
#include"ChJsonObject.h"
#include"ChJsonArray.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"ChJsonBoolean.h"
#include"../ChCumulative/ChCumulative.h"

using namespace ChCpp;

constexpr char nullText[] = "null";

std::string JsonNull::GetRawData()const
{
	return nullText;
}

ChPtr::Shared<JsonBaseType> JsonBaseType::GetParameter(const std::string& _json)
{
	if (_json == nullText)return ChPtr::Make_S<JsonNull>();

	ChPtr::Shared<JsonBaseType> res = nullptr;

	res = GetParameterToObject(_json);

	if (res != nullptr)return res;

	res = GetParameterToArray(_json);

	if (res != nullptr)return res;

	res = GetParameterToString(_json);

	if (res != nullptr)return res;

	res = GetParameterToBoolean(_json);

	if (res != nullptr)return res;

	res = GetParameterToNumber(_json);

	if (res != nullptr)return res;

	return  ChPtr::Make_S<JsonNull>();
}

ChPtr::Shared<JsonObject> JsonBaseType::GetParameterToObject(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonObject>();
	if(!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonArray> JsonBaseType::GetParameterToArray(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonArray>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonString> JsonBaseType::GetParameterToString(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonString>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonBoolean> JsonBaseType::GetParameterToBoolean(const std::string& _json)
{
	auto&& res = ChPtr::Make_S<JsonBoolean>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

ChPtr::Shared<JsonNumber> JsonBaseType::GetParameterToNumber(const std::string& _json)
{
	if (_json.size() <= 0)return nullptr;
	if (_json.size() <= 1 && (_json[0] > 57 || _json[0] < 48))return nullptr;


	bool floatingPointFlg = false;

	auto&& res = ChPtr::Make_S<JsonNumber>();

	*res = ChStr::GetFloatingFromText<long double>(_json);

	return res;
}


std::string JsonBaseType::GetRawText(unsigned long& _textPosition, const std::string& _parameterObjectText, const TextObject& _parameterObject,bool _jsonObjectFlg)
{
	std::string res = _parameterObjectText;
	ChPtr::Shared<ChCpp::Cumulative<char>> testNum = nullptr;

	if (_jsonObjectFlg)
	{
		auto nameAndValue = ChStr::Split(_parameterObject.GetTextLine(_textPosition), ":");

		for (unsigned long i = 2; i < nameAndValue.size(); i++)
		{
			res += ":" + nameAndValue[i];
		}

	}
	else
	{
		res += ",";
	}

	if (res[0] == '[')
	{

		testNum = ChPtr::Make_S<ChCpp::Cumulative<char>>('[', ']');
		
		for (unsigned long i = 0; i < res.size(); i++)
		{
			testNum->Update(res[i]);
		}


		do
		{
			_textPosition++;
			if (_parameterObject.LineCount() <= _textPosition)return "";
			std::string testText = _parameterObject.GetTextLine(_textPosition);
			res += "," + testText;

			for (unsigned long i = 0; i < testText.size(); i++)
			{
				testNum->Update(testText[i]);
			}

		} while (testNum->GetCount() > 0);
	}
	else if (res[0] == '{')
	{

		testNum = ChPtr::Make_S<ChCpp::Cumulative<char>>('{', '}');

		for (unsigned long i = 0; i < res.size(); i++)
		{
			testNum->Update(res[i]);
		}

		do
		{
			_textPosition++;
			if (_parameterObject.LineCount() <= _textPosition)return "";

			std::string testText = _parameterObject.GetTextLine(_textPosition);
			res += "," + testText;

			for (unsigned long i = 0; i < testText.size(); i++)
			{
				testNum->Update(testText[i]);
			}


		} while (testNum->GetCount() > 0);
	}

	return res;
}
