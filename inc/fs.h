#pragma once

#include <minizip/zip.h>
#include <minizip/unzip.h>
#include "fs/fstype.h"
#include "fs/file.h"
#include "fs/dir.h"
#include "fs/zip.h"
#include "fs/fsfile.h"
#include "fs/remote.h"
#include "ui/miscui.h"

#define BUFF_SIZE 0x4000
#define ZIP_BUFF_SIZE 0x20000
#define TRANSFER_BUFFER_LIMIT 0xC00000

namespace fs
{
    // Existing function declarations...

    copyArgs *copyArgsCreate(const std::string& src, const std::string& dst, const std::string& dev, zipFile z, unzFile unz, bool _cleanup, bool _trimZipPath, uint8_t _trimPlaces);
    void copyArgsDestroy(copyArgs *c);

    void init();
    bool mountSave(const FsSaveDataInfo& _m);
    inline bool unmountSave() { return fsdevUnmountDevice("sv") == 0; }
    bool commitToDevice(const std::string& dev);
    std::string getWorkDir();
    void setWorkDir(const std::string& _w);

    // Loads paths to filter from backup/deletion
    void loadPathFilters(const uint64_t& tid);
    bool pathIsFiltered(const std::string& _path);
    void freePathFilters();

    void createSaveData(FsSaveDataType _type, uint64_t _tid, AccountUid _uid, threadInfo *t);
    void createSaveDataThreaded(FsSaveDataType _type, uint64_t _tid, AccountUid _uid);
    bool extendSaveData(const data::userTitleInfo *tinfo, uint64_t extSize, threadInfo *t);
    void extendSaveDataThreaded(const data::userTitleInfo *tinfo, uint64_t extSize);
    uint64_t getJournalSize(const data::userTitleInfo *tinfo);
    uint64_t getJournalSizeMax(const data::userTitleInfo *tinfo);

    // Always threaded operations
    void wipeSave();

    void createNewBackup(void *a);
    void overwriteBackup(void *a);
    void restoreBackup(void *a);
    void deleteBackup(void *a);

    void dumpAllUserSaves(void *a);
    void dumpAllUsersAllSaves(void *a);

    void logOpen();
    void logWrite(const char *fmt, ...);

    // -------------------------------------------------------------------------
    // New Sync Function Declarations:
    // -------------------------------------------------------------------------
    // Sync an NSO save (from sdmc:/switch/JKSV/Saves/NSO/<gameName>/cartridge.sram)
    // to an emulator save (sdmc:/roms/<platform>/<gameName>.sav).
    bool syncNSOtoEmulator(const std::string &gameName, const std::string &platform);

    // Sync an emulator save (sdmc:/roms/<platform>/<gameName>.sav)
    // to an NSO save (sdmc:/switch/JKSV/Saves/NSO/<gameName>/cartridge.sram).
    bool syncEmulatorToNSO(const std::string &gameName, const std::string &platform);
}
