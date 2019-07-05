CXX = g++
CXXFLAGS = -g
main: main.o gridworld.o actionSpace.o network.o neuron.o
	$(CXX) $(CXXFLAGS) -o main main.o gridworld.o actionSpace.o network.o neuron.o
main.o: main.cpp gridworld/gridworld.h gridworld/actionSpace.hpp snn/network.h
	$(CXX) $(CXXFLAGS) -c main.cpp
gridworld.o: gridworld/gridworld.h gridworld/actionSpace.hpp
	$(CXX) $(CXXFLAGS) -c gridworld/gridworld.cpp
actionSpace.o: gridworld/actionSpace.hpp
	$(CXX) $(CXXFLAGS) -c gridworld/actionSpace.cpp
network.o: snn/network.h snn/neuron.h snn/hyperparams_neuron.hpp
	$(CXX) $(CXXFLAGS) -c snn/network.cpp
neuron.o: snn/neuron.h snn/hyperparams_neuron.hpp
	$(CXX) $(CXXFLAGS) -c snn/neuron.cpp



