#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <dirent.h>
#include <cstdlib>
#include <sys/stat.h>

int createFolder(const char* folder_path){
    const char* folder_name = folder_path;

    // Create the folder
    if (mkdir(folder_name) == 0) {
        std::cout << "Folder created successfully.\n";
    } else {
        std::cerr << "Error creating folder.\n";
        return 1;
    }
}

std::vector<std::string> listdir(const char *path) {
    struct dirent *entry;
    DIR *dp;
    std::vector<std::string> ret_vec {};
    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
    }
    bool isTrue = false;
    int i = 0;
    while ((entry = readdir(dp))){
        if (i == 2){
          isTrue = true;
          i++;
        }
        if (isTrue == false){
          i++;
        }
        if (isTrue){
          std::string ret_string = entry->d_name;
          std::cout << "Size of String : " <<ret_string.size() << std::endl;
          ret_vec.push_back(entry->d_name);
        }
    }
    std::cout << std::endl;
    closedir(dp);
    return ret_vec;
}

class GameObject {

public:
  float GOmodelmat[4][4] {};
  std::string path{};
  std::vector<float> tvecm{0.0f, 0.0f, 0.0f};
  std::vector<float> svecm{1.0f, 1.0f, 1.0f};
  float xaxisanglem = 0.0f;
  float yaxisanglem = 0.0f;
  float zaxisanglem = 0.0f;
  float scalem = 1.0f;
  GameObject(std::string path) {
    this->path = path;
  }
	void set_location(std::vector<float> &input_pose) {
		for (int i{}; i < 16; i++) {
			this->GOmodelmat[(int)i / 4][i % 4] = input_pose[i];
		}
		for (int i{16}; i < 19; i++){
			this->tvecm[i-16] = input_pose[i];
		}
		for (int i{19}; i < 22; i++){
			this->svecm[i-19] = input_pose[i];
		}
		this->xaxisanglem = input_pose[22];
		this->yaxisanglem = input_pose[23];
		this->zaxisanglem = input_pose[24];
		this->scalem = input_pose[25];
		return;
	}
	

	std::vector<float> get_pose() {
		std::vector<float> return_pose{};
		for (int i{}; i < 16; i++) {
			return_pose.push_back(this->GOmodelmat[(int)i / 4][i % 4]);
		}
		for (int i{16}; i < 19; i++){
			return_pose.push_back(this->tvecm[i-16]);
		}
		for (int i{19}; i < 22; i++){
			return_pose.push_back(this->svecm[i-19]);
		}
		return_pose.push_back(this->xaxisanglem);
		return_pose.push_back(this->yaxisanglem);
		return_pose.push_back(this->zaxisanglem);
		return_pose.push_back(this->scalem);
		return return_pose;
	}
};

