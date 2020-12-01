"use strict";
exports.__esModule = true;
exports.fetch = exports.update = exports.create = void 0;
var bindings = require("bindings");
var addonNative = bindings('addon.node');
var wrapperFunc = function (command, args) {
    if (!addonNative.hasOwnProperty(command)) {
        throw new Error("The command - " + command + " doesn't exist in the addon.");
    }
    return addonNative[command].apply(null, args);
};
var create = function (args) { return wrapperFunc('create', args); };
exports.create = create;
var update = function (args) { return wrapperFunc('update', args); };
exports.update = update;
var fetch = function (args) { return wrapperFunc('fetch', args); };
exports.fetch = fetch;
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
