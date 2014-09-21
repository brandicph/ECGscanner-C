# ECG scanner
Electrocardiography (ECG or EKG) scanner to detect R peaks and heart failure based on the QRS algorithm written in C.
The main goal of this project is to learn the programming language C but also the benifits by using a low level language to optimize and make better performing software.

## Filters

#### Low-pass filter
Description of the lowpass filter

<!---
latex: y_n=2y_{n-1}-y_{n-2}+\frac{1}{32}\cdot(x_{n}-2x_{n-6}+x_{n-12})
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411309664/eqn.png)

#### High-pass filter
Description of the highpass filter
<!---
latex: y_n=y_{n-1}-\frac{x_{n}}{32}+x_{n-16}-x_{n-17}+\frac{x_{n-32}}{32}
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411309614/eqn.png)


#### Derivative
Description of the Derivative

#### Squaring
Description of the Squaring

#### Moving window integration
Description of the Moving window integration

#### QRS detection algorithm
Description of the QRS detection algorithm

### Flow diagram
The following flow diagram is showing the different stages and decision making in the QRS detection algorithm. Furtheremore the variables being set at initialization, peak detection and R peak detection.

![](Diagrams/QRS_algorithm_flow_chart.png?raw=true)
