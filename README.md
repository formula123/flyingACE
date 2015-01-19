# flyingACE (王牌飞行员)
- 这是一个使用Cocos2d-x-3.X 开发的飞机大战游戏，实际版本为Cocos2d-x3.3

---

## 开发环境
- Linux OS (Ubuntu 14.04 LTS)
- Eclipse 4.4.1
- Cocos2d-x-3.3
- Android SDK 4.4.2 (API 19)
- Android NDK r10d
- gcc 4.8
- 在win32平台、linux平台、android平台、android虚拟机上测试通过

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

#鸣谢
- 特别感谢TexturePacker的作者Andreas Löw为本次开发提供Pro版的序列号
- Thanks to the author of TexturePacker Mr. Andreas Löw, for prividing the free key for TexturePacker pro.

---

# 联系方式
- Email: netbeen.cn@gmail.com
- QQ: 394062113

---
