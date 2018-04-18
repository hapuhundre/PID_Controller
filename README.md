PID控制器

Self-Driving Car Engineer Nanodegree Program

---

代码的运行环境与运行方式与Term2的大同小异，不再赘述，可参考Project 3

使用PID控制器让小车安全的跑起来，越快越好。小车的速度在30迈到100迈之间。





行驶的视频参见video文件夹下mp4文件

PID results can be found in the mp4 file under the video folder



PID Tuning

使用“twiddle”方法+手工调参(Manual adjustment )对三个系数Kp、Ki以及Kd进行调参，twiddle实现过程参见PID.cpp文件中的Tunning函数，但在tuning过程中，twiddle方法车辆的形式过程并不稳定,因此手工调整参数是有必要的。

I use the "twiddle" method + manual adjustment to adjust the three coefficients Kp, Ki, and Kd. The twiddle implementation could be found  Tunning function in the PID.cpp file. In the tuning process, the twiddle method is not stable to control the vehicle. It is necessary to manually adjust the parameters.

对于手工调节参数的基本原则，可参考Tips内容和相关资料。



Tips

PID控制器的实现较为简单，课程的Python版本在cpp中实现也没什么难度。

- throttle的问题
  当将throttle value设为恒定值0.3~0.5时，小车运动的稳定性比用PID控制要强不少。当throttle value为pid控制时，小车两边摇晃，显然不够安全，也限制了小车的速度。
- steer初始参数的设置
  Init的三个系数Kp、Kd以及Ki在运动学上的含义。

 I should follow the following rules to use the manual adjustment.

K_p的大小代表了水龙头的粗细，即控制器对汽车调节的敏感程度，越大调的越快，即增大比例系数一般会加快系统响应,如下图所示：

The size of K_p represents the thickness of the "faucet", that is, the controller's sensitivity to the car. The larger K_p, the faster the adjustment of driving direction. That is, increasing the scale factor will generally speed up the system response, as shown in the following figure:





积分系数的定义为 K_{i}=\frac{K_p}{T_i} 其中T_i为积分时间常数，增大积分时间T_i，   即减小积分系数有利于减小超调，减小振荡，使系统的稳定性增加，但是系统静差消除时间变长，其过程如下：

The integral coefficient is defined as 



where T_i is the integral time constant. Bigger T_i, ie reducing the integral coefficient is beneficial to reducing overshoot, less oscillation, and making the system more stable , but the system static elimination time becomes longer. The process is as follows:



至于微分系数，主要用来来克服被控对象的滞后，尤其是对于汽车急转弯时，适当增大系数K_d可调整汽车响应速度。

As for the differential coefficient K_d, it is mainly used to overcome the lag of the controlled object, especially when the car is making a sharp turn. An appropriate adjustment of the coefficient K_d could ensure the stability of the car cornering.
