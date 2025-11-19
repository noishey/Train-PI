/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Clicked_png;
    const int            Clicked_pngSize = 6941;

    extern const char*   HoveredOff_png;
    const int            HoveredOff_pngSize = 4864;

    extern const char*   HoveredOn_png;
    const int            HoveredOn_pngSize = 1020;

    extern const char*   OffState_png;
    const int            OffState_pngSize = 5561;

    extern const char*   OnState_png;
    const int            OnState_pngSize = 727;

    extern const char*   Unclickable_png;
    const int            Unclickable_pngSize = 1069;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
