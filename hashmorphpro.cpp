#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <wincrypt.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool morphFile(const char* sourcePath, const char* destinationPath) {
    // Copy the source file to the destination
    if (!copyFile(sourcePath, destinationPath)) {
        return false;
    }

    // Open the destination file
    FILE* destination = fopen(destinationPath, "r+b");
    if (!destination) {
        return false;
    }

    // Seek to the end of the file
    fseek(destination, 0, SEEK_END);

    // Generate a random number of bytes (within a reasonable range to avoid making the file too large)
    int randomBytes = rand() % 1024;

    // Insert the random bytes at the end of the file (in the overlay)
    char randomData[randomBytes];
    for (int i = 0; i < randomBytes; i++) {
        randomData[i] = rand() % 256;
    }
    fwrite(randomData, 1, randomBytes, destination);

    // Close the file handle
    fclose(destination);

    return true;
}

void morphFilesInDirectory(const char* directoryPath) {
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(directoryPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue;
        }

        char* extension = strrchr(findData.cFileName, '.');
        if (extension == NULL) {
            continue;
        }

        if (strcmp(extension, ".exe") != 0 && strcmp(extension, ".dll") != 0 && strcmp(extension, ".ps1") != 0) {
            continue;
        }

        char destinationPath[MAX_PATH];
        sprintf(destinationPath, "%s\\%s", directoryPath, findData.cFileName);
        morphFile(findData.cFileName, destinationPath);
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
}

int main() {
    srand(time(NULL));

    int choice;
    const char* sourcePath;
    char destinationPath[MAX_PATH] = "";

    printf(ANSI_COLOR_RED);
    printf("\t\t\tHash Morph Pro\n");
    printf(ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE);
    printf("\t\t\t\t\tBy a7t0fwa7\n");
    printf("\t\t\t\t\tgithub.com/a7t0fwa7\n\n\n");
    printf(ANSI_COLOR_RESET);

    printf(ANSI_COLOR_GREEN);
    printf("Select an option:\n\n");
    printf("1: CMD\n");
    printf("2: Powershell\n");
    printf("3: Powershell_ise\n");
    printf("4: Custom path\n");
    printf("5: Morph all files in a directory\n\n");
    printf("#  ");
    printf(ANSI_COLOR_RESET);
    scanf_s("%d", &choice);

    switch (choice) {
    case 1:
        sourcePath = "C:\\Windows\\System32\\cmd.exe";
        break;
    case 2:
        sourcePath = "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe";
        break;
    case 3:
        sourcePath = "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\PowerShell_ise.exe";
        break;
    case 4:
        printf(ANSI_COLOR_GREEN);
        printf("Enter custom source path: ");
        printf(ANSI_COLOR_RESET);
        char customSourcePath[MAX_PATH];
        scanf_s("%s", customSourcePath, sizeof(customSourcePath));
        sourcePath = customSourcePath;
        break;
    case 5:
        printf(ANSI_COLOR_GREEN);
        printf("Enter directory path: ");
        printf(ANSI_COLOR_RESET);
        char directoryPath[MAX_PATH];
        scanf_s("%s", directoryPath, sizeof(directoryPath));
        morphFilesInDirectory(directoryPath);
        return 0;
    default:
        printf(ANSI_COLOR_RED);
        printf("Invalid choice.\n");
        printf(ANSI_COLOR_RESET);
        return 1;
    }

    printf(ANSI_COLOR_GREEN);
    printf("Enter destination path (leave empty for current directory): ");
    printf(ANSI_COLOR_RESET);
    getchar();

    char input[MAX_PATH];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "") != 0) {
        strncpy_s(destinationPath, sizeof(destinationPath), input, _TRUNCATE);
    }
    else {
        const char* fileName = strrchr(sourcePath, '\\');
        if (fileName == NULL) {
            printf(ANSI_COLOR_RED);
            printf("Invalid source path.\n");
            printf(ANSI_COLOR_RESET);
            return 1;
        }
        fileName++;
        const char* dot = strrchr(fileName, '.');
        if (dot != NULL) {
            strncpy_s(destinationPath, sizeof(destinationPath), fileName, dot - fileName);
            strcat_s(destinationPath, sizeof(destinationPath), "_new");
            strcat_s(destinationPath, sizeof(destinationPath), dot);
        }
        else {
            strcpy_s(destinationPath, sizeof(destinationPath), fileName);
            strcat_s(destinationPath, sizeof(destinationPath), "_new");
        }
    }

    if (morphFile(sourcePath, destinationPath)) {
        char fullPath[MAX_PATH];
        if (GetFullPathNameA(destinationPath, sizeof(fullPath), fullPath, NULL) == 0) {
            printf(ANSI_COLOR_RED);
            printf("Failed to get full path of the destination file. Error code: %d\n", GetLastError());
            printf(ANSI_COLOR_RESET);
        }
        else {
            printf(ANSI_COLOR_GREEN);
            printf("\nFile copied successfully to: %s\n\n", fullPath);
            printf(ANSI_COLOR_MAGENTA);
            printf("Calculating hash values...\n\n");
            printf(ANSI_COLOR_YELLOW);
            printf("Old File Hash:\n");
            printFileHash(sourcePath);
            printf(ANSI_COLOR_BLUE);
            printf("\nNew File Hash:\n");
            printFileHash(destinationPath);
            printf(ANSI_COLOR_RESET);
        }
    }
    else {
        printf(ANSI_COLOR_RED);
        printf("File copy failed.\n");
        printf(ANSI_COLOR_RESET);
    }

    return 0;
}

