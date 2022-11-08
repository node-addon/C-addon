const addon = require("./GetNetworkList.node");
let str = "";
let arr = addon.GetNetworkList();
const set = new Set(arr);
arr = Array.from(set);
arr.map((wifi, index) => {
    if (wifi !== "")
        if (arr.length - 2 > index)
            str += `${wifi}\n`;
        else
            str += wifi;
});
console.log(str);