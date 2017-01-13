## 代码编写调试笔记
##### 思磊 2017.1.2
--------------------------
1. wxAuiManager的Load/Save Perspective注意事项
* 需要使用LoadPerspective/LoadePerspective方法来载入/保存界面信息时：
	* 每个面板必须命名
	``` c++
	wxAuiPaneInfo().Name("pane_name")
	```
	**否则再次载入面板时，由于找不到对应信息归属导致整个界面空白**

* 注意LoadPerspective()方法第二个参数
	该参数默认值为`true`，会自动调用wxAuiManager::Update()方法

2. 关于wxConfig类，在析构函数（主Frame）中delete其对应的对象才能保存配置



