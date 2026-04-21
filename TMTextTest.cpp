#pragma warning(disable : 4711 4710)

#include <iostream>
#include "TMText/TMText.h"

int main()
{
    auto Specs = TrackmaniaText::FindAllFormatSpecifiers("$iHello! $fffWhite. $000Give me some $$$$$$. Also, this is $uunsupported!");

    for (auto& Spec : Specs)
    {
        std::cout << (std::string)Spec << ": " << Spec.Type << " (at " << Spec.Idx << ")" << "\n";
    }

    std::cout << Specs.OriginalText << "\n";

    for (auto& Spec : Specs)
    {
        for (size_t Wait = 0; Wait < Spec.Idx == 0 ? 0 : Spec.Idx - 1; Wait++)
        {
            std::cout << " ";
        }
        std::cout << "^\n";
    }
}