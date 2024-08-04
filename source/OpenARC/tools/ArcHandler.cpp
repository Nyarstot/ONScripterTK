#include "OpenARC/tools/ArcHandler.h"



ArcHandler::ArcHandler(ArchiveType archiveType)
{
    this->archiveType = archiveType;
    switch (archiveType)
    {
    case ARCHIVE_TYPE_NONE:
    case ARCHIVE_TYPE_NS2:
    case ARCHIVE_TYPE_NSA:
        nsaReader = new NsaReader(path);
        sarReader = nullptr;
        break;
    case ARCHIVE_TYPE_SAR:
        sarReader = new SarReader(path);
        nsaReader = nullptr;
        break;
    }
}

ArcHandler::~ArcHandler()
{
    delete nsaReader;
    delete sarReader;
}

void ArcHandler::setNSAOffset(int offset)
{
    nsaData.nsa_offset = offset;
}

int ArcHandler::getNSAOffset()
{
    return nsaData.nsa_offset;
}

void ArcHandler::clearNSAReaderData()
{
    delete[] nsaData.buffer;
    nsaData.buffer = nullptr;
    nsaData.buffer_length = 0;
    nsaData.length = 0;
    nsaData.nsa_offset = 0;
}

void ArcHandler::clearSARReaderData()
{
    delete[] sarData.buffer;
    sarData.buffer = nullptr;
    sarData.buffer_length = 0;
    sarData.length = 0;
}

void ArcHandler::decodeNSA(char* archive_path, char* outdir)
{
    int result = -1;
    int count = 0;
    struct stat file_stat;

    result = nsaReader->openForConvert(archive_path, archiveType, nsaData.nsa_offset);
    if (result != 0) {
        fprintf_s(stderr, "Can't open file");
        exit(-1);
    }
    count = nsaReader->getNumFiles();

    NsaReader::FileInfo sFI;
    for (int i{}; i < count; i++) {
        sFI = nsaReader->getFileByIndex(i);
        nsaData.length = nsaReader->getFileLength(sFI.name);
        if (nsaData.length > nsaData.buffer_length) {
            if (nsaData.buffer) delete[] nsaData.buffer;
            nsaData.buffer = new unsigned char[nsaData.length];
            nsaData.buffer_length = nsaData.length;
        }

        if (nsaData.length > 0) {
            unsigned int len;
            if ((len = nsaReader->getFile(sFI.name, nsaData.buffer)) != nsaData.length) {
                fprintf(stderr, "file %s is not fully retrieved %d %lu\n", sFI.name, len, nsaData.length);
                nsaData.length = sFI.length;
                continue;
            }
        }
        else
        {
            fprintf(stderr, "file %s is empty\n", sFI.name);
        }

        char file_name[512];
        char dir_name[256];

        if (outdir)
            sprintf_s(file_name, "%s\\%s", outdir, sFI.name);
        else
            sprintf_s(file_name, "%s", sFI.name);

        printf("extracting %d of %d, %lu bytes (%s)\n", i + 1, count, nsaData.length, sFI.name);
        for (int j = 0; j < strlen(file_name); j++) {
            file_name[j] = tolower(file_name[j]); //Mion: easier on the eyes
            if (file_name[j] == '\\') {
                file_name[j] = '/';
                strncpy(dir_name, file_name, j);
                dir_name[j] = '\0';

                /* If the directory doesn't exist, create it */
                if (stat(dir_name, &file_stat) == -1 && errno == ENOENT)
                    mkdir(dir_name
#ifndef WIN32
                        , 0755
#endif
                    );
            }
        }

        FILE* fp;
        if ((fp = fopen(file_name, "wb"))) {
            printf("    opening %s\n", file_name);
            fwrite(nsaData.buffer, 1, nsaData.length, fp);
            fclose(fp);
        }
        else {
            printf("    opening %s ... failed\n", file_name);
        }
    }

    if (nsaData.buffer) clearNSAReaderData();
}

void ArcHandler::decodeSAR(char* archive_path, char* outdir)
{
    int result = -1;
    int count = 0;
    struct stat file_stat;

    result = sarReader->openForConvert(archive_path);
    if (result != 0) {
        fprintf_s(stderr, "Can't open file");
        exit(-1);
    }
    count = sarReader->getNumFiles();

    SarReader::FileInfo sFI;
    for (int i{}; i < count; i++) {
        sFI = sarReader->getFileByIndex(i);
        sarData.length = sarReader->getFileLength(sFI.name);
        if (sarData.length > sarData.buffer_length) {
            if (sarData.buffer) delete[] sarData.buffer;
            sarData.buffer = new unsigned char[sarData.length];
            sarData.buffer_length = sarData.length;
        }

        if (sarData.length > 0) {
            unsigned int len;
            if ((len = sarReader->getFile(sFI.name, sarData.buffer)) != sarData.length) {
                fprintf(stderr, "file %s is not fully retrieved %d %lu\n", sFI.name, len, sarData.length);
                sarData.length = sFI.length;
                continue;
            }
        }
        else
        {
            fprintf(stderr, "file %s is empty\n", sFI.name);
        }

        char file_name[512];
        char dir_name[256];

        if (outdir)
            sprintf_s(file_name, "%s\\%s", outdir, sFI.name);
        else
            sprintf_s(file_name, "%s", sFI.name);

        printf("extracting %d of %d, %lu bytes (%s)\n", i + 1, count, nsaData.length, sFI.name);
        for (int j = 0; j < strlen(file_name); j++) {
            file_name[j] = tolower(file_name[j]); //Mion: easier on the eyes
            if (file_name[j] == '\\') {
                file_name[j] = '/';
                strncpy(dir_name, file_name, j);
                dir_name[j] = '\0';

                /* If the directory doesn't exist, create it */
                if (stat(dir_name, &file_stat) == -1 && errno == ENOENT)
                    mkdir(dir_name
#ifndef WIN32
                        , 0755
#endif
                    );
            }
        }

        FILE* fp;
        if ((fp = fopen(file_name, "wb"))) {
            printf("    opening %s\n", file_name);
            fwrite(sarData.buffer, 1, sarData.length, fp);
            fclose(fp);
        }
        else {
            printf("    opening %s ... failed\n", file_name);
        }
    }

    if (sarData.buffer) clearSARReaderData();
}

void ArcHandler::decodeArc(char* archive_path, char* outdir)
{
    if (archiveType != ArchiveType::ARCHIVE_TYPE_SAR) {
        decodeNSA(archive_path, outdir);
        return;
    }
    decodeSAR(archive_path, outdir);
    return;
}

// Python export functions

ARC_API ArcHandler* create(int archiveType) {
    return new ArcHandler((ArchiveType)archiveType);
}

ARC_API void destroy(ArcHandler* arcHandler) {
    delete arcHandler;
}

ARC_API void setNSAOffset(ArcHandler* arcHandler, int offset) {
    arcHandler->setNSAOffset(offset);
}

ARC_API int getNSAOffset(ArcHandler* arcHandler) {
    return arcHandler->getNSAOffset();
}

ARC_API void decodeArc(ArcHandler* arcHandler, char* archive_path, char* outdir) {
    arcHandler->decodeArc(archive_path, outdir);
}