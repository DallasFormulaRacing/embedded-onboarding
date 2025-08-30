# Introduction

This document assumes you have read `analog_filtering.md`.
Digital filtering is a conceptual extension of analog filtering, since it requires a stronger understanding of the calculus that drives the process of filtering.

Digital filtering is the process of filtering in the *digital domain*.
The general idea is to sample a voltage with an ADC through time, then mathematically process it to filter out noise.
The purpose of filtering in the digital domain is to build filters that are not possible to build with analog components.

Digital filters can be built to have special properties that are advantageous to the application.
These properties include:
 - Linear phase response
 - Ideal or arbitrary magnitude response

# Digital Filter Implementations

## Mathematical Relationship between the Input and Output Voltage
The most important result from the section on the Mathematical Basis for Digital Filtering is the following mathematical algorithm:

$$v_{out}(n)=\sum_{i=0}^{a}v_{in}(i)h(n-i)$$

$$v_{out}(n) = v_{in}(0)h(a) + v_{in}(1)h(a-1) + \cdots +v(a)h(0)$$

This shows the relationship between the input voltage, the transfer function (aka the filter kernel $h(n)$ ).
This mathematical process is called a *convolution*, which is a series of *Multiply and Accumulate* operations.
See the Mathematical Basis for Digital Filtering section for details.

## Data Flow through a Digital Filter

Here are the steps that describe how data is processed in a digital filter:

 1. Data populates an $a$ point long buffer.
 2. While data is filling the buffer, invalid convolutions are being computed, so these outputs are discarded.
 3. When the buffer is full, the MAC is performed on the entire buffer with the entire filter kernel.
 4. When this happens, the first valid $v_{out}(n)$ point is created.
 5. This buffer is a First In, First Out (FIFO) buffer, so after the first valid complete MAC, the next $v_{in}$ point is shifted into the buffer, knocking the first one out.
 6. The next MAC is performed, and this process repeats every time the ADC produces a new sample.

## Implementations on the DFR Team

On the DFR team, the CMSIS library is used to compute the digital filters.
The filter kernel is hard coded, and a pointer to the kernel data is passed to a function in the CMSIS library that convolves the provided kernel with the input data.

# Analog to Digital Converters

Analog to Digital Converters (ADCs) have one job: measure an analog signal at regular intervals and record the data.
To understand this process better, imagine you are sitting on the side of the road, and you take a video of the cars going by.
You might be aware of the camera's *frame rate*, which refers to the number of "pictures" per second that the camera is capturing.
An ADC works much the same way in that is has a *sampling rate*.

This sampling rate is a very important design consideration due to the *nyquist theorem*, which is mentioned in the `analog_filtering.md` file.
It also affects the design of the digital filter and anti-aliasing filter.

## Challenge: Digitize a Signal

In tinkercad, write a program to sample a signal using the ADC on an arduino.
Here is some example code:
``` c++
#define DEL 100
#define NUM 1000

void setup()
{
  Serial.begin(115200);
  int aout = 0;
  
  for (int i=0; i<NUM; i++)
  {
    aout = analogRead(0);
    Serial.println(aout);
    delay(DEL);
  }
}

void loop()
{
  
}
```
Here is an example design in tinkercad:

![img](figures/tinker_cad_adc.JPG)

Play around with this design in tinkercad:
 - Add additional potentiometers
 - Change how the printing looks by using `Serial.print()` instead of `Serial.println()`
 - Print the actual voltage instead of the ADC conversion code

To find the voltage, assume the ADC code corresponds to a number between 0 and 5V.
Let 1023 be 5V, and 0 be 0V.
Use that information to correctly print the voltage.

Note that the loop() function is required, even though it is not populated.

# Mathematical Basis for Digital Filtering

Before diving into the specific applications on the DFR team, some time needs to be spent understanding what is happening mathematically.

## The Transfer Function

Filters can be described mathematically with their transfer function:

$$H(\omega) = \frac{V_{out}}{V_{in}}$$

Recall that this $(H(\omega))$ is the *frequency domain* representation of the filter's *impulse response* which is referred to as $h(t)$. 
For this document, capital letters define a function expressed in the frequency domain, and lower case letters define a function expressed in the time domain.

## Convolution

When using digital filtering to process an input signal, $V_{in}$ is known and $H(\omega)$ is known. More will be said about deriving $H(\omega)$ later.
That means we do not know $V_{out}$.
This means we must solve the equation for $V_{out}$:

$$V_{out} = V_{in}H$$

This process appears to be a simple multiplication, but we must be careful to note that these functions are all defined in the frequency domain.
It is possible to do the digital filtering in this manner, but it is more complicated because the user must take the fourier transform of the input data and multiply the result with the spectrum of the impulse response, also called the *filter kernel*.

To reduce computational intensity and development time, we need to rewrite the equation using the *Inverse Leplace Transform*:

$$\mathcal{L}^{-1}[V_{out} = V_{in}H] \to v_{out}(t) = v_{in}(t)*h(t)$$

The Leplace Transform and the Fourier Transform are mathematical means of converting a function from the time domain to the frequency domain.
The way to apply these transforms is outside the scope of this work.
Pay close attention to these mathematical processes in your differential equations class.

Now I direct your attention to the " $*$ " operator in the following equation:

$$v_{out}(t) = v_{in}(t)*h(t)$$

This is *not* a multiplication, but a *convolution* of the two functions.
You can think of convolution as a "fancy" multiplication, and it is defined as such:

$$v_{out}(t) = v_{in}(t)*h(t) = \int_{-\infty}^{\infty}v_{in}(\tau)h(t-\tau)d\tau$$

Since we are dealing with discrete functions, this integral becomes:

$$v_{out}(t) = \int_{-\infty}^{\infty}v_{in}(\tau)h(t-\tau)d\tau\to$$
$$v_{out}(n)=\sum_{i=0}^{\infty}v_{in}(i)h(n-i)$$

This summation is what must be evaluated to run a digital filter.
This can be thought of as an *inner product* or *dot product* of the discrete impulse response of the filter $h(n)$ and the input signal $v_{in}(i)$.
There is one subtle difference in that the impulse response is written as $h(n-i)$.
This simply denotes that we reverse the order of $h$.

### Example

Let $a$ be the total length of the filter kernel $h$ and the input signal $v_{in}$.
Then the convolution is written as:

$$v_{out}(n)=\sum_{i=0}^{a}v_{in}(i)h(n-i)$$

This translates to a *Multiply-Accumulate* (MAC) operation, or *weighted sum*:

$$v_{out}(n) = v_{in}(0)h(a) + v_{in}(1)h(a-1) + \cdots +v(a)h(0)$$

This weighted sum must be repeated to find every point in $v_{out}$.

# Challenge

Implement a digital filter in C.
Test it with the following:
 - Use an impulse
 - Use a sinusoid, and be sure the attenuation is as you expect
