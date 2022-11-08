#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wlanapi.h>
#include "GetNetworkList.h"

napi_value GetNetworkList(napi_env env, napi_callback_info info) {
    size_t argc = 0;
    size_t convertedChars;
    napi_value arr;
    napi_value result;
    char str[0x100];

    DWORD ClientVersion = 1;
    DWORD NegotiatedVersion = 0;
    HANDLE hClientHandle;
    PWLAN_INTERFACE_INFO_LIST pwlanInterfaceInfoList;
    PWLAN_AVAILABLE_NETWORK_LIST pwlanAvailableNetworkList;

    napi_create_array(env, &arr);

    WlanOpenHandle(ClientVersion, NULL, &NegotiatedVersion, &hClientHandle);
    WlanEnumInterfaces(hClientHandle, NULL, &pwlanInterfaceInfoList);

    for (int i = 0; i < (int)pwlanInterfaceInfoList->dwNumberOfItems; i++) {
        WlanGetAvailableNetworkList(
                hClientHandle,
                &pwlanInterfaceInfoList->InterfaceInfo[i].InterfaceGuid,
                0,
                NULL,
                &pwlanAvailableNetworkList);

        for (int j = 0; j < (int)pwlanAvailableNetworkList->dwNumberOfItems; ++j) {
            WCHAR* strProfileName = pwlanAvailableNetworkList->Network[j].strProfileName;
            wcstombs_s(&convertedChars,str, sizeof(str), strProfileName, sizeof(str));
            napi_create_string_utf8(env, str, strlen(str), &result);
            napi_set_element(env, arr, j, result);
        }
    }
    return arr;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor _napi_prop[] = {
            {
                .utf8name = "GetNetworkList",
                .method = GetNetworkList,
                .attributes = napi_default
            }};
    napi_define_properties(env, exports, 1, _napi_prop);
    return exports;
}

NAPI_MODULE(GetNetworkList, Init);