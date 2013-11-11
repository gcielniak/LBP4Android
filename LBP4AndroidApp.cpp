#include <iostream>
#include <fstream>
#include "LBPFeature.h"

using namespace std;

void print_help()
{
	cerr << "LBP4Android usage:" << endl;

	cerr << " -ic : input color image" << endl;
	cerr << " -or : output file in raw format" << endl;
	cerr << " -ox : output file in xml (opencv) format" << endl;
	cerr << " -pd : pyramid depth [deafult: -1, max]" << endl;
	cerr << " -vo : verbose off" << endl;
	//additional lines
}

int main(int argc, char **argv)
{
	string color_file_name = "";
	string output_raw_file_name = "";
	string output_xml_file_name = "";
	int pyramid_depth = -1;
	bool verbose = true;

	if (argc == 1)
	{
		print_help();
		return 0;
	}

	for (int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i],"-ic")==0) && (i < (argc-1))) { color_file_name = argv[++i]; }
		else if ((strcmp(argv[i],"-or")==0) && (i < (argc-1))) { output_raw_file_name = argv[++i]; }
		else if ((strcmp(argv[i],"-ox")==0) && (i < (argc-1))) { output_xml_file_name = argv[++i]; }
		else if ((strcmp(argv[i],"-pd")==0) && (i < (argc-1))) { pyramid_depth = atoi(argv[++i]); }
		else if (strcmp(argv[i],"-vo")==0) { verbose = false; }
		else if (strcmp(argv[i],"-h")==0)	{ print_help();	}
	}

	cv::Mat color_image;
	cv::Mat color_feature;

	LinLib::LBPFeature feature;

	//load the specified image
	cv::Mat color_frame = cv::imread(color_file_name, CV_LOAD_IMAGE_GRAYSCALE);
	if (!color_frame.data)
	{
		cerr << "Error loading the input image." << endl;
		return 0;
	}

	//extract features
	color_feature = feature.Get(color_frame, pyramid_depth);

	//save features in xml (opencv format)
	if (output_xml_file_name.compare("")!=0)
	{
		if (verbose)
			cerr << "Writing data in xml format... ";

		cv::FileStorage file_storage;
		file_storage.open(output_xml_file_name, cv::FileStorage::WRITE);
		file_storage << "color_features" << color_feature;
		file_storage.release();

		if (verbose)
			cerr << "done." << endl;
	}

	//save features in raw format (Oscar compatible :) )
	if (output_raw_file_name.compare("")!=0)
	{
		if (verbose)
			cerr << "Writing data in raw format... ";

		ofstream file;
		file.open(output_raw_file_name.c_str());
		for (int i = 0; i < color_feature.cols; i++)
			file << color_feature.at<float>(0,i) << " ";
		file << endl;
		file.close();

		if (verbose)
			cerr << "done." << endl;
	}
	return 0;
}
