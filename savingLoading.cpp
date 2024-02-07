#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// Example using SQLite
// #include "sqlite3.h"

// int main() {
//     float myFloat = 3.14f;

//     // Open or create a database
//     sqlite3* db;
//     sqlite3_open("mydatabase.db", &db);

//     // Create a table
//     sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS FloatTable (Value REAL);",
//     0, 0, 0);

//     // Insert float into the table
//     sqlite3_exec(db, ("INSERT INTO FloatTable (Value) VALUES (" +
//     std::to_string(myFloat) + ");").c_str(), 0, 0, 0);

//     // Query and retrieve the float
//     float readFloat{};
//     sqlite3_exec(db, "SELECT Value FROM FloatTable;", [](void* data, int
//     argc, char** argv, char** /*azColName*/) {
//         float& localReadFloat = *static_cast<float*>(data);

//         if (argc > 0 && argv[0]) {
//             localReadFloat = std::stof(argv[0]);
//         }

//         return 0;
//     }, &readFloat, 0);

//     std::cout << "Read float: " << readFloat << std::endl;

//     // Close the database
//     sqlite3_close(db);

//     return 0;
//// }

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

class saving_loading {

public:
  saving_loading() {}

  void saving(std::vector<GameObject*> &inputObject) {
    std::ofstream file;
    file.open("myFile.txt");
    for (int k{}; k < inputObject.size(); k++) {
      std::string path = inputObject[k]->path;
      std::vector<float> current_mat = inputObject[k]->get_pose();
      file << path;
      file << "\n";
      for (int i{}; i < 26; i++) {
        file << current_mat[i];
        file << " ";
      }
      file << "\n";
    }
    file.close();
    return;
  }

  std::vector<GameObject *> loading() {
    std::ifstream file("myFile.txt");
    std::string line{};
    std::vector<GameObject *> ret_vector{};
    if (file.is_open()) {
      while (getline(file, line)) {

        std::vector<float> inputPose {};
        getline(file, line);
        std::istringstream iss(line);
        float floatValue{};
        int i{};
        while (i < 27) {
          iss >> floatValue;
          inputPose.push_back(floatValue);
          i++;
        }
        // gameObject->specifications = arr;
        GameObject *gameObject = new GameObject(line,input_pose[26]);
        gameObject->set_location(inputPose);
        ret_vector.push_back(gameObject);
      }
      file.close();
    } else {
      std::cout << "file is not open"
                << "\n";
    }
    return ret_vector;
  }
};

int main() {
  saving_loading *sl_ins = new saving_loading();
  std::vector<GameObject *> ret_ve = sl_ins->loading();
  // GameObject *g1 = new GameObject("Telo");
  // GameObject *g2 = new GameObject("Helo");
  // GameObject *g3 = new GameObject("Belo");
  // std::vector<GameObject *> save_vec{g1, g2, g3};

  // sl_ins->saving(save_vec);
  // ret_ve = sl_ins->loading();
  // for (int i{}; i < ret_ve.size(); i++) {
  //   std::cout << ret_ve[i]->path << std::endl;
  //   for (int x{}; x < 16; x++) {
  //     std::cout << ret_ve[i]->GOmodelmat[(int)x/4][x%4] << " ";
  //     if ((x+1)%4 == 0){
  //       std::cout << std::endl;
  //     }
  //   }
  //   std::cout << std::endl;
  //   for (int i {}; i < 3; i++){
  //     std::cout << ret_ve[i]->tvecm[i] << " ";
  //   }
  //   std::cout << std::endl;
  //   for (int i{}; i < 3; i++){
  //     std::cout << ret_ve[i]->svecm[i] << " ";
  //   }
  //   std::cout <<std::endl;
  //   std::cout << std::endl;
  // }
  for (int i{}; i < ret_ve.size(); i++) {
    for (int x {}; x < 16; x++){
      int m = i%2==0 ? x:15-x;
      ret_ve[i]->GOmodelmat[(int)x/4][x%4] = m*0.5;
    }
    for (int x{}; x < 3; x++){
      int m = i%2==0? 3-x:x;
      int n = 3-m;
      ret_ve[i]->tvecm[i] = m*0.5;
      ret_ve[i]->svecm[i] = n*0.5;
    }
  }
  sl_ins->saving(ret_ve);
  ret_ve.clear();
  ret_ve = sl_ins->loading();
  for (int i{}; i < ret_ve.size(); i++) {
    std::cout << ret_ve[i]->path << std::endl;
    for (int x{}; x < 16; x++) {
      std::cout << ret_ve[i]->GOmodelmat[(int)x/4][x%4] << " ";
      if ((x+1)%4 == 0){
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
    for (int i {}; i < 3; i++){
      std::cout << ret_ve[i]->tvecm[i] << " ";
    }
    std::cout << std::endl;
    for (int i{}; i < 3; i++){
      std::cout << ret_ve[i]->svecm[i] << " ";
    }
    std::cout <<std::endl;
    std::cout << std::endl;
  }
  return 0;
}
