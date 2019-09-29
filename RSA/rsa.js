var fs = require('fs')
var bigInt = require("big-integer");
var help = require("./functions")
var tempFile = '../../data/1mb-file.txt'
let p = 3557
let q = 2579
let n = (p * q)
let phi = (p - 1) * (q - 1)
let message = 'Ave'
let e = 3
let d = help.functions.functionD(e, phi)


console.log('n ' + n)
console.log('phi ' + phi)
console.log('d ' + d)
console.log('e ' + e)


const signature = (message, d) => {
    let hexString = help.functions.toHex(message)
    console.log('sign hexString: ' + hexString)
    let decString = Number(help.convert.hex2dec(hexString))
    console.log('sign decString: ' + decString)
    console.log(decString)
    let s = bigInt(decString).modPow(bigInt(d), bigInt(n))
    const pair = {
        's': s,
        'message': message
    }
    
    return pair                  
}
console.log(signature(message, e))

const checkSignature = (pair, e) => {
    console.log('check pair: s ' + pair.s)
    console.log('check pair: e ' + e)
    let m = bigInt(pair.s).modPow(e, n)
    console.log('m ' + m)
    let hexString = help.convert.dec2hex(m)
    let textString = help.functions.hex2a(hexString)
    console.log('Result: ' + textString)
    if(pair.message == textString) return true
    else return false
}

checkSignature(signature(message, d), e)

module.exports.signature = signature;
module.exports.checkSignature = checkSignature;

