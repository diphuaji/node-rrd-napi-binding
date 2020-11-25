"use strict";
exports.__esModule = true;
exports.addon = void 0;
var bindings = require("bindings");
var addonNative = bindings('addon.node');
let args = 'create temp.rrd --start 1000000000 --step 5 DS:temp:GAUGE:20:0:100 RRA:AVERAGE:0.5:1:100'.split(' ');
addonNative['create'].apply(null, args);
args = 'update temp.rrd 1000000003:8 1000000006:1 1000000017:6 1000000020:7 1000000021:7 1000000022:4'.split(' ');
addonNative['update'].apply(null, args);
;
// console.log(process.argv)
// let argv = process.argv
// if (argv.length < 3) {
//   throw new Error('You must specify a command, ie: create, fetch ...')
// }
// let command = argv[2]
// if (!addon.hasOwnProperty(command)) {
//   throw new Error(`The command - ${command} doesn't exist in the addon.`)
// }
// console.log('return value:', addon['fetch'].apply(this, process.argv.slice(2)))
