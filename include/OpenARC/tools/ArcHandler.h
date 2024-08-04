#ifndef __ARC_HANDLER_H__
#define __ARC_HANDLER_H__

#include "OpenARC/BaseReader.h"
#include "OpenARC/DirectReader.h"
#include "OpenARC/DirPaths.h"
#include "OpenARC/NsaReader.h"
#include "OpenARC/SarReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#ifdef _WIN32
    #include <direct.h>
    #include <Windows.h>

    #ifdef BUILD_DLL
        #define ARC_API extern "C" __declspec(dllexport)
    #else
        #define ARC_API __declspec(dllimport)
    #endif // BUILD_DLL
#endif // _WIN32

extern int errno;


struct dirnode {
    DIR* dir;
    int namelen;
    dirnode* next;
    dirnode* prev;
    dirnode() : dir(NULL), namelen(0), next(NULL), prev(NULL) {}
};
static dirnode dirn;

enum ArchiveType
{
    ARCHIVE_TYPE_NONE   = BaseReader::ARCHIVE_TYPE_NONE,
    ARCHIVE_TYPE_NS2    = BaseReader::ARCHIVE_TYPE_NS2,
    ARCHIVE_TYPE_NSA    = BaseReader::ARCHIVE_TYPE_NSA,
    ARCHIVE_TYPE_SAR    = BaseReader::ARCHIVE_TYPE_SAR
};


class ARC_API ArcHandler final
{
    struct NsaReaderData
    {
        unsigned long length = 0;
        unsigned long buffer_length = 0;
        unsigned char* buffer = NULL;
        int nsa_offset = 0;
    };

    struct SarReaderData
    {
        unsigned long length = 0;
        unsigned long buffer_length = 0;
        unsigned char* buffer = NULL;
    };

private:
    DirPaths path;
    NsaReader* nsaReader;
    SarReader* sarReader;
    ArchiveType archiveType;

    NsaReaderData nsaData;
    SarReaderData sarData;

private:
    void decodeNSA(char* archive_path, char* outdir);
    void decodeSAR(char* archive_path, char* outdir);

    //void encodeNSA(char* indir);
    //void encodeSAR(char* indir);

    void clearNSAReaderData();
    void clearSARReaderData();

    //void processFile();

public:
    ArcHandler(ArchiveType archiveType);
    ~ArcHandler();

    void decodeArc(char* archive_path, char* outdir);
    //void encodeArc(char* indir);

    void setNSAOffset(int offset);
    int getNSAOffset();
};

#endif // !__ARC_HANDLER_H__
