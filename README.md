# flyingACE
-  这是一个使用Cocos2d3.0开发的飞机大战游戏，实际版本为Cocos2d-x3.3
---
## 开发环境
- Linux OS (Ubuntu 14.04 LTS)
- Eclipse 4.4.1
- Cocos2d-x-3.3
- Android SDK 4.4.2 (API 19)
- Android NDK r10d
- gcc 4.8
-  在linux平台、android平台、android虚拟机上测试通过
---
## 主要类功能分布
- AppDelegate: 程序入口，初始化Director类的参数，场景构建，布景层挂载，精灵挂载
- BulletLayer: 子弹层，用批量渲染技术加载子弹并维护子弹数据
- BulletUserData: 子弹数据
- EnemyLayer: 敌机层，加载敌机并维护敌机数据，检测敌机与子弹、敌机与我机及碰撞，并且调用对应接口
- EnemyUserData: 敌机数据
- GameBackgroundLayer: 布景层，实现地图加载，循环滚动
- PlaneLayer: 飞机层，渲染飞机动画，响应用户滑屏操作
- PlaneUserData: 飞机数据
---
# 联系方式
- Email: netbeen.cn@gmail.com
- QQ: 394062113
---
