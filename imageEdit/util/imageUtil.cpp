#include <string>
#include <coreutils/functions/cli/accessCli.hpp>

using namespace coreutils::functions;

namespace imageEdit {
   namespace util {
		std::string imageFromFileHandler () {
			std::string inputImagePath = cli::exec("zenity --file-selection");
			return inputImagePath.substr(0, inputImagePath.length() - 1);
		}
	}
}