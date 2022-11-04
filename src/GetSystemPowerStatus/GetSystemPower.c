#include <node_api.h>
#include <Windows.h>
#include "GetSystemPower.h"

napi_value GetSystemPower(napi_env env,napi_callback_info info){
    size_t s=0;
    napi_value obj;

    napi_value ACLineStatus_;
    napi_value BatteryFlag_;
    napi_value BatteryLifePercent_;
    napi_value SystemStatusFlag_;
    napi_value BatteryLifeTime_;
    napi_value BatteryFullLifeTime_;

    napi_value strACLineStatus_;
    napi_value strBatteryFlag_;
    napi_value strBatteryLifePercent_;
    napi_value strSystemStatusFlag_;
    napi_value strBatteryLifeTime_;
    napi_value strBatteryFullLifeTime_;

    SYSTEM_POWER_STATUS systemPowerStatus;
    GetSystemPowerStatus(&systemPowerStatus);

    napi_create_object(env,&obj);

    byte ACLineStatus=systemPowerStatus.ACLineStatus;
    byte BatteryFlag=systemPowerStatus.BatteryFlag;
    byte BatteryLifePercent=systemPowerStatus.BatteryLifePercent;
    byte SystemStatusFlag=systemPowerStatus.SystemStatusFlag;
    DWORD BatteryLifeTime=systemPowerStatus.BatteryLifeTime;
    DWORD BatteryFullLifeTime=systemPowerStatus.BatteryFullLifeTime;

    char* strACLineStatus="ACLineStatus";
    char* strBatteryFlag="BatteryFlag";
    char* strBatteryLifePercent="BatteryLifePercent";
    char* strSystemStatusFlag="SystemStatusFlag";
    char* strBatteryLifeTime="BatteryLifeTime";
    char* strBatteryFullLifeTime="BatteryFullLifeTime";

    napi_create_string_utf8(env,strACLineStatus, strlen(strACLineStatus),&strACLineStatus_);
    napi_create_string_utf8(env,strBatteryFlag, strlen(strBatteryFlag),&strBatteryFlag_);
    napi_create_string_utf8(env,strBatteryLifePercent, strlen(strBatteryLifePercent),&strBatteryLifePercent_);
    napi_create_string_utf8(env,strSystemStatusFlag, strlen(strSystemStatusFlag),&strSystemStatusFlag_);
    napi_create_string_utf8(env,strBatteryLifeTime, strlen(strBatteryLifeTime),&strBatteryLifeTime_);
    napi_create_string_utf8(env,strBatteryFullLifeTime, strlen(strBatteryFullLifeTime),&strBatteryFullLifeTime_);

    napi_create_int32(env,ACLineStatus,&ACLineStatus_);
    napi_create_int32(env,BatteryFlag,&BatteryFlag_);
    napi_create_int32(env,BatteryLifePercent,&BatteryLifePercent_);
    napi_create_int32(env,SystemStatusFlag,&SystemStatusFlag_);
    napi_create_int32(env,BatteryLifeTime,&BatteryLifeTime_);
    napi_create_int32(env,BatteryFullLifeTime,&BatteryFullLifeTime_);

    napi_set_property(env,obj,strACLineStatus_,ACLineStatus_);
    napi_set_property(env,obj,strBatteryFlag_,BatteryFlag_);
    napi_set_property(env,obj,strBatteryLifePercent_,BatteryLifePercent_);
    napi_set_property(env,obj,strSystemStatusFlag_,SystemStatusFlag_);
    napi_set_property(env,obj,strBatteryLifeTime_,BatteryLifeTime_);
    napi_set_property(env,obj,strBatteryFullLifeTime_,BatteryFullLifeTime_);

    return obj;
}

napi_value Init(napi_env env, napi_value exports){
    napi_property_descriptor _napi_props[]={
            {
                    .utf8name=METHODNAME,
                    .method=GetSystemPower,
                    .attributes=napi_default
            }
    };
    napi_define_properties(env,exports,1,&_napi_props);
    return exports;
}

NAPI_MODULE(GETSYSTEMPOWER,Init);