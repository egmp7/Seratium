/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   crossfader_png;
    const int            crossfader_pngSize = 4840;

    extern const char*   cue_png;
    const int            cue_pngSize = 12307;

    extern const char*   load_png;
    const int            load_pngSize = 8940;

    extern const char*   logo_png;
    const int            logo_pngSize = 8251;

    extern const char*   logo1_png;
    const int            logo1_pngSize = 10496;

    extern const char*   playPause_png;
    const int            playPause_pngSize = 11430;

    extern const char*   speedFader_png;
    const int            speedFader_pngSize = 5541;

    extern const char*   volFader_png;
    const int            volFader_pngSize = 5417;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

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
