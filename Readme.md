# Find No Light

## Introduction

Find No Light is a simple project that uses Arduino and a neural network to find regions without light. The neural network used is simple: it is a multilayer perceptron and uses supervised learning.

## Operation

There are three phototransistors and a motor servo. The inputs of the neural network are the returned values of each phototransistor (interval between 0 and 1023) and the output is the angle which motor servo will do.

### Circuit

The circuit is easy to make! You will need:
 - 1 Arduino;
 - 3 phototransistors;
 - 1 motor servo;
 - 1 capacitor - 100 μF;
 - 3 resistors - 10 kΩ;
 - Some wires.

![circuit](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/circuit.png)

*Note: The resistors are really important! They do not allow many electrons to pass through, otherwise this will damage the circuit. Another thing is the capacitor; as the Arduino uses a lot of energy, it serves to maintain the energy balance on the board.*

### The Neural Network 

#### Configuration
The neural network is a multilayer perceptron. It has 8 neurons, 16 weights and 5 bias. For more details, check the table.

| Configuration            | Values        | 
| ------------------------ |:------------- | 
| Activation Function      | reLU          |
| Programming Language     | C++           |
| Inputs (x3)              | [0, 1023]     |
| Output                   | [0, 179]      |
| Learning Rate            | 1 * 10e-8     |
| Training time            | ≈ 1 min       |

*Note: The training time can be faster or slower depending on your Arduino. Besides that, if the learning rate is lower, the training time will be longer.*

***

For further illustration, a GIF is provided with the representation of the neurons and connections, along with subtitles.

![neural_map](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/neural_network.gif)

#### Calculations

##### Feed Forward

When we give three inputs, the neural network returns one output. This process is called __feed forward__. The feed forward can be expressed with one equation like this:

![feed_forward](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/formula1.png)

For each neuron in the hidden layer, there is a sum of the inputs multiplied by their respective weights. After that, the bias is added, and then the value goes through the activation function, returning the neuron-hidden output. The final output is same process, but the inputs will be the hidden neurons.

##### Back-propagation

For the neural network to learn, it will be named the "Gradient descent", which in turn constitutes the __back-propagation__.

First, we need to compute how much the neural network is failing, given your weights. For this, we will have a __cost function__, expressed by this equation:

![cost_function](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/formula2.png)

*T* is the target (the value that we expect to come out), and *o* is the output of the neural network.

The mission now is to be able to determine the value of the weights where the cost function is low. For that, we have to calculate the derivative of the cost function in relation to the weights. This mathematical expression is given by:

![dCost_dwij](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/formula3.png)

We can write all weights and bias with a row vector:

![w_row_vector](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/formula5.png)

And we can write all the derivatives by the gradient of the cost function given by row vector.

![gradient_of_cost](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/formula6.png)

With these tools, we can update our row vector using this expression:

![new_row_vector](https://github.com/AndrePinheiroPT/FindNoLight/blob/main/img/formula4.png)

__W(i+1)__ is the new row vector, __W(i)__ is the old row vector and __ν__ is the learning rate. 

***

For more information, check out this [webpage](https://en.wikipedia.org/wiki/Artificial_neural_network)!













