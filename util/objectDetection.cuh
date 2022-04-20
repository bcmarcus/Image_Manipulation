#ifndef OBJECT_DETECTION
#define OBJECT_DETECTION

#include <string>

namespace imageEdit {
	namespace util {
		std::string detectObject (std::string inputFilePath, int modelNumber);
	}
}

#endif