CC = gcc
CCPP = g++
NVCC = /usr/local/cuda-11.6/bin/nvcc

INCLUDE = ../../../
DEFINES = -DUSE_ZLIB

OPTFLAGS = -O2 -std=c++2a -Wall 

NVFLAGS = -I $(INCLUDE) -I $(EXTRAI) -Xcompiler -O2 -L/usr/local/cuda-11.6/lib64 -lcuda -lstdc++ -lcudart -dc -arch=sm_86 --std=c++17 
NVLINKFLAGS = -L/usr/local/cuda-11.6/lib64 -lcuda -lcudart
#-lstdc++

CPPFLAGS = $(OPTFLAGS) -I $(INCLUDE) $(DEFINES)
LINKFLAGS = -lz 

WXWIDGETSFLAGS = `wx-config --libs --cxxflags --cppflags`
WXWIDGETSLINKFLAGS = `wx-config --libs`

MAGICKFLAGS = `Magick++-config --cxxflags --cppflags`
MAGICKLINKFLAGS = `Magick++-config --ldflags --libs`

NVCCOBJS = src/testDisplay.o \
	src/BasicLayerList.o \
	src/BasicLayer.o \
	src/BasicWeight.o \
	src/activationFunctions.o \
	src/Matrix3D.o

CPPOBJS = src/imageUtil.o

all: linkCPU

linkCPU: $(CPPOBJS) $(NVCCOBJS) src/gpuCode.o
	$(CCPP) $(CPPFLAGS) -o testDisplay.out  $^ $(LINKFLAGS) $(NVLINKFLAGS) $(MAGICKLINKFLAGS) $(WXWIDGETSLINKFLAGS)

src/gpuCode.o: $(NVCCOBJS)
	$(NVCC) --device-link -arch=sm_86 -o $@ $^ $(LINKFLAGS) $(NVLINKFLAGS) $(CPPOBJS)

src/imageUtil.o: $(INCLUDE)Image_Manipulation/util/imageUtil.cpp $(INCLUDE)Image_Manipulation/util/imageUtil.hpp 
	$(CCPP) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

src/Matrix3D.o: $(INCLUDE)coreutils/classes/matrixes/Matrix3D.cu
	$(NVCC) $(NVFLAGS) $< -o $@

src/activationFunctions.o: $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/functions/activationFunctions.cu $(INCLUDE)coreutils/classes/matrixes/Matrix3D.cuh
	$(NVCC) $(NVFLAGS) $< -o $@

src/BasicWeight.o: $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/classes/weights/BasicWeight.cu $(INCLUDE)coreutils/classes/matrixes/Matrix3D.cuh
	$(NVCC) $(NVFLAGS) $< -o $@

src/BasicLayer.o: $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/classes/layers/BasicLayer.cu $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/classes/weights/BasicWeight.cuh $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/functions/activationFunctions.cuh $(INCLUDE)coreutils/classes/matrixes/Matrix3D.cuh
	$(NVCC) $(NVFLAGS) $< -o $@

src/BasicLayerList.o: $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/classes/layerLists/BasicLayerList.cu $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/classes/layers/BasicLayer.cuh $(INCLUDE)coreutils/classes/matrixes/Matrix3D.cuh
	$(NVCC) $(NVFLAGS) $< -o $@

src/testDisplay.o : testDisplay.cpp  $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/basicLearningTypes/generationalAIBasic.cu $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/classes/layerLists/BasicLayerList.cuh $(INCLUDE)AI_Simple_CUDA/artificialIntelligence/basicLearningTypes/generationalAIBasic.cuh $(INCLUDE)coreutils/classes/matrixes/Matrix3D.cuh
	$(CCPP) $(CPPFLAGS) -c $< -o $@ $(WXWIDGETSFLAGS) $(MAGICKFLAGS)

clean1: 
	rm -f src/*.o ./testDisplay.out

clean: 
	rm -f ./testDisplay.out