#ifndef IMPORTDESC_H
#define IMPORTDESC_H

#include <fstream>
#include <vector>

class ImportDesc {

  public:
	// var
	// funct
	int32_t GetNumFeat();
	int32_t GetNumReg();
	std::vector<std::vector <int32_t> > GetFeat();
	void Read();
	ImportDesc(std::string file_name);
	~ImportDesc();
  private:
	// var
	std::string file_name_;
	std::ifstream inline_;
	std::vector<std::vector <int32_t> > feat_data_;
	int32_t num_feat_;
	int32_t num_reg_;
	// funct
	void OpenFile();
	void ReadNumFeat();
	void ReadNumReg();
	void ReadNumData();
};




#endif


