import { addon } from './addon';

let args = [
    'temp.rrd',
    '--start',
    '1000000000',
    '--step',
    '5',
    'DS:temp:GAUGE:20:0:100',
    'RRA:AVERAGE:0.5:1:100'
]

describe('addon', () => {
    describe('create()', () => {
        it('should run without errors', () => {
            addon('create', args);
        });
    });
})