# flyingACE (王牌飞行员)
- 这是一个使用Cocos2d-x-3.X 开发的飞机大战游戏，实际版本为Cocos2d-x3.3
- This is a Cocos2dx game about aircraft fighting (using Cocos2dx binding C++). During this commit, the version of my Cocos2d is Cocos2d-x3.3.

---

## 开发环境 Dev Environment
- Linux OS (Ubuntu 14.04 LTS)
- Eclipse 4.4.1
- Cocos2d-x-3.3
- Android SDK 4.4.2 (API 19)
- Android NDK r10d
- gcc 4.8
- 在win32平台、linux平台、android平台、android虚拟机上测试通过
- Tested under the win32, linux, android(both mobile and SDK).

---

## 类功能分布 Files
- AppDelegate: 程序入口，初始化Director类的参数，场景构建，布景层挂载
- AppDelegate: The init access of the program. Init the Direct class and construct the Scenes and Layers.
- BulletLayer: 子弹层，用批量渲染技术加载子弹并维护子弹数据
- BulletLayer: Bullet Layer, using SpriteBatchNode to load bullets.
- BulletUserData: 子弹数据
- BulletUserData: The data struct defined by myself. Recording the damage of each bullet.
- EnemyLayer: 敌机层，加载敌机并维护敌机数据，检测敌机与子弹、敌机与我机及碰撞，并且调用对应接口
- EnemyLayer: Enemy Layer, load the enemy from a plist, and placed them onto a random position. Also, prividing the interface of the crash detecting.
- EnemyUserData: 敌机数据
- EnemyUserData: The datastruct defined by myself. Recording the some paramater of enemy plane, like HP and others. 
- GameBackgroundLayer: 布景层，实现地图加载，循环滚动
- GameBackgroundLayer: Background Layer, auto loading the background image and rolling.
- PlaneLayer: 飞机层，渲染飞机动画，响应用户滑屏操作
- PlaneLayer: Plane Layer, Interactive layer of the game.
- PlaneUserData: 飞机数据
- PlaneUserData: The datastruct defined by myself. Recording the some paramater of enemy plane, like HP and others. 

---

# 鸣谢 Thanks
- 特别感谢TexturePacker的作者Andreas Löw为本次开发提供Pro版的序列号
- Thanks to Mr. Andreas Löw (the author of TexturePacker), for prividing the free key of TexturePacker pro.

---

# 联系方式 Contact Me
- Email: netbeen.cn@gmail.com
- QQ: 394062113

---

# 关键字 Keywords
- cocos cocos2d cocos2dx cocos2dx3.0
