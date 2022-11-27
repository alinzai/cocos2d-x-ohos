# XComponent

### 简介

本示例通过XComponent组件使用C++ OpenGL渲染三角形，可通过按键改变三角形的颜色和形状。

同时，该实例展示了如何将应用生命周期，页面生命周期桥接到C++层，结合XComponent组件提供的surface生命周期，可实现C++层渲染的完整开发过程。实现效果如下：

![](./screenhots/devices/main.png)

### 相关概念

XComponent：可用于EGL/OpenGLES和媒体数据写入，并显示在XComponent组件。

### 相关权限

不涉及。

### 使用说明

1.打开应用，首页面显示两个button和黑色背景的绿色三角形。

2.点击屏幕中的ChangeColor按键，画面中三角形变为粉色。

3.点击屏幕中的ChangeShape按键，画面中三角形变换形状且颜色变为红色。

### 约束与限制

1.本示例仅支持在标准系统上运行。

2.本示例需要使用DevEco Studio 3.0 Beta3 (Build Version: 3.0.0.901, built on May 30, 2022)才可编译运行。

3.API8只支持32位，API9支持32位和64位；当前Demo应用使用API9，支持32位和64位版本。

4.本示例需要使用特定版本的NDK编译才能正常显示。