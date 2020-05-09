
# My AI notes and remarks

This file contains notes, remarks collected in years and years. I had to refresh some concepts and theory before doing this fun project. Hope this short tutorial will help you to understand AI and deep learning better. 

This is a learn-by-doing tutorial and every step of project is there documented and explained in detail, with math and theory.

## Basics - theory

Artificial Intelligence (AI) is a way to make a computer acting like a human. Of course, a program can always be written. For example I can write a program to do a simple sum *a+b* with just an instruction. However this is not intelligence because I am telling the computer what I want and the computer is doing that. Nothing else.

We have learned what a sum is when children, counting with fingers. Would it be possible a computer doing that like us?

Our brain is, essentialy, a sort of *elecrtonic processor*. Neurons are connected each other by *synapsis* and electric signals are sent between one and the other neuron through those connections. If a neuron is *activated* from incoming electric signals (mV, millivolts) then an electric signal is produced and propagated through the other connections. 

![](https://en.wikipedia.org/wiki/Biological_neuron_model#/media/File:Neuron3.png)
*Image from Wikipedia*

Such model can be easly converted in a program and the electric processes behind can be enough well translated into math. 

## Machine learning

One way to learn a computer how to solve problems is through Neural Networks (it is not the only way, but I think the most interesting one!).

Essentialy a Neural Network (NN) is a program that acts like neurons connected each other and **simulating** the human thinking/learning. In fact a neural network can *adjust* itself internal calculations in order to produce the expected results.

Given an input the network will try to produce an output. The output is just a series of calculations (computers are good in that!) that could be right or not.

Those results are then measured (compared to an expected value) and error is calculated. If error is more than a desidered threshold, this information is *"sent back"* in the program in order to produce a better calculation/result.

Doing that for many, many times (**epochs**) will led to an enough precise result (error is lower each time).

Essentialy the computer, providing a good program, could reproduce our way of learning things. In fact we learn, for example, what a cat is and then we are able to say "*yes this is a cat*". Then we can learn what is a Siamese cat and distinguish Siamese from Russian Blue for example. But this is done step-by-step (in fact, if we would not be able to say what a cat is, would be very difficult to say if this is a Siamese).

Through a computer program we have to give, for example, a cat image as input. The output should be "yes" or "no" (is a cat or not classification). But we do not want to write each single line of code to recognize a cat or hash all world's cat pics to a big dictionary with yes/no answers. 

We'd like to write a particular algorithm that given any pic as input will produce yes/no as output and that this algorithm will **automatically** adjust itself in order to learn what a cat is. Then, when we are satistfacted, this **model** of calculations can be used with all images we like. We are not interested in telling the computer what a cat is but we aim to teach the computer how a cat can be recognized.

This is, essentialy, machine learning: computer will be able to learn and adjust its knowledge itself. This can be done with statistics, math, and many other ways. But the most interesting one is Neural Networks, algorithms capable to simulate human brain.

## What is a Neural Network (NN)

### Basics

Neural Network concept is creating a data structure with neurons connected each other. Neurons wait for our input and calculations inside the network will produce an output. 

Like explained before, a neuron is a "unit" connected to other neuros. Neuros can be active or not and its signals are sent as millivolts to other neuros. Other neurons take those input signals and they can activate or not. And so on... million and million times.

Translating that into informatics: we have a set of neurons (a **layer** of neurons). They take an input and have connections to other neurons (**synapsis**). Input is translated into electric signal (**weighted**) and basing on that value, through an **activation function** the neuron output is (sent) **propagated** to the other layers. 

The first layer is the **input layer** (where we define one or more input for the network), then one (or more) **hidden layers** of neurons (may be **fully connected**) elaborate inputs and produces an output for the next layer. The final layer is the **output layer** (that could be one or more).

Simple network:

![](https://miro.medium.com/max/640/0*Bqpea_57RtV-kJ6D.webp)
*image from https://miro.medium.com*

A neural network without any hidden layer (so only input and output) is called **Perceptron**
A neural network with more than one hidden layer is called **Deep Neural Network (DNN)** and, as the name states, is used in the **Deep Learning**.

Translating it into simple informatics, a neuron "value" (the circles) can be C++ *objects*. Each object is connected to others (*pointers*). There will be a "value" (*double*) calculated by a function (*activation function*) and this value will be sent through connections to the other neurons. Of course the sent value could not be the same in each connection and to obtain this we can add a factor called **weight** (another *double*).

In schematics:

![](https://miro.medium.com/max/640/0*87ax_yzYZp-OUkFL.webp])
*image from https://miro.medium.com*

So, this is easy to translate in C++, you can find it in the [header file](components/briand_ai/include/BriandNN.hxx)

Generally, if we have a neuron $O$ receiving inputs from $n$ neurons having value of $I$ its "value" (output of the connected neurons) is  given by the easy formula of weighted sum:

$$ O = w_{1} * I_{1} + w_{2} * I_{2} + w_{3} * I_{3} + ... + w_{n} * I_{n} $$

Where:

 - $i$ is the neuron $i$ of $n$
 - $w_{i}$ is the weight assigned to the connection $i$
 - $I_{i}$ is the "value" of the neuron $i$

But... if all weights or inputs in a certain moment are all zero? The sum will be zero. And this 0 will be **propagated** to all other, making always output equal to zero. How to avoid this? It's simple, we can add a **bias** in one, two, or all layers (excluding output layer). A bias is a "standalone" neuron who has no inputs but is fully connected to all other neurons in the layer he lies.
