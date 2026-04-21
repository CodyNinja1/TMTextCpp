#include "TMText.h"

namespace TrackmaniaText
{
	std::string ValidTrackmaniaTextFormatSpecifierChars = "iownmtslgzpabcdef0123456789";

	constexpr char CharToLower(char Char)
	{
		return Char >= 'A' and Char <= 'Z' ? Char | 32 : Char;
	}

	FormatSpecifier::FormatSpecifier(std::string FormatSpec, size_t Idx)
	{
		char TypeOfSpecifierDecider = CharToLower(FormatSpec[1]);
		if (TrackmaniaText_IsHexadecimal(TypeOfSpecifierDecider))
		{
			this->Type = FormatSpecifierType_Color;
		}
		else if (ValidTrackmaniaTextFormatSpecifierChars.find(TypeOfSpecifierDecider) == std::string::npos)
		{
			this->Type = FormatSpecifierType_NotSupported;
		}
		else
		{
			this->Type = (FormatSpecifierType)TypeOfSpecifierDecider;
		}

		this->Code = FormatSpec;
		this->Idx = Idx;
		this->Pad = 0;
	}

	FormatSpecifier::operator std::string()
	{
		return this->Code;
	}

	void FormatSpecifierSearchResult::push_back(std::string FormatSpec, size_t Idx)
	{
		Specifiers.push_back(FormatSpecifier( FormatSpec, Idx ));
	}

	std::vector<FormatSpecifier>::iterator FormatSpecifierSearchResult::begin()
	{
		return Specifiers.begin();
	}

	std::vector<FormatSpecifier>::iterator FormatSpecifierSearchResult::end()
	{
		return Specifiers.end();
	}

	FormatSpecifierSearchResult FindAllFormatSpecifiers(std::string Str)
	{
		FormatSpecifierSearchResult Founds = {};

		int CharsToGo = 0;

		std::string Temp = "";

		size_t DoubleDollarSignsEncountered = 0;

		for (size_t CharIdx = 0; CharIdx < Str.length(); CharIdx++)
		{
			char Char = Str[CharIdx];

			bool CharInvolvedInSpecifiers = false;

			if (CharsToGo == 0)
			{
				if (not Temp.empty())
				{ 
					Founds.push_back(Temp, CharIdx - Temp.length() - DoubleDollarSignsEncountered);
					Temp = "";
				}
				CharsToGo = 1;
			}

			if (Char == '$')
			{
				if (not Temp.empty())
				{
					CharsToGo = 1;
					Temp = "";

					DoubleDollarSignsEncountered += 1;
				}
				else
				{
					CharsToGo = 2;
					Temp.push_back(Char);

					CharInvolvedInSpecifiers = true;
				}
			}
			else if ((TrackmaniaText_IsHexadecimal(Char)) and Temp.length() > 0)
			{
				if (Temp.length() == 1)
				{
					CharsToGo = 3;
				}
				Temp.push_back(Char);

				CharInvolvedInSpecifiers = true;
			}
			else if (Temp.length() == 1)
			{
				Temp.push_back(Char);

				CharInvolvedInSpecifiers = true;
			}

			CharsToGo -= 1;

			if (not CharInvolvedInSpecifiers)
			{
				Founds.OriginalText.push_back(Char);
			}
		}

		if (Temp.length() > 1)
		{
			Founds.push_back(Temp);
		}

		size_t RollingOffset = 0;

		for (size_t SpecIdx = 0; SpecIdx < Founds.Specifiers.size(); SpecIdx++)
		{
			auto& Spec = Founds.Specifiers[SpecIdx];
			Spec.Idx -= RollingOffset;
			RollingOffset += Spec.Code.length();
		}

		return Founds;
	}
}