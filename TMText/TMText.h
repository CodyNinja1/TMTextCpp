#pragma once
#pragma warning(disable : 5045 4711 4710)

#include <string>
#include <regex>
#include <vector>


#define TrackmaniaText_IsHexadecimal(Char) (((Char) >= '0' && (Char) <= '9') || ((Char) >= 'a' && (Char) <= 'f') || ((Char) >= 'A' && (Char) <= 'F'))


namespace TrackmaniaText
{
	extern std::string ValidTrackmaniaTextFormatSpecifierChars;

	constexpr char CharToLower(char);

	enum FormatSpecifierType
	{
		FormatSpecifierType_NotSupported = 0,
		FormatSpecifierType_Color = 1,
		FormatSpecifierType_Italic = 'i',
		FormatSpecifierType_Bold = 'o',
		FormatSpecifierType_Wide = 'w',
		FormatSpecifierType_Narrow = 'n',
		FormatSpecifierType_ResetWidth = 'm',
		FormatSpecifierType_ForceUpper = 't',
		FormatSpecifierType_Shadow = 's',
		FormatSpecifierType_Link = 'l',
		FormatSpecifierType_ResetColor = 'g',
		FormatSpecifierType_ResetAll = 'z',
		FormatSpecifierType_PlayerManialink = 'p'
	};

	enum ColorEdgecaseBehaviour
	{
		ColorEdgecaseBehaviour_FillZero = 0,
		ColorEdgecaseBehaviour_InterpretAsHex = 1
	};

	struct FormatSpecifier
	{
		std::string Code;
		FormatSpecifierType Type;
#ifdef _M_X64
		uint32_t Pad;
#endif
		size_t Idx;

		FormatSpecifier(std::string FormatSpec, size_t Idx = -1);
	};

	struct TextSlice
	{
		std::string Text;
		FormatSpecifier Specifier;

		TextSlice() = delete;
	};

	struct FormatSpecifierSearchResult
	{
		std::vector<FormatSpecifier> Specifiers;
		std::string OriginalText;
		std::string TextNoFormatSpecifiers;

		void push_back(std::string FormatSpec, size_t Idx = -1);

		std::vector<FormatSpecifier>::iterator begin();
		std::vector<FormatSpecifier>::iterator end();
	};

	FormatSpecifierSearchResult FindAllFormatSpecifiers(std::string Str, ColorEdgecaseBehaviour ColorEdgecaseBehaviourType = ColorEdgecaseBehaviour_InterpretAsHex);
}

