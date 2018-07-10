# 计算图说明文档

（注：第一阶段已有内容不再重复，详见第一阶段小组的文档）

## 项目结构

Node类为所有节点的抽象基类，派生出Constant、Placeholder、Variable、SingleOperator、DoubleOperator类。SingleOperator和DoubleOperator为一个操作数的节点（如sin、cos）和两个操作数的节点（如+、*）的抽象基类。

Tensor类为数据类，所有的数据均为Tensor，包括数值、向量、矩阵。

## 运行环境

经过测试的环境：Ubuntu、CentOS 7、Windows 10

请使用c++11及以上版本，直接运行make即可编译，生成的测试程序名为test

## 新增接口介绍

### Node类

|代码|解释|
|---|---|
|`int depend() const`|返回输入节点个数|
|`bool Prop() const`|是否接受别人对他求导（例如比较节点这一项就为false）|
|`virtual Node& derive(int index)`|求导，index为1或2表示对第1个或第2个参数求导，返回的是节点|
|`std::map<Node*, Node*>& grad()`|求梯度，返回一个map，map中key为节点地址，value为对该节点的偏导数|

### SingleOperator

|新增节点|解释|
|---|---|
|Assert|输入1个节点，输出始终为0，但是却能够在节点小于等于0时报`invalid_argument("Error : Assert <= 0")`。|

### DoubleOperator

|新增节点|解释|
|---|---|
|Bigger|a大于b，值为1，否则为0|
|Smallerer|a小于b，值为1，否则为0|
|BiggerEqual|a大于等于b，值为1，否则为0|
|SmallerEqual|a小于等于b，值为1，否则为0|
|Equal|a等于b，值为1，否则为0|
|Bind|调用`Bind.Eval()`输出节点2，调用`Bind.eval()`（也就是在求其他节点时路过它时）输出节点1|
