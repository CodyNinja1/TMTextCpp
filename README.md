# TMText
A simple C++20 for parsing Trackmania-formatted text.

```c++
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
```
```
$i: 105 (at 0)
$fff: 1 (at 7)
$000: 1 (at 14)
$u: 0 (at 46)
Hello! White. Give me some $$$. Also, this is unsupported!
^
       ^
              ^
                                              ^
```
