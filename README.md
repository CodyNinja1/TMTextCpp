# TMText
A simple C++20 for parsing Trackmania-formatted text.

```c++
#include "TMText/TMText.h"
int main()
{
    auto Specs = TrackmaniaText::FindAllFormatSpecifiers("$iHello! $fffWhite. $000Give me some $$$$$$. Also, this is $uunsupported!");

    for (auto& Spec : Specs)
    {
        std::cout << Spec.Code << ": " << Spec.Type << " (at " << Spec.Idx << ")" << "\n";
    }

    std::cout << Specs.OriginalText << "\n\n";

    for (auto& Spec : Specs)
    {
        for (size_t Wait = 0; Wait < Spec.Idx == 0 ? 0 : Spec.Idx - 1; Wait++)
        {
            std::cout << " ";
        }
        std::cout << "^";
    }

    std::cout << "\n\n";

    // FillZero       => if any character is found to not be hex, the rest is filled with zeros,     so $fhello becomes equivilant to $f00hello
    // InterpretAsHex => if any character is found to not be hex, it is assumed to be equal to zero, so $fhello becomes equivilant to $f0ello
    auto SpecsEdgecase = TrackmaniaText::FindAllFormatSpecifiers("$fhello, world!", TrackmaniaText::ColorEdgecaseBehaviour_FillZero);
    std::cout << "Edgecase: " << SpecsEdgecase.OriginalText << "\n\n";
}
```
```
$i: 105 (at 0)
$fff: 1 (at 7)
$000: 1 (at 14)
$u: 0 (at 46)

Hello! White. Give me some $$$. Also, this is unsupported!
^      ^      ^                               ^

Edgecase: hello, world!
```
## Limits
It does not support `$l` or `$p` properly.
