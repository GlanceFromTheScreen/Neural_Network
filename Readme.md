# Neural Network uses Back propagation method to recognize handwritten numbers

# Network parametrs (change it in main.cpp):
	1) amount of layers (now is 3)
	2) amount of neurons in each layer (now is 784, 20, 10)
        3) amount of learn images: from 1 to 60000 (now is 1000)
        4) amount of tests: from 1 to 10000 (now is 1000)
        5) amount of generations: change it by changing the amount of loop steps (now is 5)
        6) "step" and "alfa" numbers: a) step influence the learning speed (now is from 10^1 to 10^-3)
                                      b) alfa is from 0 to 1 (now is 0.7)
        7) files directories

# Example of output:

Generation 1 Total score: 42.3% Time: 16.598 seconds
Generation 2 Total score: 64.8% Time: 10.238 seconds
Generation 3 Total score: 66.7% Time: 10.762 seconds
Generation 4 Total score: 67.3% Time: 10.707 seconds
Generation 5 Total score: 67.3% Time: 10.442 seconds

# The best result I got: 91.08%  
# Parametrs of my best result:
	1) 3
	2) 784, 20, 10
        3) 60000
        4) 10000
        5) 5
        6) a) now is from 10^1 to 10^-3
           b) 0.7

# Future updetes:
	1) optimize the structure and logic of code
	2) add the procedure, rhat would cycle through different parametrs values of the network and choose the best ones
 	3) add the visualization: user writes a number on a screen, and program recognize it as a number




