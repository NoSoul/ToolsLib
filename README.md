ToolsLib
========
ColorBashLog
    打印类,根据不同log等级,打印不同颜色
Complex
    复数类，使用avx并行优化
CPPMap
    Map模板类
FIFO:
    First In First Out类
    ReSize();   分配数据区域，以支持数组式定义,每个对象需要ReSize()
    operator=();    重写赋值函数
    Clear();    清除FIFO
    Push();     插入元素
    Pop();      取出元素
    Exist();    判断元素是否存在
    Empty();    判断当前FIFO是否为空
    GetLength();    获取当前FIFO有效值的大小
LogSet:
    Log类，维护各个模块的打印状态
    IsLogToScrn();  判断当前模块是否打印到屏幕
    IsLogTOFile();  判断当前模块是否打印到文件
    SetLogToScrn(); 设置当前模块打印到屏幕的状态
    SetLogToFile(); 设置当前模块打印到文件的状态
    SetBoth();      同时设置当前模块打印到屏幕和文件的状态
Matrix:
    二维矩阵类
    ReSize();   分配数据区域，以支持数组式定义,每个对象需要ReSize()
    Set();      设置当前对象某个元素的值
    Get();      获取当前对象某个元素的值
    operator=();    重写赋值函数
    operator+();    当前对象与另一对象相加，返回结果
    operator-();    当前对象与另一对象相减，返回结果
    operator*();    当前对象与另一对象相乘，返回结果
    operator*();    当前对象与某系数相乘，返回结果
    operator/();    当前对象与某系数相除，返回结果
    operator-();    当前对象取反，返回结果
    operator+=();    当前对象与另一对象相加，结果存储在当前对象
    operator-=();    当前对象与另一对象相减，结果存储在当前对象
    Inv2x2();   对2*2的矩阵求逆
    Inv3x3();   对3*3的矩阵求逆
    Atr();      将矩阵倒置，即M*N => N*M
PthreadEvent:
    pthread系列的事件类
    Set();      触发某个指定事件
    SetAll();   触发所有事件
    WaitOnce(); 某个事件只需阻塞等待一次，下一次不需要阻塞等待
    Wait();     阻塞等待某个指定事件
    WaitAll();  阻塞等待所有事件
    WaitAny();  阻塞等待任一事件
TCPScoket:
    TCP连接，支持一对一重连
    GetInstance();      获取唯一句柄
    InitialServer();    服务端初始化
    InitialClient();    客户端初始化
    ReconnTCPSocket();  服务端等待客户端重连（一对一连接）
    TCPSocketWrite();   发送一定长度的数据
    TCPSocketRead();    读取一定长度的数据
    TCPSocketReadLine();    给定最大接收数据长度，读取一行数据(\r \n结束)
