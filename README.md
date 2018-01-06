README
===========================
该文件用来给课设组员提供编程时的参考与向导

****

|Author|赵xx|朱xx|陈xx
|---|---|---|---
|E-mail|1224306181@qq.com|810485796@qq.com|1595881193@qq.com

****

## 目录
* [设计](#设计)
    * 主要数据结构
        *   类依赖
        *   类API
    * GUI
        *   外观设计
        *   GUI类
        *   GUI类API
* [分工](#分工)
* [风格约定](#风格约定)

****

## 设计
主要数据结构(非GUI)， GUI外观设计， GUI类
### 主要数据结构
包括核心 邻接表&&tarjan 辅助 hash_map 线性表
#### 类依赖
#### 类API
### GUI
#### 外观设计
外观设计主要使用demo设计软件Axure rp
#### GUI类
#### GUI类API
## 分工

## 风格约定
代码的风格主要参考于 [Google 开源项目风格指南](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/)
#### 普通变量命名
小写，下划线相连
```c++
int table_name;
```
#### 类内变量命名
结尾接下划线, 其他与普通变量一样
```c++
class ClassName{
private:
 int table_name_;
};
```
#### 结构体变量命名
与普通变量一样，结尾不接下划线
```c++
struct StructName{
 int table_name;
};
```
