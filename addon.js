const process = require('process')
var addon = require('bindings')('addon.node')

console.log(process.argv)
console.log('This should be eight:', addon.create.apply(this, process.argv.slice(2)))
