
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shlobj.h>
#include <shellapi.h>
#include <string.h>
#include "resource.h"

// Function to copy files to System32
int copyFiles() {
    struct {
        int id;
        const char *name;
    } files[] = {
        {cat, "cat.exe"},
        {mv, "mv.exe"},
        {cp, "cp.exe"},
        {rm, "rm.exe"},
        {clear, "clear.exe"},
        {ls, "ls.exe"}
    };

    char dest[MAX_PATH];

    if (SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, 0, dest) != S_OK) {
        MessageBox(NULL, "Failed to get System32 path", "Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    for (int i = 0; i < sizeof(files)/sizeof(files[0]); ++i) {
        HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(files[i].id), RT_RCDATA);
        if (!hResource) {
            MessageBox(NULL, "Failed to find resource", "Error", MB_ICONERROR | MB_OK);
            return 1;
        }

        HGLOBAL hLoadedResource = LoadResource(NULL, hResource);
        DWORD dwResourceSize = SizeofResource(NULL, hResource);
        void *pResourceData = LockResource(hLoadedResource);

        char destFile[MAX_PATH];
        snprintf(destFile, sizeof(destFile), "%s\\%s", dest, files[i].name);

        FILE *file = fopen(destFile, "wb");
        if (!file) {
            MessageBox(NULL, "Failed to open destination file", "Error", MB_ICONERROR | MB_OK);
            return 1;
        }

        fwrite(pResourceData, 1, dwResourceSize, file);
        fclose(file);
    }

    MessageBox(NULL, "Install successfully completed.", "Success", MB_OK);
    return 0;
}

// Function to request admin privileges
int requestAdminPrivileges(int argc, char *argv[]) {
    if (!IsUserAnAdmin()) {
        char szPath[MAX_PATH];
        if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
            SHELLEXECUTEINFO sei = { sizeof(sei) };
            sei.lpVerb = "runas";
            sei.lpFile = szPath;
            sei.lpParameters = "";
            sei.nShow = SW_SHOWNORMAL;

            if (!ShellExecuteEx(&sei)) {
                MessageBox(NULL, "Failed to elevate privileges", "Error", MB_ICONERROR | MB_OK);
                return 1;
            }
            exit(0);
        }
    }
    return 0;
}

// Main function
int main(int argc, char *argv[]) {
    if (requestAdminPrivileges(argc, argv)) {
        return 1;
    }

    int result = MessageBox(NULL, "Do you want to install Unix Commands for Windows?", "Install", MB_ICONQUESTION | MB_YESNO);
    if (result == IDYES) {
        return copyFiles();
    } else {
        MessageBox(NULL, "Installation cancelled", "Cancel", MB_OK);
    }

    return 0;
}
