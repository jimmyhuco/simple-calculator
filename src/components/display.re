open Esmodule;

import("./display.css");

let component = ReasonReact.statelessComponent("Display");

let make = (~result, _children) => {
  ...component,
  render: _self =>
    <div className="component-display">
      <div> {ReasonReact.string(result)} </div>
    </div>,
};