"use strict";
exports.__esModule = true;
var addon_1 = require("./addon");
describe('addon', function () {
    var args;
    describe('create()', function () {
        it('should run without errors', function () {
            args = 'create temp.rrd --start 1000000000 --step 5 DS:temp:GAUGE:20:0:100 RRA:AVERAGE:0.5:1:100'.split(' ');
            addon_1.create(args);
        });
    });
    describe('update()', function () {
        it('should run without errors', function () {
            args = 'update temp.rrd 1000000005:8.2 1000000010:1 1000000015:6 1000000020:7 1000000025:7 1000000030:4'.split(' ');
            addon_1.update(args);
        });
    });
    describe('fetch()', function () {
        it('should run without errors', function () {
            args = 'fetch temp.rrd AVERAGE --start 1000000000 --end 1000000045'.split(' ');
            console.log(addon_1.fetch(args));
        });
    });
});
