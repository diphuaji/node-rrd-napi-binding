const process = require('process')
var addon = require('bindings')('addon.node')

console.log(process.argv)
let argv = process.argv
if(argv.length<3){
  throw new Error('You must specify a command, ie: create, fetch ...')
}
let command = argv[2]
if(!addon.hasOwnProperty(command)){
  throw new Error(`The command - ${command} doesn't exist in the addon.`)
}
console.log(addon.hasOwnProperty('fetch'))
console.log(Object.getOwnPropertyNames(addon))
console.log('return value:', addon['fetch'].apply(this, process.argv.slice(2)))
