"use strict";
exports.__esModule = true;
var addon_1 = require("./addon");
var args = [
    'temp.rrd',
    '--start',
    '1000000000',
    '--step',
    '5',
    'DS:temp:GAUGE:20:0:100',
    'RRA:AVERAGE:0.5:1:100'
];
describe('addon', function () {
    describe('create()', function () {
        it('should run without errors', function () {
            addon_1.addon('create', args);
        });
    });
});
