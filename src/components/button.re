open Esmodule;

import("./button.css");

let component = ReasonReact.statelessComponent("Button");

let make = (~name, ~otherCls=?, ~txt=?, ~onClick, _children) => {
  ...component,
  render: _self => {
    let className =
      switch (otherCls) {
      | Some(cls) => "component-button " ++ cls
      | _ => "component-button"
      };
    <div className>
      <button onClick={_event => onClick(name)}>
        {
          ReasonReact.string(
            switch (txt) {
            | None => name
            | Some(x) => x
            },
          )
        }
      </button>
    </div>;
  },
};