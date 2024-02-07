When creating a new game object on Windows, a menu allows the user to choose a .obj file. After selecting the file, its parent directory is copied to ${projectdir/models} for organization and easy access. This involves:

1. Formatting the parent folder path to create a corresponding folder in ${projectdir/models}.
2. Using dirent.h to iterate through the parent directory and copy each file into the new folder.
3. The path to the new .obj file is then passed to the GameObject instance creation.


For Saving and Loading

1. We take in a total of 26 Parameters defining all characteristics of a Game object. We fetch each model's details and store them in a text file.
2. When we are loading, we fetch all these details back and create instances of GameObjects accordingly and get GameObject pointers array.
