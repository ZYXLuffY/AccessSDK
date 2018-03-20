#iOS蓝牙门禁SDK说明
[TOC]
##简介
门禁SDK提供蓝牙开门、iBeacon开门、获取门禁设备蓝牙信号强度、开卡功能、读卡功能、众筹升级功能。 
调用BYAccessManager类的接口完成对应业务功能，成功失败均有对应RESUALT_CODE及Message返回
###业务说明

#### 蓝牙开门
* 广播开门：构建广播开门数据，发送广播请求 参考 [BLE广播通信相关的技术分析](http://www.cnblogs.com/heiyue/p/6109283.html) 

* 蓝牙数据响应开门：接收开门广播，判断广播开门是否成功，再继续构建蓝牙开门数据的请求，解析开门回调，成功即上报开门记录

#### iBeacon开门
基于iOS的CoreLocation API 提供的判断附近设备的位置以判断附近QD的门禁设备，触发程序中的开门接口。
#### 获取门禁设备蓝牙信号强度
提供门禁设备的蓝牙信号，便于上层调用。
#### 开卡
由外部提供卡的卡号及卡信息，发送构建好的蓝牙数据，等待门禁蓝牙回调，写卡过程不可操作过快。
#### 读卡
流程同写卡，等待读卡操作后的蓝牙回调，读卡过程不可操作过快。
#### 众筹升级
初始化SDK，获取当前门禁版本信息，当前版本开门数据发送同时，门禁设备升级回调被调用，判断当前设备版本是否需要升级（发送截取的升级片段）

###数据构造
调用蓝牙开门、读卡、写卡业务时返回对应的RESUALT_CODE及描素

![](http://os5gpc0lx.bkt.clouddn.com/14982071784886.jpg)

##SDK集成
首先设置网络环境获取同行设备列表为了判断通行权限

* 设置网络环境

````
/**
 设置网络环境

 @param environment	  	NET_DEV = 1,   //开发环境
                     	NET_QA = 2,    //测试环境
                     	NET_BOSS = 3   //生成环境
*/
+ (void) setAccessNetworkEnvironment (ACCESS_NETWORK_ENVIRONMENT)environment;

````


* 同步数据

````
/**
 同步当前App用户用于通行的数据（所绑定房间的可通行设备列表，同时会对用户ID做精简操作）

 @param userID App用户ID
 @param roomIDs 用户所绑定的所有房间数组
 */
+ (void)syncAccessDataForUser:(NSString *)userID withRooms:(NSArray *)roomIDs;
````


##接口调用

<!--### 更新记录
* 版本：V2.1.0 
* 1.新增写卡业务接口
* 2.新增读卡业务接口
* 3.新增众筹升级业务
* 4.新增断开蓝牙连接接口-->

BYAccessManager  的开卡接口定义如下：
###开门接口
````
/**
 用户开本操作

 @param appUserID 用户appUserID
 @param openWay 用户的开门方式OPEN_BY_USER：用户手动开门。OPEN_BY_IBEACON：无障碍通行
 @param result 开门操作完成后的回调
 */
- (void)openDoorByUserID:(NSString *)appUserID andWay:(OPEN_WAY)openWay result:(OpenDoorResult)result;
````

**使用方法**


```Objective-C
[[BYAccessManager sharedInstance] openDoorByUserID:@"" andWay:OPEN_BY_USER result:^(RESUALT_CODE errorCode, NSString *message) {
        if (errorCode == RESUALT_SUCCESS) {
            NSLog(@"开门成功");
        }else{
            NSLog(@"开门失败 %@",message);
        }
}];
```

###获取蓝牙信号强度

```
/**
 开始检测附近是否有门禁设备并返回RSSI
 
 @param rssi 返回信号强度的block 
 typedef void (^NearDeviceRSSI)(NSNumber *RSSI);
 */
- (void)startCheckQDDeviceNear:(NearDeviceRSSI)rssi;

```
**使用方法**
RSSI值小于65才符合开门要求


````
[[BYAccessManager sharedInstance] startCheckQDDeviceNear:^(NSNumber *RSSI) {
    NSInteger rssi = [RSSI integerValue];
}];
````

###写卡接口

```jsdddsd
/**
写卡操作
 @param userID 用户ID 
 @param cardDic 传入的卡信息
 @param duirationTime 超时时间（总时间）
 @param actionBlock 等待操作的回调
 @param resultBlock 操作结果的回调
*/

+ (void)writeCardWithUserID:(NSString *)userID withCardDic:(NSDictionary *)cardDic duirationTime:(NSInteger)duirationTime waitingForAction:(WaitingForAction)actionBlock resultBlock:(OnDistributeCardAck)resultBlock;

```

<font color=#0099ff size=  face="黑体">cardDic = 
@{@"cardNo" : @"cardInfo"}

构建相应的NSDictionary 卡号为key，卡序列码为value

actionBlock 和 resultBlock 均会返回对应的RESUALT_CODE 

resultBlock 成功会返回相应的 RESUALT_CODE 而 message 则当前卡号，RESUALT_CODE != RESUALT_SUCCESS 则message为错误描述

</font>


**使用方法**

````
[BYAccessManager writeCardWithUserID:app_user_ID withCardDic:@{@"123":@"456",@"789":@"168"} duirationTime:20 waitingForAction:^(RESUALT_CODE errorCode, NSString *message) {
	NSLog(@"message %@",message);
} resultBlock:^(RESUALT_CODE errorCode, NSString *message) {
       if (errorCode == RESUALT_SUCCESS) {
           NSLog(@"写卡成功");
       }
}];
````

###读卡接口


```js
/**
读卡操作

@param userID 用户ID
@param duirationTime 超时时间
@param actionBlock 等待操作的回调
@param resultBlock 操作结果的回调
*/
+ (void)readCardWithUserID:(NSString *)userID  duirationTime:(NSInteger)duirationTime waitingForAction:(WaitingForAction)actionBlock resultBlock:(OnReadedCardAck)resultBlock;
```

<font color=#0099ff size=  face="黑体">


actionBlock 和 resultBlock 均会返回对应的RESUALT_CODE actionBlock会先于resultBlock调用

actionBlock 和 resultBlock 成功会返回相应的 RESUALT_CODE 而 message（resultBlock） 则当前卡号，RESUALT_CODE != RESUALT_SUCCESS 则message为错误描述

</font>

```
[BYAccessManager readCardWithUserID:app_user_ID duirationTime:15 waitingForAction:^(RESUALT_CODE errorCode, NSString *message) {
BYLog(@"等待读卡操作");
} resultBlock:^(RESUALT_CODE errorCode, NSString *message) {
BYLog(@"readCardResult == %@",message);
}];
```
###iBeacon
1.APP的定位权限必须是 始终允许
2.蓝牙开启
3.能够完成手动点击亮屏后触发iBeacon开门
####超能门禁触发方式
1.离开设备较远范围外（二三十米范围，范围未确定），再向门禁设备靠近则可开门，需要离开设备远范围外，再重新靠近 ，才可以触发无感开门
2.在设备附近（可以正常开门的距离），由暗屏点亮手机屏幕可触发开门
下图作出解释：
![](http://os5gpc0lx.bkt.clouddn.com/15084923910021.jpg)

