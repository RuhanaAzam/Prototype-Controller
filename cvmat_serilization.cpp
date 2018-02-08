#include <opencv2/opencv.hpp>
#include<boost/serialization/split_free.hpp>
#include<boost/serialization/vector.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::cv::Mat)

namespace boost { 
	namespace serialization {
		template
		void save(archive & ar, cv::Mat& m, const unsigned int file_version) {
			ar & m.cols;
			ar & m.rows;
			ar & m.size;
			ar & m.flags;
		
		}

	}
}