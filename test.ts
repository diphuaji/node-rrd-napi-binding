import { create, update, fetch } from './addon';

describe('addon', function () {
    let args: string[];
    describe('create()', function () {
        it('should run without errors', function () {
            args = 'create temp.rrd --start 1000000000 --step 5 DS:temp:GAUGE:20:0:100 RRA:AVERAGE:0.5:1:100'.split(' ');
            create(args);
        });
    });
    describe('update()', function () {
        it('should run without errors', function () {
            args = 'update temp.rrd 1000000005:8.2 1000000010:1 1000000015:6 1000000020:7 1000000025:7 1000000030:4'.split(' ');
            update(args);
        });
    });
    describe('fetch()', function () {
        it('should run without errors', function () {
            args = 'fetch temp.rrd AVERAGE --start 1000000000 --end 1000000045'.split(' ');
            console.log(fetch(args));
        });
    });
})