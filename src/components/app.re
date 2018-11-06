open Esmodule;
open DomEvents;
open Calculator;
open String;

import("./app.css");

type operator =
  | Delelte
  | Clear
  | Sign
  | Percent
  | Point
  | Equals;

type action =
  | Sums(sums)
  | Op(operator)
  | Number(string);

type state = {
  fst: string,
  snd: option(string),
  op: option(sums),
  flag: ref(string),
};

let initState = {fst: "0", snd: None, op: None, flag: ref("DEL")};

let component = ReasonReact.reducerComponent("App");

let buttonActionCreator = (name, send) =>
  switch (name) {
  | "1"
  | "2"
  | "3"
  | "4"
  | "5"
  | "6"
  | "7"
  | "8"
  | "9"
  | "0" => send(Number(name))
  | "DEL" => send(Op(Delelte))
  | "CLS" => send(Op(Clear))
  | "+/-" => send(Op(Sign))
  | "%" => send(Op(Percent))
  | "." => send(Op(Point))
  | "+" => send(Sums(Sum))
  | "-" => send(Sums(Substract))
  | "*" => send(Sums(Multiply))
  | "/" => send(Sums(Divide))
  | "=" => send(Op(Equals))
  | _ => ()
  };

let mapResult = ({fst, op, snd}) =>
  switch (fst, op, snd) {
  | (x, None, _) => x
  | (x, Some(_), None) => x
  | (_, Some(_), Some(y)) => y
  };

let computeState = (action, {fst, op, snd} as state) =>
  switch (action, fst, op, snd) {
  /* only one zere from start */
  | (Number("0"), "0", _, _) => state
  | (Number("0"), _, _, Some("0")) => state

  /* 0xxx is invalid */
  | (Number(x), "0", _, _) => {...state, fst: x}
  | (Number(x), _, _, Some("0")) => {...state, snd: Some(x)}

  | (Number(x), y, None, _) => {...state, fst: y ++ x}
  | (Number(x), _, Some(_), None) => {...state, snd: Some(x)}
  | (Number(x), _, Some(_), Some(y)) => {...state, snd: Some(y ++ x)}

  | (Op(Delelte), x, None, None) when x != "0" => {
      ...state,
      fst: length(x) > 1 ? sub(x, 0, length(x) - 1) : "0",
    }
  | (Op(Delelte), _, Some(_), Some(y)) when y != "0" => {
      ...state,
      snd: length(y) > 1 ? Some(sub(y, 0, length(y) - 1)) : None,
    }

  | (Op(Clear), _, _, _) => initState

  | (Op(Sign), x, None, _) when x != "0" => {
      ...state,
      fst: get(x, 0) == '-' ? sub(x, 1, length(x) - 1) : "-" ++ x,
    }
  | (Op(Sign), _, Some(_), Some(x)) when x != "0" => {
      ...state,
      snd:
        get(x, 0) == '-' ?
          Some(sub(x, 1, length(x) - 1)) : Some("-" ++ x),
    }

  | (Op(Percent), x, None, _) when x != "0" => {...state, fst: percent(x)}
  | (Op(Percent), _, Some(_), Some(y)) when y != "0" => {
      ...state,
      snd: Some(percent(y)),
    }

  | (Op(Point), x, None, _) => {
      ...state,
      fst: contains(x, '.') ? fst : x ++ ".",
    }
  | (Op(Point), _, Some(_), Some(y)) => {
      ...state,
      snd: contains(y, '.') ? snd : Some(y ++ "."),
    }

  | (Sums(Sum), _, _, None) => {...state, op: Some(Sum)}

  | (Sums(Substract), _, _, None) => {...state, op: Some(Substract)}

  | (Sums(Multiply), _, _, None) => {...state, op: Some(Multiply)}

  | (Sums(Divide), _, _, None) => {...state, op: Some(Divide)}

  | (Sums(newOp), x, Some(oldOp), Some(y)) => {
      ...initState,
      fst: evalValue(x, oldOp, y),
      op: Some(newOp),
    }

  | (Op(Equals), x, Some(op), Some(y)) => {
      ...initState,
      fst: evalValue(x, op, y),
    }

  | (_, _, _, _) => state
  };

let make = _children => {
  ...component,
  initialState: () => initState,
  reducer: (action, state) => {
    state.flag :=
      (
        switch (action) {
        | Op(Equals) => "CLS"
        | _ => "DEL"
        }
      );
    ReasonReact.Update(computeState(action, state));
  },
  didMount: self => {
    let keyUpHandle = evt =>
      switch (ReactEvent.Keyboard.key(evt)) {
      | "Delete" => buttonActionCreator("DEL", self.send)
      | "Backspace" => buttonActionCreator("CLS", self.send)
      | "Enter" => buttonActionCreator("=", self.send)
      | name => buttonActionCreator(name, self.send)
      };
    addEventListener(win, "keyup", keyUpHandle);
    self.onUnmount(() => removeEventListener(win, "keyup", keyUpHandle));
  },
  render: ({state, send}) => {
    let handleClick = name => buttonActionCreator(name, send);

    <div className="component-app">
      <Display result={mapResult(state)} />
      <ButtonPanel onClick=handleClick flag=state.flag^ />
    </div>;
  },
};