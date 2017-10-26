//
//  BYAccessManager.h
//  qding
//
//  Created by 高应超 on 16/4/22.
//  Copyright © 2016年 www.qdingnet.com. All rights reserved.
//

/**
 * 更新记录
 * 版本：V2.1.0 发布时间：2017-05-24
 * 1.新增写卡业务接口
 * 2.新增读卡业务接口
 * 3.新增众筹升级业务
 * 4.新增断开蓝牙连接接口
 *
 *
 * 版本：V2.0.0  发布时间：2016-06-25
 * 1.新增广播开门，提高开门效率到0.5s左右。
 * 2.精简与门禁设备传输数据（userID精简，取消无用的参数），提高传输效率。
 * 3.修改了同步门禁列表的接口，一次性请求所有数据（门禁设备列表，用户的房屋信息）。
 * 4.完善了设备信号强度判断，防止用户远距离开门。
 * 5.调整错误信息提示，更贴近用户。
 * 6.调整通行记录上传方式，取消30s轮询。当用户有开门操作后才进行通行记录的上传。
 * 7.完成代码结构的总体调整。
 *
 *
 * 版本：V1.0.4  发布时间：2016-05-27 19：06
 * 1. 取消了对设备端RSSI的监听和判断，提升开门速度约300ms.取消开门请求数据传输间隔时间。提升200ms开门速度
 * 2. 对代码结构进行调整，优化性能。
 *
 *
 * 版本：V1.0.3  发布时间：2016-04-18 19：06
 * 1. 添加终端设备位置学习代码
 * 2. 添beacon代码
 * 3. 将代码转移到BYSDK，修改类以BY开头，并去掉QDData依赖
 *
 * 版本：V1.0.2  发布时间：2016-04-07 17：06
 * 1. 添加终端设备位置学习代码
 *
 * 版本：V1.0.1  发布时间：2016-02-26 11：33
 * 1. 修改通行记录及设备授权列表文件到 ~/Document/qduser/accesscontrol/目录下。
 * 2. 程序会删除以前版本建立的文件。
 *
 * 版本：V1.0.0  发布时间：2016-02-25 20：01
 * 1. 修复通行记录数据库try catch，内存释放bug。
 *
 * 版本：V0.0.9  发布时间：2016-01-19 14：21
 * 1. 修改提示文案，开门失败原因更具体，并附加简单说明。
 * 当前提示文案：
 * 1. 请通行
 * 2. 房屋未授权，请联络物业中心
 * 3. 请靠近门重试，有效开门距离为1~2米
 * 4. 当前未发现您可通行的门禁设备
 * 5. 房屋数据处理异常，请下拉刷新后重试
 * 6. 验证过程异常中断，请重试
 * 7. 其他用户通行中，请稍后再试
 * 8. 不支持当前手机型号，请使用iPhone4S及以后机型
 *
 * 版本：V0.0.8  发布时间：2015-11-17 23：35
 * 1. 移除Pod，直接集成MJExtion源码。
 * 2. 同步最新MJExtion源码，解决未知的异常
 *
 * 版本：V0.0.7  发布时间：2015-11-16 16:51
 * 1. 移除AppUserID必须为32byte字符串的强验证
 *
 * 版本：V0.0.6  发布时间：2015-11-16 10:20
 * 1. 修正服务器返回错误为0，但并无数据的逻辑处理bug
 *
 * 版本：V0.0.5  发布时间：2015-11-15 17:40
 * 1. 调整开门超时时间为5秒，增加通信时间，避免出现实际开门已经成功，但收到请重试的错误提示
 *
 * 版本：V0.0.4  发布时间：2015-11-13 18:54
 * 1. 提高iBeacon模式下的识别成功率
 * 2. 调整最长时间为3秒钟
 *
 * 版本：V0.0.3  发布时间：2015-11-13 15:34
 * 1. 增加版本获取接口
 * 2. 修复通信数据过短，处理逻辑错误bug
 */

