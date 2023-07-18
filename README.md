# HashMorphPro

Is an alternate version of the original Hash Morpher code by [oh-az](https://github.com/oh-az/HashMorpher). It includes a couple of improvements:

1. **Morphing Functionality** : The original HashMorpher code added two random bytes at the end of the copied file. The new Hash Morph Pro code adds a random number of bytes (up to 1024) at the end of the copied file. This increases the variability of the morphed files, making them less likely to be detected by simple hash-based file integrity checks.
2. **Directory Morphing** : The new code introduces a feature to morph all executable files (.exe, .dll, .ps1) in a specified directory. This is another enhancement over the original code, which could only morph a single file at a time.

## Compiling and Usage

1. **Compile the Program** : In a Windows Terminal, compile the program using a C compiler. If you're using GCC, the command would be `gcc -o hashmorphpro.exe hashmorphpro.c`pp. This will create an executable named `hashmorphpro`.exe.
2. **Run the Program** : Run the program by typing `./hashmorphpro`.exe in the terminal.
3. **Choose an Option** : The program will display a menu with five options:

* 1: CMD
* 2: Powershell
* 3: Powershell_ise
* 4: Custom path
* 5: Morph all files in a directory

   Enter the number corresponding to your choice and press Enter.

1. **Enter Source Path or Directory Path** :

* If you chose options 1-3, the program will use a predefined source path.
* If you chose option 4, you will be prompted to enter a custom source path. Type the full path to the file you want to morph and press Enter.
* If you chose option 5, you will be prompted to enter a directory path. Type the full path to the directory containing the files you want to morph and press Enter.

1. **Enter Destination Path** : If you chose options 1-4, you will be prompted to enter a destination path. This is where the morphed file will be saved. If you want to save the morphed file in the current directory, just press Enter without typing anything. Otherwise, type the full path to the destination directory and press Enter.
2. **View Results** : The program will attempt to morph the file(s) based on your choices. If successful, it will display the full path of the morphed file(s) and calculate the hash values of the original and morphed file(s).

Remember, this program modifies binary files in a way that changes their hash values but keeps them executable. Always use caution when handling executable files, and only use this program for legitimate purposes.
