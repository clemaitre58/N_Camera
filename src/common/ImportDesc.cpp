#include "ImportDesc.h"
#include <vector>

ImportDesc::ImportDesc(std::string file_name)
{
file_name_ = file_name;
}

ImportDesc::~ImportDesc()
{
if(inline_.is_open()) inline_.close();
}

void ImportDesc::OpenFile(){
inline_.open(file_name_, std::ifstream::in);
}

void ImportDesc::ReadNumFeat(){
inline_ >> num_feat_ ;
}

void ImportDesc::ReadNumReg(){
inline_ >> num_reg_ ;
}

void ImportDesc::ReadNumData(){

for(int i=0; i<num_reg_; i++){
	std::vector<int32_t > tab_feat;
	for(int j; j<num_feat_; j++){
		int32_t temp_val;
		inline_ >> temp_val;
		tab_feat.push_back(temp_val);
	}
	feat_data_.push_back(tab_feat);
}
}

int32_t ImportDesc::GetNumFeat(){return num_feat_;}

int32_t ImportDesc::GetNumReg(){return num_reg_;}

std::vector<std::vector <int32_t> > ImportDesc::GetFeat(){return feat_data_;}

void ImportDesc::Read(){

	OpenFile();
	ReadNumFeat();
	ReadNumReg();
	ReadNumData();
}
