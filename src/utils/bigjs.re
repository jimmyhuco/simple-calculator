type bignum;

[@bs.module "big.js"] external big: string => bignum = "Big";

[@bs.send] external plus: (bignum, bignum) => bignum = "";
[@bs.send] external minus: (bignum, bignum) => bignum = "";
[@bs.send] external times: (bignum, bignum) => bignum = "";
[@bs.send] external div: (bignum, bignum) => bignum = "";
[@bs.send] external toPrecision: bignum => string = "";