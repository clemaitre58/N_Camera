#include "src/common/interestpoint.h"
#include "src/common/ImportDesc.h"

#include <iostream>

int main() 
{
 	//typedef util::threading::Thread thread_type;

	/*const uint32 skip = 150;
	sensor::FrameInfo info;
	sensor::IOFrame<uint16> ioframe;
	sensor::IrFrame frame1,frame2;
	g2d::ImgScene scene1,scene2;
	g2d::Viewer viewer1,viewer2;

	algo::FastHessianDetector detector;
	algo::SurfDescriptor surf;*/
	core::InterestPointVector<> pts1,pts2;
	core::InterestPair<> pair;

	/*std::wstring dir = L"/Users/c.andre/Documents/ergocycle/data/cyclist/";
	std::wstring filename = L"ir_cyclist1.bin";
	filename = dir + filename;

	ioframe.filename(filename.c_str());
	ioframe.read_info(info);

	int32 width = info.width;
	int32 height = info.height;
	// Init scene
	scene1.size(width, height);
	scene2.size(width, height);

	scene1.lut().load(core::Rgb(color::black),
		core::Rgb(color::white), 512);
	scene1.lut().range(150, 15000);

	scene2.lut().load(core::Rgb(color::black),
		core::Rgb(color::white), 512);
	scene2.lut().range(150, 15000);

	if (!ioframe.is_open() || !ioframe.read(frame1))
		return;

	core::Matrix<uint16> sframe(height, width, nullptr, frame1.data());

	detector.set_image(sframe);
	surf.integral_image(detector.integral_image());
	detector.find(pts1);
	surf.describe(pts1);

	for (uint32 i = 0; i < skip; ++i)
		ioframe.read(frame2);
	if (!ioframe.read(frame2))
		return;

	sframe.init(height, width, nullptr, frame2.data());
	detector.set_image(sframe);
	surf.integral_image(detector.integral_image());
	detector.find(pts2);
	surf.describe(pts2);*/
	std::string file_name = "img1.haraff.sift";
	ImportDesc reader_desc(file_name);
	int32_t nb_reg = reader_desc.GetNumReg();
	int32_t nb_feat = reader_desc.GetNumFeat();
	std::vector<std::vector<int32_t > > data_feat = reader_desc.GetFeat();
	std::cout << "Nombre de régions : " << nb_reg << "\n";
	std::cout << "Nombre de dimensions : " << nb_feat << "\n";

	for(int32_t i=0; i<nb_reg; i++){
		for(int32_t j=0; j<nb_feat; j++){
		std::cout << data_feat[i][j];
		}
	std::cout << "\n";
	}

	//core::Matching(pts1, pts2, pair,0.75f,50);
	/*pts1.clear();
	pts2.clear();
	for (const auto& p : pair)
	{
		pts1.push_back(p.first);
		pts2.push_back(p.second);
	}*/

	/*g2d::Scene::pointer_type shape1(new g2d::IptsShape(pts1));
	scene1.push_back(shape1);

	g2d::Scene::pointer_type shape2(new g2d::IptsShape(pts2));
	scene2.push_back(shape2);

	scene1.set_buffer(frame1.data(), frame1.size());
	scene2.set_buffer(frame2.data(), frame2.size());

	//viewer1.show(&scene1);
	thread_type thread1(&g2d::Viewer::show, &viewer1, &scene1);
	thread_type thread2(&g2d::Viewer::show, &viewer2, &scene2);

	thread1.join();
	thread2.join();*/
    return 0;
}
