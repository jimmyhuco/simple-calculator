open Esmodule;

import("./button.css");

let component = ReasonReact.statelessComponent("Button");

let make = (~name, ~orange=?, ~wide=?, ~str=?, ~onClick, _children) => {
  ...component,
  render: _self => {
    let className =
      switch (orange, wide) {
      | (Some(true), Some(true)) => "component-button orange wide"
      | (Some(true), None) => "component-button orange"
      | (None, Some(true)) => "component-button wide"
      | (_, _) => "component-button"
      };
    <div className>
      <button onClick={_event => onClick(name)}>
        {
          ReasonReact.string(
            switch (str) {
            | None => name
            | Some(x) => x
            },
          )
        }
      </button>
    </div>;
  },
};