/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== IconOpenPlugin.svg ==================
static const unsigned char temp_binary_data_0[] =
"<svg width=\"40\" height=\"40\" viewBox=\"0 0 40 40\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">\n"
"<path d=\"M18.3268 27.9022H33.7252C34.5468 27.9088 35.3616 27.7527 36.1225 27.4428C36.8835 27.1329 37.5755 26.6754 38.1588 26.0966C38.7421 25.5179 39.2051 24.8294 39.521 24.0708C39.8369 23.3122 39.9996 22.4986 39.9995 21.6768V6.27586C40.0096 5.44897 "
"39.8542 4.62842 39.5424 3.86251C39.2307 3.0966 38.7689 2.4008 38.1843 1.81605C37.5996 1.23131 36.9039 0.769448 36.1381 0.457643C35.3724 0.145838 34.552 -0.00960538 33.7252 0.000459286H18.3268C16.676 0.000459286 15.0929 0.656348 13.9256 1.82384C12.758"
"3 2.99133 12.1025 4.57478 12.1025 6.22586V21.6268C12.0992 22.4477 12.2576 23.2611 12.5686 24.0207C12.8797 24.7803 13.3372 25.4712 13.9152 26.0539C14.4932 26.6366 15.1803 27.0998 15.9372 27.4169C16.6942 27.734 17.5062 27.899 18.3268 27.9022ZM33.7252 3"
".8007C34.3882 3.8007 35.024 4.06411 35.4928 4.53298C35.9616 5.00185 36.2249 5.63778 36.2249 6.30086V21.7018C36.2249 22.3649 35.9616 23.0009 35.4928 23.4697C35.024 23.9386 34.3882 24.202 33.7252 24.202H18.3268C17.6639 24.202 17.0281 23.9386 16.5593 23"
".4697C16.0905 23.0009 15.8271 22.3649 15.8271 21.7018V6.27586C15.8271 5.61278 16.0905 4.97685 16.5593 4.50798C17.0281 4.03911 17.6639 3.7757 18.3268 3.7757L33.7252 3.8007Z\" fill=\"#FFE600\"/>\n"
"<path d=\"M6.27516 39.9996H21.6735C23.3243 39.9996 24.9075 39.3438 26.0748 38.1763C27.2421 37.0088 27.8979 35.4253 27.8979 33.7742V18.3233C27.8913 16.6742 27.2334 15.0946 26.0675 13.9285C24.9017 12.7624 23.3223 12.1044 21.6735 12.0979H6.27516C5.45357"
" 12.0913 4.6388 12.2474 3.87785 12.5573C3.1169 12.8672 2.42482 13.3247 1.84153 13.9035C1.25824 14.4822 0.795284 15.1707 0.479361 15.9293C0.163437 16.6879 0.000799179 17.5015 0.000823975 18.3233V33.7242C-0.00923729 34.5511 0.146177 35.3717 0.45793 36."
"1376C0.76968 36.9035 1.23147 37.5993 1.81611 38.184C2.40075 38.7688 3.09644 39.2307 3.86222 39.5425C4.628 39.8543 5.44841 40.0097 6.27516 39.9996ZM21.6735 15.8981C22.3365 15.8981 22.9723 16.1615 23.4411 16.6304C23.9099 17.0993 24.1733 17.7352 24.1733"
" 18.3983V33.7992C24.1733 34.4623 23.9099 35.0983 23.4411 35.5671C22.9723 36.036 22.3365 36.2994 21.6735 36.2994H6.27516C5.61219 36.2994 4.97637 36.036 4.50758 35.5671C4.03879 35.0983 3.77542 34.4623 3.77542 33.7992V18.3233C3.77542 17.6602 4.03879 17."
"0242 4.50758 16.5554C4.97637 16.0865 5.61219 15.8231 6.27516 15.8231L21.6735 15.8981Z\" fill=\"#FFE600\"/>\n"
"</svg>\n";

const char* IconOpenPlugin_svg = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x19b5b63b:  numBytes = 2395; return IconOpenPlugin_svg;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "IconOpenPlugin_svg"
};

const char* originalFilenames[] =
{
    "IconOpenPlugin.svg"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
