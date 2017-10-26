//
//  BYBLEUrlDefine.h
//  qding
//
//  Created by 胡涛 on 3/30/16.
//  Copyright © 2016 www.qdingnet.com. All rights reserved.
//

#ifndef QDBLEUrlDefine_h
#define QDBLEUrlDefine_h


// ===== 服务器地址定义 =====
//开发环境
#define SERVER_ADDR_DEV   @"http://tx.lixiaodeng.com"
//QA环境
#define SERVER_ADDR_QA    @"https://qatx.qdingnet.com"
//正式环境
#define SERVER_ADDR_BOSS  @"https://tx.qdingnet.com"

// ===== API定义 =====
#define GET_MAC_LIST_API         @"/brake_api/Brake_Machine_Api/get_can_pass_brake_list/"
#define REPORT_PASSBY_RECORD_API @"/brake_api/Brake_Pass_Api/set_user_pass_list/"
//add by 高应超 2016.6.12  新的接口做了数据精简
#define GET_BRAKE_DEVICE_API @"/basedata_api/Basedata_Bj_App_User_Api/get_app_user_can_open_door_list/"
#define REPORT_SIMPLIFY_PASSBY_RECORD_API @"/brake_api/Brake_Pass_Api/set_number_user_pass_list/"
#define SIMPLIFY_ORIGINAL_USERID_API @"/basedata_api/Basedata_Bj_App_User_Api/get_app_user_id/"
#define CHECK_BRAKE_FIRMWARE_VERSION_API @"/basedata_api/Basedata_Bj_App_User_Api/check_brake_firmware_version/"
#define SET_BRAKE_FIRMWARE_VERSION_API @"/basedata_api/Basedata_Bj_App_User_Api/check_brake_firmware_version/"
#define OPENDOOR_RECORD_LIST_API  @"/brake_api/Brake_Open_Time_Api/uploads/"

typedef enum ACCESS_NETWORK_ENVIRONMENT
{
    NET_DEV = 1,   //开发环境
    NET_QA = 2,    //测试环境
    NET_BOSS = 3   //生成环境
}ACCESS_NETWORK_ENVIRONMENT;



#endif /* QDBLEUrlDefine_h */
