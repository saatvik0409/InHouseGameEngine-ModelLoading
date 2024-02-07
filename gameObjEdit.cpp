	/*
		void set_location(std::vector<float> &input_pose) {
			for (int i{}; i < 16; i++) {
				GOmodelmat[(int)i / 4][i % 4] = input_pose[i];
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
	

		std::vector<float> get_location() {
			std::vector<float> return_pose{};
			for (int i{}; i < 16; i++) {
				return_pose.push_back(this->GOModelmat[(int)i / 4][i % 4]);
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
            return_pose.push_back(this->)
			return return_pose;
		}
	*/