#import <Foundation/Foundation.h>
#import "QDAccessManagerDefine.h"
#import "QDBLEUrlDefine.h"


@import CoreLocation;


@protocol BYiBeaconDelegate <NSObject>

-(void)ibeaconDeviceEnter;

-(void)ibeaconDeviceProximity:(CLProximity)proximity rssi:(NSInteger)rssi;

@end

@interface BYAccessManager : NSObject

//当启用无障碍通行时，必须设置次委托，拿到设备进入的回调时间
@property (nonatomic, weak)  id<BYiBeaconDelegate> ibeaconDelegate;
//在QDAppDelegate类中的进入前台、退入后台的方法中调用，以确保ibeacon在后台触发。
@property BOOL appEnterBackground;


+ (const NSString *) getFrameworkVersion;

/**
 *  获取通行管理对象（单例）
 *
 *  @return 对象
 */
+ (BYAccessManager *)sharedInstance;

/**
 开始检测附近是否有门禁设备并返回RSSI
 
 @param rssi 返回信号强度的block
 */
- (void)startCheckQDDeviceNear:(NearDeviceRSSI)rssi;

/**
 停止检测附近设备
 */
- (void)stopCheckQDDeviceNear;


/**
 *  用户开本操作
 *
 *  @param appUserID 用户appUserID
 *  @param openWay   用户的开门方式
 *  @param result    开门操作完成后的回调
 */
- (void)openDoorByUserID:(NSString *)appUserID andWay:(OPEN_WAY)openWay result:(OpenDoorResult)result;


/**
 写卡数据
 @param userID 用户ID
 @param cardDic 传入的卡号
 @param duirationTime 超时时间（总时间）
 @param resultBlock 回调
 
 */

+ (void)writeCardWithUserID:(NSString *)userID withCardDic:(NSDictionary *)cardDic duirationTime:(NSInteger)duirationTime waitingForAction:(WaitingForAction)actionBlock resultBlock:(OnDistributeCardAck)resultBlock;

/**
 读卡操作
 
 @param userAppID 用户ID
 @param duirationTime 超时时间
 @param resultBlock 回调NSDictionary *
 */
+ (void)readCardWithUserID:(NSString *)userID  duirationTime:(NSInteger)duirationTime waitingForAction:(WaitingForAction)actionBlock resultBlock:(OnReadedCardAck)resultBlock;
/**
 断开蓝牙
 */
+ (void)cancelBLEConnection;


@end



@interface BYAccessManager (IBeacon)

/**
 *  在AppDelegate里注册ibeacon，用来后台幻想APP做开门操作
 *
 *  @param delegate  实现CLLocationManagerDelegate委托的类
 */
-(void)registerIBeacon:(id<CLLocationManagerDelegate>)delegate;


/**
 *  开启无障碍通行
 * 1.	设备要求：iPhone4s+，系统要求iOS7.1+。
 * 2.要进行后台及kill掉仍然可以监控，需要用户把蓝牙打开，后台应用应用程序刷新功能打开，以及定位服务中该应用的定位功能打开。
 */
- (void)openIBeacon;

/**
 *  关闭无障碍通行
 */
- (void)closeIBeacon;

@end


@interface BYAccessManager (network)

/**
 *  设置网络环境
 *
 *  @param environment     NET_DEV = 1,   //开发环境
 NET_QA = 2,    //测试环境
 NET_BOSS = 3   //生成环境
 */
+ (void) setAccessNetworkEnvironment:(ACCESS_NETWORK_ENVIRONMENT)environment;

/**
 *  同步当前App用户用于通行的数据（所绑定房间的可通行设备列表，同时会对用户ID做精简操作）
 *
 *  @param appUserID App用户ID
 *  @param roomIDs   用户所绑定的所有房间数组
 */
+ (void)syncAccessDataForUser:(NSString *)userID withRooms:(NSArray *)roomIDs;






@end