void Copy(std::wstring input_path, int input_path_len){
    std::string models_folder = "C:/Users/Dell/Desktop/Models/";//Enter Path to your Models Folder
    std::string fileName {};
    std::string inputFolderPath{};
    int last_index {};
    int i {};
    int last_j_index {};
    for (auto x: input_path){
        if (x=='/'){
            last_index = i;
        }
        if (x=='j'){
            last_j_index = i;
        }
        i++;
    }
    for (int j {}; j < last_index+1;j++){
        inputFolderPath += (char)input_path[j];
    }
    std::cout << "last J index : " << last_j_index << std::endl;
    for (int j {last_index+1}; j < last_j_index-3; j++){
        fileName = fileName + (char)input_path[j];
    }
    std::string folderPath = models_folder+fileName;
    // std::cout << "Input Path : " << input_path << std::endl;
    std::cout << "File Name : " << fileName << std::endl;
    std::cout << "Input Folder Path : " << inputFolderPath << std::endl;
    std::cout << "Last / Detected at : " << last_index << std::endl;
    std::cout << "Folder Path : " << folderPath << std::endl;
    std::cout << "Len File Name : " << fileName.size() << std::endl;
    createFolder(folderPath.c_str());
    std::vector<std::string> files = listdir(inputFolderPath.c_str());

    for (int i {}; i < files.size(); i++){
        std::wstringstream wideStream;
        std::string destination_folder = folderPath+'/'+files[i];
        std::cout << "Paste Path : " << destination_folder << std::endl;
        std::cout << "Paste path size : " << destination_folder.size() << std::endl;
        wideStream << std::wstring(destination_folder.begin(), destination_folder.end());
        std::wstring wideString = wideStream.str();
        LPCWSTR finalDestination = wideString.c_str();
        std::string final_input_path = inputFolderPath + files[i];
        std::cout << "Copy Path : " << final_input_path << std::endl;
        std::cout << "Copy path size : " << final_input_path.size() << std::endl;
        std::wstringstream wideStream2;
        wideStream2 << std::wstring(final_input_path.begin(),final_input_path.end());
        std::wstring wideString2 = wideStream2.str();
        LPCWSTR copy_from_path = wideString2.c_str();

        BOOL success3 = CopyFileW(copy_from_path, finalDestination, TRUE);

        if (success3) {
            std::wcout << L"File copied successfully." << std::endl;
        } else {
            DWORD errorCode = GetLastError();
            if(errorCode == 80){
                BOOL success = DeleteFileW(finalDestination);
                std::cout << "DELETED SUCCESSFULLY : " << success << std::endl;
                BOOL success2 = CopyFileW(copy_from_path, finalDestination, TRUE);
                if (success2){
                    std::cout << "COPIED SUCCESFULY" << std::endl;
                }
                else{
                    errorCode = GetLastError();
                    std::cerr << "Failed to copy file. Error code: " << errorCode << std::endl;
                }
            }else{
                errorCode = GetLastError();
                std::cerr << "Failed to copy file. Error code: " << errorCode << std::endl;
            }
        }
    }
}
GameObject* createNewGameObject(){

    OPENFILENAME ofn;
    TCHAR szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // If you have a window handle, specify it here.
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(*szFile);
    ofn.lpstrFilter = _T("Wavefront Object Files (*.obj)\0*.obj\0All Files (*.*)\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    if (GetOpenFileName(&ofn) == TRUE) {
        // The user selected a file. The selected file path is in szFile.
        MessageBox(NULL, szFile, _T("Selected File"), MB_OK | MB_ICONINFORMATION);
    } else {
        // The user canceled the dialog.
        MessageBox(NULL, _T("No file selected."), _T("Canceled"), MB_OK | MB_ICONEXCLAMATION);
    }
    int i {};
    std::string path {};
    for (auto x: szFile){
        if (x == '\\'){
            path += '/';
        }else{
            path+=x;
        }
    }
    std::wstringstream wideStream;
    wideStream << std::wstring(path.begin(), path.end()); // Convert to wide string
    std::wstring wideString = wideStream.str();   
    Copy(wideString,path.size());
    return nullptr;
}
int main() {
    const wchar_t* sourcePathWide = L"C:/Users/Dell/Desktop/trial/bugatti/README.txt";
    const wchar_t* destinationPathWide = L"C:/Users/Dell/Desktop/Models/bugatti/README.txt";

    GameObject* del = createNewGameObject();
    BOOL success3 = CopyFileW(sourcePathWide, destinationPathWide, TRUE);

    if (success3) {
        std::wcout << L"File copied successfully." << std::endl;
    } else {
        DWORD errorCode = GetLastError();
        if(errorCode == 80){
            BOOL success = DeleteFileW(destinationPathWide);
            std::cout << "DELETED SUCCESSFULLY : " << success << std::endl;
            BOOL success2 = CopyFileW(sourcePathWide, destinationPathWide, TRUE);
            if (success2){
                std::cout << "COPIED SUCCESFULY" << std::endl;
            }
            else{
                errorCode = GetLastError();
                std::cerr << "Failed to copy file. Error code: " << errorCode << std::endl;
            }
        }else{
            errorCode = GetLastError();
            std::cerr << "Failed to copy file. Error code: " << errorCode << std::endl;
        }
    }

    return 0;
}
