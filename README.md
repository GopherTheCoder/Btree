**👴在干什么🍋❤里没点B🌲🐎？**
# 函数功能
+ **NewTree**：创建新树，需提供阶数m
+ **Search**：搜索，找到则返回true，否则false
+ **Insert**：添加结点，先查找，若已存在则返回false，否则插入并返回true
+ **Delete**：删除结点，先查找，若不存在则返回false，否则删除并返回true
+ **Destroy**：销毁
+ **Traverse**：升序遍历（递归）
***
+ **__Split**：仅处理非根分裂，输入为一个已经溢出的结点（关键字有序），分裂后需判断父结点是否需分裂，如需分裂则返回false，由调用者继续分裂父结点
+ **__Insert_Ordered**：顺序插入，仅在确保输入有序时使用（即尾插）
+ **__Insert_Simple**：简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
+ **__Split_Root**：根结点分裂，修改指针
+ **__Insert**：综合插入，指定需插入结点，提供阶数m，提供root
+ **__Search**：内部用搜索，找到返回所在结点，找不到则返回要插入的结点指针
+ **__Delete_Simple**：简单删除，提供目标节点及目标key，删后不做任何处理
+ **__Delete_NotTerminal**：非终端结点删除
+ **__Delete_Terminal**：终端结点删除
+ **__Unite**：结点合并
# TODO
+ [x] 插入问题，需判断插入进父结点的位置（可能不为尾部）
+ [x] 根结点分裂问题
+ [x] 分裂相关：传入子树结点进行插入，发生根分裂，无法修改树指针，需其他方案
+ [x] Insert怎么又有问题？！
+ [ ] Delete还没写完，更没测试
+ [ ] key[0]替代n
***
> ## 动态查找表基本操作
> + **InitDSTable(&DT);**  
>   *操作结果*：构造一个空的动态查找表DT。
> + **DestoryDSTable(&DT);**  
>   *初始条件*：动态查找表DT存在。  
>   *操作结果*：销毁动态查找表DT。
> + **SearchDSTable(DT,key);**  
>   *初始条件*：动态查找表DT存在，key为和关键字类型相同的给定值。  
>   *操作结果*：若DT中存在其关键字等于key的数据元素，则函数值为该元素的值或在表中的位置，否则为“空”。
> + **InsertDSTable(&DT,e);**  
>   *初始条件*：动态查找表DT存在，e为待插入的数据元素。  
>   *操作结果*：若DT中不存在其关键字等于e.key的数据元素，则插入e到DT。
> + **DeleteDSTable(&DT,key);**  
>   *初始条件*：动态查找表DT存在，key为和关键字类型相同的给定值。  
>   *操作结果*：若DT中存在其关键字等于key的数据元素，则删除之。
> + **TraverseDSTable(DT,Visit());**  
>   *初始条件*：动态查找表DT存在，Visit是对结点操作的应用函数。  
>   *操作结果*：按某种次序对DT的每个结点调用函数Visit()一次且至多一次。一旦Visit()失败，则操作失败。