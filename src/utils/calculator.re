open Bigjs;

type sums =
  | Sum
  | Substract
  | Multiply
  | Divide;

let percent = str => big(str)->div(big("100"))->toPrecision;

let eval = (x, op, y) =>
  switch (op) {
  | Sum => big(x)->plus(big(y))
  | Substract => big(x)->minus(big(y))
  | Multiply => big(x)->times(big(y))
  | Divide when y != "0" => big(x)->div(big(y))
  /* x / 0 just return big(x) */
  | _ => big(x)
  };

let evalValue = (x, op, y) => eval(x, op, y)->toPrecision;