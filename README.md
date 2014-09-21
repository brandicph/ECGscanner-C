# ECG scanner
Electrocardiography (ECG or EKG) scanner to detect R peaks and heart failure based on the QRS algorithm written in C.
The main goal of this project is to learn the programming language C but also the benifits by using a low level language to optimize and make better performing software.

## Filters

#### Low-pass filter
Description of the low-pass filter
<!---
latex: y_n=2y_{n-1}-y_{n-2}+\frac{1}{32}\cdot(x_{n}-2x_{n-6}+x_{n-12})
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411309664/eqn.png)

#### High-pass filter
Description of the high-pass filter
<!---
latex: y_n=y_{n-1}-\frac{x_{n}}{32}+x_{n-16}-x_{n-17}+\frac{x_{n-32}}{32}
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411309614/eqn.png)


#### Derivative
Description of the derivative
<!---
latex: y_n=\frac{1}{8}(2x_{n}+x_{n-1}-x_{n-3}-2x_{n-4})
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411310592/eqn.png)


#### Squaring
Description of the Squaring
<!---
latex: y_n=x_{n}^{2}
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411310897/eqn.png)

#### Moving window integration
Description of the moving window integration
<!---
latex: y_n=\frac{1}{N}(x_{n-(N-1)}+x_{n-(N-2)}+\ldots+x_{n})
-->
![equation](http://www.sciweavers.org/upload/Tex2Img_1411310840/eqn.png)

#### QRS detection algorithm
Description of the QRS detection algorithm

### Flow diagram
The following flow diagram is showing the different stages and decision making in the QRS detection algorithm. Furtheremore the variables being set at initialization, peak detection and R peak detection.

![](Diagrams/QRS_algorithm_flow_chart.png?raw=true)
