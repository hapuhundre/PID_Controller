# PID控制器
Self-Driving Car Engineer Nanodegree Program

---

代码的运行环境与运行方式与Term2的大同小异，不再赘述，可参考[Project 3][https://github.com/hapuhundre/particle_filter]

使用PID控制器让小车安全的跑起来，越快越好。小车的速度在30迈到100迈之间。

![](pics/pic.png)



行驶的视频参见video文件夹下mp4文件

PID results can be found in the mp4 file under the `video` folder



## PID Tuning

使用“twiddle”方法+手工调参(Manual adjustment )对三个系数Kp、Ki以及Kd进行调参，twiddle实现过程参见`PID.cpp`文件中的`Tunning`函数，但在tuning过程中，twiddle方法车辆的形式过程并不稳定,因此手工调整参数是有必要的。

对于手工调节参数的基本原则，可参考**Tips**内容和相关资料，例如：









## Tips

PID控制器的实现较为简单，课程的Python版本在cpp中实现也没什么难度。

* throttle的问题

  当将throttle value设为恒定值0.3~0.5时，小车运动的稳定性比用PID控制要强不少。当throttle value为pid控制时，小车两边摇晃，显然不够安全，也限制了小车的速度。

* steer初始参数的设置

  Init的三个系数Kp、Kd以及Ki在运动学上的含义。


K_p的大小代表了水龙头的粗细，即控制器对汽车调节的敏感程度，越大调的越快，即**增大比例系数一般会加快系统响应**,如下图所示：

![](https://pic2.zhimg.com/80/1bf9717813a61536a354d075804f58c1_hd.jpg)

积分系数的定义为 $$K_{i}=\frac{K_p}{T_i}$$ 其中$T_i$为积分时间常数，增大积分时间$T_i$，   即减小积分系数有利于**减小超调，减小振荡，使系统的稳定性增加，但是系统静差消除时间变长**，其过程如下：

![](https://pic3.zhimg.com/7d20a7bb08b55a6e4003011ecde23623_r.jpg)

至于微分系数，主要用来来克服被控对象的滞后，尤其是对于汽车急转弯时，适当增大系数$K_d$可调整汽车响应速度。