//
//  QDAccessManagerDefine.h
//  QDingSmartControl
//
//  Created by 高应超 on 16/6/12.
//  Copyright © 2016年 qdhl. All rights reserved.
//

#ifndef QDAccessManagerDefine_h
#define QDAccessManagerDefine_h


typedef enum RESUALT_CODE
{
    RESUALT_SUCCESS = 0,
    //common error
    ERROR_OPEN_DOOR_FAILURE = 1000,//开门失败,请重试
    ERROR_GET_DOOR_FAILURE = 1001,//"房屋未授权, 请联络物业中心"
    ERROR_BUILD_PACKET = 1002,//"生成开门数据失败"
    ERROR_OPEN_DOOR_BUSY = 1003,//"其他用户开门中，请稍后再试"
    ERROR_DISCONNECT_DEVICE_FAILURE = 1004,//"设备异常断开连接"
    ERROR_NO_AUTHORIZED_DEVICE_FIND = 1005,//"当前未发现您可通行的门禁设备"
    ERROR_TOO_FAR_DEVICE = 1006,//"请靠近门重试，有效开门距离为1~2米"
    ERROR_SEND_DATA_TIMEOUT = 1007,//"发送开门数据超时"
    ERROR_RECEIVE_DATA_TIMEOUT = 1008,//"接收开门数据超时"
    ERROR_CLOSE_DEVICE_TIMEOUT = 1009,//"等待设备关闭连接超时"
    ERROR_NOT_COMPITABLE_DEVICE = 1010,//"发现您的app版本与门禁设备不兼容,请更新下载最新版app,安装后重试"
    ERROR_NOT_SUPPORT = 1011,  //不支持当前手机型号
    ERROR_BLEDEVICE_NULL_WITHOUT_ROOMS = 1012, //未绑定房屋，且设备列表为空
    ERROR_NO_DEVICE_FIND = 1013,  //当前位置未扫描到门禁设备
    ERROR_BLEDEVICE_NULL_WITH_ROOMS = 1014, //绑定房屋，但设备列表为空
    ERROR_GET_HASHEDAPP_UID_FAILED = 1015, //获取精简版App_User_UID失败
    
    //BLE error
    ERROR_NO_BLUETOOTH_PREMISSION = 1100,//"请打开蓝牙后再试"
    ERROR_INIT_BLE_FAILUER = 1101,//"初始化蓝牙失败,关闭蓝牙后重试"
    ERROR_CONNECT_BLE_FAILURE = 1102,//"连接设备蓝牙失败,请重试"
    ERROR_CONNECT_BLE_TIMEOUT = 1103,//"连接设备蓝牙超时,请重试"
    ERROR_FIND_BLE_SERVICE_TIMEOUT = 1104,//"发现蓝牙设备服务超时"
    ERROR_WRITE_BLE_DATA_EXCEPTION = 1105,//"写入蓝牙设备数据异常"
    ERROR_WRITE_BLE_CHANNEL_CLOSED = 1106,//"写入蓝牙设备数据的特征管道关闭"
    ERROR_READ_BLE_DATA_EXCEPTION = 1107,//"读取蓝牙设备数据异常"
    
    //写卡
    ERROR_WRITE_CARD_UNSUPPORT = 1301, //"门禁设备版本过低,不支持写卡", "请升级门禁设备后重试"
    ERROR_WRITE_CARD_BUILD_DATA_FIAL = 1302, //"构建写卡数据失败", "请重试"
    ERROR_WRITE_CARD_TIMEOUT = 1303, //"写卡超时", "请靠近门禁设备重试"),
    ERROR_WRITE_CARD_CONNECT_TIMEOUT = 1304, //"设备连接超时", "请靠近门禁设备重试"
    ERROR_WRITE_CARD_FAIL = 1305, //"刷卡太快，请保持刷卡时间3秒以上", "请保持刷卡时间3秒以上"
    //读卡
    ERROR_READ_CARD_UNSUPPORT = 1401,// "门禁设备版本过低,不支持读卡", "请升级门禁设备后重试"),
    ERROR_READ_CARD_RESULT_TIMEOUT = 1402,// "读卡超时", "请靠近门禁设备重试"),
    ERROR_READ_CARD_CONNECT_TIMEOUT = 1403, //"设备连接超时", "请靠近门禁设备重试"),
    ERROR_READ_CARD_FAIL = 1404, //"刷卡太快，请保持刷卡停留时间3秒以上", "请保持刷卡停留时间3秒以上"),
    ERROR_READ_CARD_BUILD_DATA_FIAL = 1405,// "构建读卡数据失败", "请重试"),;
    
    
}RESUALT_CODE;



typedef enum OPEN_RESULT_WAY
{
    OPEN_RESULT_BY_AV = 11101,
    OPEN_RESULT_BY_DATA = 11102
} OPEN_RESULT_WAY;

typedef enum CMD_ACTION_STATUS
{
    CMD_ACTION_REACTED,/** 操作的响应之后 处理时间*/
    CMD_ACTION_SENDING,/** 发送之后等待 QD_WRITECARD_SENDED_TIMEOUT , QD_READCARD_SENDED_TIMEOUT */
    CMD_ACTION_RECIEVED,/** 收到了第一次响应 等待操作 持续时间为外部提供*/
    CMD_ACTION_CONNECTING,/** 正在建立蓝牙连接*/
    CMD_ACTION_CONNECTED,/** 蓝牙连接成功*/
    
} CMD_ACTION_STATUS;


typedef enum OPEN_WAY
{
    OPEN_BY_USER     = 100,  //用户手动点击开门(已废弃)
    OPEN_BY_IBEACON  = 101,  //ibeacon无障碍通行
    OPEN_BY_SHAKE    = 102,  //摇一摇
    OPEN_BY_Button   = 103,  //按钮
    OPEN_BY_SPLASH   = 104,  //启动页
    OPEN_BY_SHORTCUT = 105,  //桌面快捷方式
    OPEN_BY_3DTOUCH  = 106,  //3DTouch
}OPEN_WAY;


typedef enum OPEN_TYPE_DATA
{
    OPEN_TYPE_CARD_DATA,   //携带开卡信息
    OPEN_TYPE_BLACKANDWHITE_DATA,   //黑白名单
    OPEN_TYPE_NORMAL_DATA   //默认开门信息
}OPEN_TYPE_DATA;





///**
// *  开门成功后的回调
// *
// *  @param errorCode         开门结果标示码
// *  @param message           开门结果信息描述
// *  @param animationKeepTime 开门成功后动画效果保持时长
// */

//typedef void (^OpenDoorResult)(OPEN_ERROR_CODE errorCode,NSString *message,int animationKeepTime);
/**
 *  开门成功后的回调
 *
 *  @param errorCode         开门结果标示码
 *  @param message           开门结果信息描述
 */
typedef void (^OpenDoorResult)(RESUALT_CODE errorCode,NSString *message);
typedef void (^NearDeviceRSSI)(NSNumber *RSSI);

/**
 写卡Block
 
 @param isSuccess 是否写入成功
 @param message  写卡回调信息
 */
typedef void (^OnDistributeCardAck)(RESUALT_CODE errorCode,NSString *message);

/**
 读卡回调
 
 @param dataDic 返回的卡信息
 */
typedef void (^OnReadedCardAck)(RESUALT_CODE errorCode, NSString *message);

typedef void (^WaitingForAction)(RESUALT_CODE errorCode, NSString *message);


#endif /* QDAccessManagerDefine_h */
