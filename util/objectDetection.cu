#include "objectDetection.cuh"

#include <AI_Simple_CUDA/artificialIntelligence/classes/layerLists/BasicLayerList.cuh>
#include <coreutils/functions/cli/accessCli.hpp>

#include <fstream>

using namespace std;
using namespace coreutils::functions;

namespace imageEdit {
	namespace util {
		std::string detectObject (std::string inputFilePath, int modelNumber){

			if (modelNumber == 0 || modelNumber == 1) {
				BasicLayerList* model = nullptr;
				std::ifstream indexToAnswerFile;
				std::string modelPath;
				std::string indexToAnswerFilePath;
				if (modelNumber == 0) {
					//use mnist dataset
					modelPath = "";
					indexToAnswerFilePath = "";
				}
				if (modelNumber == 1) {
					// use animal dataset
					modelPath = "";
					indexToAnswerFilePath = "";
				}
				model = new BasicLayerList (modelPath);
				indexToAnswerFile = ifstream (indexToAnswerFilePath);

				int numOutputs = model->getLast()->getLayer()->getHeight();
				int amountShown = 5;
				
				string line;
				// std::string *indexToAnswerMap = makeIndexArray(numOutputs, indexToAnswerFile);

				std::string type;
				if (model->getRoot()->getLayer()->getLength() == 1) {
					type = "BW";
				} else if (model->getRoot()->getLayer()->getLength() == 3) {
					type = "RGB";
				} else if (model->getRoot()->getLayer()->getLength() == 4) {
					type = "RGBA";
				} else {
					std::cout << "Invalid model, invalid input length";
					exit (1);
				}





				// use the model for a test
			} else if (modelNumber == 2) {
				// use clip
			}
			
			return "";
		}
	}
}