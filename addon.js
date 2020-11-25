"use strict";
exports.__esModule = true;
exports.addon = void 0;
var bindings = require("bindings");
var addonNative = bindings('addon.node');
var addon = function (command, args) {
    if (!addonNative.hasOwnProperty(command)) {
        throw new Error("The command - " + command + " doesn't exist in the addon.");
    }
    addonNative[command].apply(null, args);
};
exports.addon = addon;
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
