# Background

Differentiation has its applications everywhere from finding zeros of functions to the back propagation algorithm in Deep Neural Networks. In this repository, we implement a library that uses Automatic Differentiation to find the derivatives of real and vector valued functions.

## Why Automatic Differentiation

The other prominent choices for implementing differentiation are __Symbolic Differentiation__ and __Finite Difference__. However, both methods have their drawbacks.
* __Symbolic Differentiation__ - This involves breaking down a given expression into subsequently simpler expressions and we are able to achieve machine precision. However, in doing so, this method tends to be slow and expensive to evaluate.
* __Finite Difference__ - Relies on the Taylor Series expansion and is very fast to evaluate. However, it suffers from poor accuracy, owing to a difficulty in selecting an appropriate value to represent h:
![finite difference](./assets/finite_difference.png)

Automatic Differentiation overcomes both these limitations.

## How it Works

### Dual Numbers

### AD Modes

## Implementation Approach