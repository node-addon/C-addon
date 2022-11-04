const addon = require("./GetSystemPower");
const result = addon.GetSystemPowerStatus();
console.log(result); // {
                     //     ACLineStatus: 1,
                     //     BatteryFlag: 1,
                     //     BatteryLifePercent: 98,
                     //     SystemStatusFlag: 0,
                     //     BatteryLifeTime: -1,
                     //     BatteryFullLifeTime: -1
                     // }
