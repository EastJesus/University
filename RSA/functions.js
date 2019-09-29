const functions = {

    nod(x, y) {
        while (y !== 0) y = x % (x = y);
        return x;
    },

     toHex(str) {
        var result = '';
        for (var i=0; i<str.length; i++) {
          result += str.charCodeAt(i).toString(16);
        }
        return result;
      },

      functionD(e, phi) {
        for(let i = 2; i < 1000000000; i++) {
            let left = i * e
            if((left - 1) % phi == 0) {
                return i
            }
        }
    },
    
    functionE(phi){
        for(let i = 0; i < phi - 1; i++) {
            if(this.nod(i, phi) == 1) {
                return i
            } 
            else return i
        }
    },

    hex2a(hexx) {
        var hex = hexx.toString();//force conversion
        var str = '';
        for (var i = 0; (i < hex.length && hex.substr(i, 2) !== '00'); i += 2)
            str += String.fromCharCode(parseInt(hex.substr(i, 2), 16));
        return str;
    },

    gcd(a, b){
        if(b === 0) return a;
        return this.gcd(b, (a % b));
    }
    
}
const convert = {
    bin2dec : s => parseInt(s, 2).toString(10),
    bin2hex : s => parseInt(s, 2).toString(16),
    dec2bin : s => parseInt(s, 10).toString(2),
    dec2hex : s => parseInt(s, 10).toString(16),
    hex2bin : s => parseInt(s, 16).toString(2),
    hex2dec : s => parseInt(s, 16).toString(10)
}

module.exports.functions = functions
module.exports.convert = convert