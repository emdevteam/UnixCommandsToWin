#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shlobj.h>
#include <shellapi.h>
#include <string.h>

// Function to delete files from System32
int deleteFiles() {
    const char *files[] = {
        "cat.exe",
        "mv.exe",
        "cp.exe",
        "rm.exe",
        "clear.exe",
        "ls.exe"
    };

    char dest[MAX_PATH];

    if (SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, 0, dest) != S_OK) {
        MessageBox(NULL, "Failed to get System32 path", "Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    for (int i = 0; i < sizeof(files)/sizeof(files[0]); ++i) {
        char destFile[MAX_PATH];
        snprintf(destFile, sizeof(destFile), "%s\\\\%s", dest, files[i]);

        if (remove(destFile) != 0) {
            MessageBox(NULL, "Failed to delete file", "Error", MB_ICONERROR | MB_OK);
            return 1;
        }
    }

    MessageBox(NULL, "Uninstall successfully completed.", "Success", MB_OK);
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

    int result = MessageBox(NULL, "Do you want to uninstall Unix Commands for Windows?", "Uninstall", MB_ICONQUESTION | MB_YESNO);
    if (result == IDYES) {
        return deleteFiles();
    } else {
        MessageBox(NULL, "Uninstallation cancelled", "Cancel", MB_OK);
    }

    return 0;
}